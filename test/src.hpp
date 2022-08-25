#pragma once

#include <parsium/common.hpp>

#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

using namespace parsium;

class InputStream {
public:
	std::string data;
	int offset = 0;

	InputStream() = default;

	InputStream(const char* data)
		: data(data)
	{}

	auto peek() -> int {
		if(offset >= int(data.size())) {
			return EOF;
		} else {
			return data[offset];
		}
	}

	auto get() -> int {
		auto p = peek();
		if(p != EOF) {
			offset += 1;
		}
		return p;
	}

	void asg_offset(int i) {
		assert(i > 0);
		offset = i;
	}
};

class Characters {
public:
	std::string content_;

	explicit Characters(std::string content)
		: content_(std::move(content))
	{}
};

auto does_accept(const Characters& cs, int position, char c) -> bool {
	return c == cs.content_[position];
}

class Codepoint {
public:
	char symbol = 0;

	Codepoint(char c)
		: symbol(c)
	{}
};

auto does_accept(const Codepoint& co, int, char ch) -> bool {
	return ch == co.symbol;
}

class Range {
public:
	char lower_bound_ = 0;
	char upper_bound_ = 0;

	Range() = default;

	Range(char lb, char ub)
		: lower_bound_(lb)
		  , upper_bound_(ub)
	{}
};

auto does_contain(const Range& r, char c) -> bool {
	return c >= r.lower_bound_ && c <= r.upper_bound_;
}

auto does_accept(const Range& r, int, char c) -> bool {
	return does_contain(r, c);
}

class Exclude {
public:
	char symbol = 0;

	Exclude(char s)
		: symbol(s)
	{}
};

class RangeExclude {
public:
	Range range;
	std::vector<Exclude> excludes;

	RangeExclude() = default;

	RangeExclude(Range r)
		: range(std::move(r))
	{}

	RangeExclude(Range r, std::vector<Exclude> excludes)
		: range(std::move(r))
		  , excludes(std::move(excludes))
	{}
};

auto does_contain(const RangeExclude& re, char c) -> bool {
	auto does_range = does_contain(re.range, c);
	if(!does_range) {
		return false;
	} else {
		auto does_excludes = true;
		for(auto& e : re.excludes) {
			if(e.symbol == c) {
				does_excludes = false;
				break;
			}
		}
		return does_excludes;
	}
}

auto does_accept(const RangeExclude& re, int, char c) -> bool {
	return does_contain(re, c);
}

class Literal {
public:
	using Variant = std::variant<std::monostate, Characters, Codepoint, Range, RangeExclude>;

	Variant content_;

	explicit Literal(Variant content)
		: content_(std::move(content))
	{}
};

class Name {
public:
	std::string content_;

	Name() = default;

	Name(std::string s)
		: content_(std::move(s))
	{}

	auto operator=(std::string s) -> Name& {
		content_ = std::move(s);
		return *this;
	}
};

auto operator<(const Name& n0, const Name& n1) -> bool {
	return n0.content_ < n1.content_;
}

class Item {
public:
	using Variant = std::variant<std::monostate, Literal, Name>;

	Variant content_;

	Item(Variant content)
		: content_(std::move(content))
	{}
};

class Alternative {
public:
	std::vector<Item> items_;

	Alternative() = default;

	explicit Alternative(std::vector<Item>&& items)
		: items_(std::move(items))
	{}
};

class Rule {
public:
	Name name;
	std::vector<Alternative> alternatives_;

	bool does_accept_nothing = false;
};

class Grammar {
public:
	std::map<Name, Rule> named_rules_;
};

auto rule(const Grammar& g, const Name& n) -> NP<const Rule> {
	auto it = g.named_rules_.find(n);
	if(it == end(g.named_rules_)) {
		return nullptr;
	} else {
		return &it->second;
	}
}

class ParsingNode {
public:
	ParsingNode() = default;

	explicit ParsingNode(P<const Rule> rule, int offset = 0)
		: rule(rule)
		, input_offset(offset)
	{}

	NP<const Rule> rule;
	int alternative = 0;
	int item = 0;
	int character_ = 0;

	int input_offset = 0;
};

auto current_alternative(const ParsingNode& n) -> NP<const Alternative> {
	return &n.rule->alternatives_[n.alternative];
}

auto current_item(const ParsingNode& n) -> NP<const Item> {
	return &current_alternative(n)->items_[n.item];
}

auto is_out_of_alternatives(const ParsingNode& n) -> bool {
	return n.alternative >= int(n.rule->alternatives_.size());
}

auto has_current_alternative(const ParsingNode& n) -> bool {
	return n.alternative < int(n.rule->alternatives_.size());
}

auto has_current_item(const ParsingNode& n) -> bool {
	return n.item < int(current_alternative(n)->items_.size());
}

enum class ParsingStatus {
	undefined,
	accepted,
	rejected
};

class Parser {
public:
	NP<const Grammar> grammar;
	NP<const Rule> initial_rule_;

	std::vector<ParsingNode> stack;

	ParsingStatus status = ParsingStatus::undefined;
};

void push(Parser& p, const Name& n) {
	auto r = rule(*p.grammar, n);
	if(r == nullptr) {
		p.stack.clear();
	} else {
		auto n = ParsingNode();
		n.rule = r;
		p.stack.push_back(std::move(n));
	}
}

void pop(Parser& p) {
	if(!p.stack.empty()) {
		p.stack.pop_back();
	}
}

auto top(const Parser& p) -> NP<const ParsingNode> {
	if(p.stack.empty()) {
		return nullptr;
	} else {
		return &p.stack.back();
	}
}

auto top(Parser& p) -> NP<ParsingNode> {
	if(p.stack.empty()) {
		return nullptr;
	} else {
		return &p.stack.back();
	}
}

void init(Parser&) {
	// NOP.
}

auto is_accepting(const Parser& p) -> bool {
	return p.status == ParsingStatus::accepted;
}

class ParsingContext {
public:
	Parser* parser;
	InputStream* input;
};

auto is_done(const ParsingContext& c) -> bool {
	auto is_input_done = c.input->peek() == EOF;
	auto is_parser_rejecting = c.parser->stack.empty();
	return is_input_done || is_parser_rejecting;
}

auto parse_rule(ParsingContext& c, const Rule& r) -> ParsingStatus;

auto parse_characters(ParsingContext& co, const Characters& ch) -> ParsingStatus {
	auto t = top(*co.parser);
	while(true) {
		auto received = co.input->peek();
		if(received == EOF) {
			return ParsingStatus::rejected;
		} else {
			auto expected = ch.content_[t->character_];
			if(received != expected) {
				return ParsingStatus::rejected;
			} else {
				co.input->get();
				t->character_ += 1;
				if(t->character_ == ch.content_.size()) {
					return ParsingStatus::accepted;
				}
			}
		}
	}
}

auto parse_range(ParsingContext& c, const Range& r) -> ParsingStatus {
	while(true) {
		auto received = c.input->peek();
		if(received == EOF) {
			return ParsingStatus::rejected;
		} else {
			if(does_contain(r, received)) {
				c.input->get();
				return ParsingStatus::accepted;
			} else {
				return ParsingStatus::rejected;
			}
		}
	}
}

auto parse_range_exclude(ParsingContext& c, const RangeExclude& re) -> ParsingStatus {
	while(true) {
		auto received = c.input->peek();
		if(received == EOF) {
			return ParsingStatus::rejected;
		} else {
			if(does_contain(re, received)) {
				c.input->get();
				return ParsingStatus::accepted;
			} else {
				return ParsingStatus::rejected;
			}
		}
	}
}

auto parse_singleton(ParsingContext& c, const Codepoint& s) -> ParsingStatus {
	while(true) {
		auto received = c.input->peek();
		if(received == EOF) {
			return ParsingStatus::rejected;
		} else {
			if(received == s.symbol) {
				c.input->get();
				return ParsingStatus::accepted;
			} else {
				return ParsingStatus::rejected;
			}
		}
	}
}

auto parse_literal(ParsingContext& c, const Literal& l) -> ParsingStatus {
	if(auto characters = get_if<Characters>(&l.content_)) {
		auto result = parse_characters(c, *characters);
		// If the result is accepted or rejected,
		// the character position need to be reset to 0
		// because the parsing node might be reused for another item.
		auto is_accepted = result == ParsingStatus::accepted;
		auto is_rejected = result == ParsingStatus::rejected;
		if(is_accepted || is_rejected) {
			auto t = top(*c.parser);
			t->character_ = 0;
		}
		return result;
	} else if(auto range = get_if<Range>(&l.content_)) {
		return parse_range(c, *range);
	} else if(auto range_exclude = get_if<RangeExclude>(&l.content_)) {
		return parse_range_exclude(c, *range_exclude);
	} else if(auto singleton = get_if<Codepoint>(&l.content_)) {
		return parse_singleton(c, *singleton);
	} else {
		return ParsingStatus::rejected;
	}
}

auto parse_name(ParsingContext& c, const Name& n) -> ParsingStatus {
	auto r = rule(*c.parser->grammar, n);
	if(r == nullptr) {
		return ParsingStatus::rejected;
	} else {
		return parse_rule(c, *r);
	}
}

auto parse_item(ParsingContext& c, const Item& i) -> ParsingStatus {
	if(auto literal = std::get_if<Literal>(&i.content_)) {
		return parse_literal(c, *literal);
	} else if(auto name = std::get_if<Name>(&i.content_)) {
		return parse_name(c, *name);
	} else {
		return ParsingStatus::rejected;
	}
}

auto parse_alternative(ParsingContext& c, const Alternative& a) -> ParsingStatus {
	while(true) {
		if(!has_current_item(*top(*c.parser))) {
			// Parsed all items. Success.
			return ParsingStatus::accepted;
		} else {
			auto i = current_item(*top(*c.parser));
			auto status = parse_item(c, *i);
			if(status == ParsingStatus::accepted) {
				// Moves to the next item.
				top(*c.parser)->item += 1;
			} else if(status == ParsingStatus::rejected) {
				return status;
			}
		}
	}
}

auto parse_rule(ParsingContext& c, const Rule& r) -> ParsingStatus {
	// Adds a node for the rule to parse.
	c.parser->stack.push_back(ParsingNode(r, c.input->offset));
	// Tries all alternatives.
	while(true) {
		// Must be careful, t might be invalidated.
		auto t = top(*c.parser);
		if(!has_current_alternative(*t)) {
			// Couldn't fully parse any alternative.
			// Removes current node.
			c.parser->stack.pop_back();
			if(r.does_accept_nothing) {
				return ParsingStatus::accepted;
			} else {
				return ParsingStatus::rejected;
			}
		} else {
			auto a = current_alternative(*t);
			auto status = parse_alternative(c, *a);
			if(status == ParsingStatus::accepted) {
				// Succeeded to fully parse one alternative.
				// Removes current node.
				c.parser->stack.pop_back();
				return ParsingStatus::accepted;
			} else if(status == ParsingStatus::rejected) {
				// Failed to parse current alternative/
				// Moving to the next one.
				// `t` might have been invalidated.
				t = top(*c.parser);
				// Goes back to the first item.
				t->item = 0;
				t->alternative += 1;
				// Resets rule offset.
				c.input->offset = t->input_offset;
			}
		}
	}
}

auto parse(ParsingContext& c) -> ParsingStatus {
	c.parser->status = parse_rule(c, *c.parser->initial_rule_);
	assert(c.parser->stack.empty());
	auto p = c.input->peek();
	if(p != EOF) {
		c.parser->status = ParsingStatus::rejected;
	}
	return c.parser->status;
}

void parse(Parser& p, InputStream& is) {
	auto context = ParsingContext();
	context.parser = &p;
	context.input = &is;
	parse(context);
}
