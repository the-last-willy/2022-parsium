#include <parsium/common.hpp>

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

using namespace parsium;

class Codepoint {
public:
	char symbol = 0;

	Codepoint(char c)
	: symbol(c)
	{}
};

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

class Item {
public:
	std::variant<Codepoint, Range> content_;
};

class Alternative {
public:
	std::vector<Item> items_;

	explicit Alternative(std::vector<Item>&& items)
	: items_(std::move(items))
	{}
};

class Rule {
public:
	std::string name_;
	std::vector<Alternative> alternatives_;
};

class ParsingNode {
public:
	NP<Rule> rule_;
	int alternative_ = -1;
	int item_ = 0;

	int start = 0;
	int count = 0;

	std::vector<ParsingNode> children_;
};

class Parser {
public:
	ParsingNode parsing_tree_;
	NP<ParsingNode> head_ = nullptr;
};

auto is_accepting(const Parser& p) {
	if(p.head_ == nullptr) {
		return false;
	} else {
		auto head = p.head_;
		auto rule = head->rule_;
		auto alternative = &rule->alternatives_[head->alternative_];
		return head->item_ == alternative->items_.size();
	}
}

void parse(Parser& p, std::istream& is) {
	while(is.peek() != EOF) {
		if(p.head_ == nullptr) {
			break;
		} else {
			auto node = p.head_;
			auto rule = node->rule_;
			auto c = is.get();
			auto alternative = &rule->alternatives_[node->alternative_];
			if(node->item_ >= alternative->items_.size()) {
				p.head_ = nullptr;
			} else {
				auto item = &alternative->items_[node->item_];
				if(auto codepoint = get_if<Codepoint>(&item->content_)) {
					if(codepoint->symbol == c) {
						node->count += 1;
						node->item_ += 1;
					} else {
						p.head_ = nullptr;
						break;
					}
				} else if(auto range = get_if<Range>(&item->content_)) {
					if(range->lower_bound_ <= c && range->upper_bound_ >= c) {
						node->count += 1;
						node->item_ += 1;
					} else {
						p.head_ = nullptr;
						break;
					}
				} else {
					p.head_ = nullptr;
					break;
				}
			}
		}
	}
}

auto indentation_rule() -> Rule {
	auto rule = Rule();
	rule.name_ = "indentation";
	{
		auto alternative = std::vector<Item>();
		alternative.push_back(Item{Codepoint(' ')});
		alternative.push_back(Item{Codepoint(' ')});
		alternative.push_back(Item{Codepoint(' ')});
		alternative.push_back(Item{Codepoint(' ')});
		rule.alternatives_.push_back(Alternative(std::move(alternative)));
	}
	return rule;
};

auto letter_rule() -> Rule {
	auto rule = Rule();
	rule.name_ = "letter";
	{
		auto alternative = std::vector<Item>();
		alternative.push_back(Item{Range('a', 'z')});
		rule.alternatives_.push_back(Alternative(std::move(alternative)));
	}
	return rule;
}

auto space_rule() -> Rule {
	auto rule = Rule();
	rule.name_ = "space";
	{
		auto alternative = std::vector<Item>();
		alternative.push_back(Item{Codepoint(' ')});
		rule.alternatives_.push_back(Alternative(std::move(alternative)));
	}
	return rule;
};

int main() {
	auto indentation = indentation_rule();
	auto letter = letter_rule();
	auto space = space_rule();

	{
		auto ss = std::stringstream(" ");
		auto parser = Parser();
		parser.parsing_tree_.rule_ = &space;
		parser.head_ = &parser.parsing_tree_;

		parse(parser, ss);

		assert(is_accepting(parser));
	}

	{
		auto ss = std::stringstream("a");
		auto parser = Parser();
		parser.parsing_tree_.rule_ = &space;
		parser.head_ = &parser.parsing_tree_;

		parse(parser, ss);

		assert(!is_accepting(parser));
	}

	{
		auto ss = std::stringstream("    ");
		auto parser = Parser();
		parser.parsing_tree_.rule_ = &indentation;
		parser.head_ = &parser.parsing_tree_;

		parse(parser, ss);

		assert(is_accepting(parser));
	}

	{
		auto ss = std::stringstream("   ");
		auto parser = Parser();
		parser.parsing_tree_.rule_ = &indentation;
		parser.head_ = &parser.parsing_tree_;

		parse(parser, ss);

		assert(!is_accepting(parser));
	}

	{
		auto ss = std::stringstream("     ");
		auto parser = Parser();
		parser.parsing_tree_.rule_ = &indentation;
		parser.head_ = &parser.parsing_tree_;

		parse(parser, ss);

		assert(!is_accepting(parser));
	}

	{
		auto ss = std::stringstream("a");
		auto parser = Parser();
		parser.parsing_tree_.rule_ = &letter;
		parser.head_ = &parser.parsing_tree_;

		parse(parser, ss);

		assert(is_accepting(parser));
	}

	{
		auto ss = std::stringstream("z");
		auto parser = Parser();
		parser.parsing_tree_.rule_ = &letter;
		parser.head_ = &parser.parsing_tree_;

		parse(parser, ss);

		assert(is_accepting(parser));
	}

	{
		auto ss = std::stringstream(" ");
		auto parser = Parser();
		parser.parsing_tree_.rule_ = &letter;
		parser.head_ = &parser.parsing_tree_;

		parse(parser, ss);

		assert(!is_accepting(parser));
	}

	{
		auto ss = std::stringstream("A");
		auto parser = Parser();
		parser.parsing_tree_.rule_ = &letter;
		parser.head_ = &parser.parsing_tree_;

		parse(parser, ss);

		assert(is_accepting(parser));
	}

	{
		auto ss = std::stringstream("Z");
		auto parser = Parser();
		parser.parsing_tree_.rule_ = &letter;
		parser.head_ = &parser.parsing_tree_;

		parse(parser, ss);

		assert(is_accepting(parser));
	}
}
