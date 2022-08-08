#pragma once

#include "mckeeman_node.hpp"

#include <array>
#include <cassert>
#include <span>
#include <string>
#include <vector>

namespace parsium {

////////////////////////////////////////////////////////////////////////////////
// Helpers.

template<typename T>
auto popped_front(std::vector<T> v) {
	v.erase(begin(v));
	return v;
}

////////////////////////////////////////////////////////////////////////////////

// Grammar.

MckeemanNode mckeeman_grammar();

// Rule.

MckeemanNode mckeeman_alternative_rule();
MckeemanNode mckeeman_alternatives_rule();
MckeemanNode mckeeman_character_rule();
MckeemanNode mckeeman_characters_rule();
MckeemanNode mckeeman_codepoint_rule();
MckeemanNode mckeeman_exclude_rule();
MckeemanNode mckeeman_grammar_rule();
MckeemanNode mckeeman_hex_rule();
MckeemanNode mckeeman_hexcode_rule();
MckeemanNode mckeeman_indentation_rule();
MckeemanNode mckeeman_item_rule();
MckeemanNode mckeeman_items_rule();
MckeemanNode mckeeman_letter_rule();
MckeemanNode mckeeman_literal_rule();
MckeemanNode mckeeman_name_rule();
MckeemanNode mckeeman_newline_rule();
MckeemanNode mckeeman_nothing_rule();
MckeemanNode mckeeman_range_rule();
MckeemanNode mckeeman_rule_rule();
MckeemanNode mckeeman_rules_rule();
MckeemanNode mckeeman_singleton_rule();
MckeemanNode mckeeman_space_rule();

// Generalization.

MckeemanNode mckeeman_rule_of(const MckeemanNode&);

// Instance.

MckeemanNode mckeeman_alternative(std::vector<MckeemanNode> items);
MckeemanNode mckeeman_alternatives(std::vector<MckeemanNode> as);
MckeemanNode mckeeman_codepoint(char c);
MckeemanNode mckeeman_grammar(std::vector<MckeemanNode> rules);
MckeemanNode mckeeman_indentation();
MckeemanNode mckeeman_item(MckeemanNode item);
MckeemanNode mckeeman_item(const std::string& s);
MckeemanNode mckeeman_items(MckeemanNode first_item);
MckeemanNode mckeeman_letter(char);
MckeemanNode mckeeman_name(const std::string&);
MckeemanNode mckeeman_newline();
MckeemanNode mckeeman_nothing(bool does_accept_nothing);
MckeemanNode mckeeman_range(char lb, char ub);
MckeemanNode mckeeman_rule(const std::string& name, bool does_accept_nothing, std::vector<MckeemanNode> alternatives);
MckeemanNode mckeeman_rules(std::vector<MckeemanNode> rules);
MckeemanNode mckeeman_singleton(char symbol);
MckeemanNode mckeeman_space();

////////////////////////////////////////////////////////////////////////////////

// Grammar.

MckeemanNode mckeeman_grammar() {
	auto rules = std::vector<MckeemanNode>();
	rules.push_back(mckeeman_rule_of(mckeeman_grammar_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_space_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_newline_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_name_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_letter_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_indentation_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_rules_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_rule_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_nothing_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_alternatives_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_alternative_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_items_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_item_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_literal_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_singleton_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_codepoint_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_hexcode_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_hex_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_range_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_exclude_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_characters_rule()));
	rules.push_back(mckeeman_rule_of(mckeeman_character_rule()));
	return mckeeman_grammar(std::move(rules));
}

// Rule.



// Generalization.



// Instance.

MckeemanNode mckeeman_alternative(MckeemanNode alternative) {
	auto r = MckeemanNode();
	*name(r) = "alternative";
	auto items = std::vector<MckeemanNode>();
	items.push_back(mckeeman_indentation());
	items.push_back(mckeeman_items(std::move(alternative)));
	items.push_back(mckeeman_newline());
	create_alternative(r, std::move(items));
	return r;
}

MckeemanNode mckeeman_alternatives(std::vector<MckeemanNode> alternatives) {
	// assert(size(as) > 0);
	auto r = MckeemanNode();
	*name(r) = "alternatives";
	if(size(alternatives) == 1) {
		auto items = std::vector<MckeemanNode>();
		items.push_back(mckeeman_alternative(std::move(alternatives[0])));
		create_alternative(r, std::move(items));
	} else if(size(alternatives) > 1) {
		auto items = std::vector<MckeemanNode>();
		items.push_back(mckeeman_alternative(std::move(alternatives[0])));
		items.push_back(mckeeman_alternatives(popped_front(std::move(alternatives))));
		create_alternative(r, std::move(items));
	}
	return r;
}

MckeemanNode mckeeman_codepoint(char c) {
    // Missing second alternative.
	auto r = MckeemanNode();
	*name(r) = "codepoint";
	*literal(r) = std::string(1, c);
	return r;
}

MckeemanNode mckeeman_grammar(std::vector<MckeemanNode> rules) {
	auto ret = MckeemanNode();
	*name(ret) = "grammar";
	auto items = std::vector<MckeemanNode>();
	items.push_back(mckeeman_rules(std::move(rules)));
	create_alternative(ret, std::move(items));
	return ret;
}

MckeemanNode mckeeman_indentation() {
    auto r =  MckeemanNode();
	*name(r) = "indentation";
	auto items = std::vector<MckeemanNode>();
	items.push_back(mckeeman_space());
	items.push_back(mckeeman_space());
	items.push_back(mckeeman_space());
	items.push_back(mckeeman_space());
	create_alternative(r, std::move(items));
	return r;
}

MckeemanNode mckeeman_item(MckeemanNode item) {
	auto r = MckeemanNode();
	*name(r) = "item";
	auto items = std::vector<MckeemanNode>();
	items.push_back(std::move(item));
	create_alternative(r, std::move(items));
	return r;
}

MckeemanNode mckeeman_item(const std::string& s) {
	auto r = MckeemanNode();
	*name(r) = s;
	return r;
}

MckeemanNode mckeeman_items(MckeemanNode first_item) {
	auto r = MckeemanNode();
	*name(r) = "items";
	if(!has_next_item(first_item)) {
		auto items = std::vector<MckeemanNode>();
		items.push_back(mckeeman_item(std::move(first_item)));
		create_alternative(r, std::move(items));
	} else {
		auto tail = next_item(first_item);
		first_item.next_item_ = nullptr;
		auto items = std::vector<MckeemanNode>();
		items.push_back(mckeeman_item(std::move(first_item)));
		items.push_back(mckeeman_space());
		items.push_back(mckeeman_items(std::move(*tail)));
		create_alternative(r, std::move(items));
	}
	return r;
}

MckeemanNode mckeeman_letter(char c) {
	auto r = MckeemanNode();
	*name(r) = "letter";
	*literal(r) = std::string(1, c);
	return r;
}

MckeemanNode mckeeman_name(const std::string& s) {
    assert(size(s) > 0);
	auto r = MckeemanNode();
	*name(r) = "name";
	*literal(r) = s;
	return r;
}

MckeemanNode mckeeman_newline() {
	auto r = MckeemanNode();
	*name(r) = "newline";
	*literal(r) = "\n";
	return r;
}

MckeemanNode mckeeman_nothing(
    bool does_accept_nothing)
{
	auto r = MckeemanNode();
	*name(r) = "nothing";
    if(does_accept_nothing) {
		auto items = std::vector<MckeemanNode>();
		items.push_back(mckeeman_indentation());
		items.push_back(mckeeman_singleton('"'));
		items.push_back(mckeeman_singleton('"'));
		items.push_back(mckeeman_newline());
		create_alternative(r, std::move(items));
    }
	return r;
}

MckeemanNode mckeeman_range(char lb, char ub) {
	auto r = MckeemanNode();
	*name(r) = "range";
	auto items = std::vector<MckeemanNode>();
	items.push_back(mckeeman_singleton(lb));
	items.push_back(mckeeman_space());
	items.push_back(mckeeman_singleton('.'));
	items.push_back(mckeeman_space());
	items.push_back(mckeeman_singleton(ub));
	create_alternative(r, std::move(items));
	return r;
}

MckeemanNode mckeeman_rule(MckeemanNode r)
{
	return r;
}

MckeemanNode mckeeman_rules(std::vector<MckeemanNode> rules) {
	assert(size(rules) > 0);
	auto r = MckeemanNode();
	*name(r) = "rules";
	if(size(rules) == 1) {
		auto items = std::vector<MckeemanNode>();
		items.push_back(mckeeman_rule(std::move(rules[0])));
		create_alternative(r, std::move(items));
	} else if(size(rules) > 1) {
		auto items = std::vector<MckeemanNode>();
		items.push_back(mckeeman_rule(std::move(rules[0])));
		items.push_back(mckeeman_rules(popped_front(std::move(rules))));
		create_alternative(r, std::move(items));
	}
	return r;
}

MckeemanNode mckeeman_singleton(
    char codepoint)
{
	auto r = MckeemanNode();
	*name(r) = "singleton";
	auto items = std::vector<MckeemanNode>();
	items.push_back(mckeeman_codepoint('\''));
	items.push_back(mckeeman_codepoint(codepoint));
	items.push_back(mckeeman_codepoint('\''));
	create_alternative(r, std::move(items));
	return r;
}

MckeemanNode mckeeman_space() {
	auto r = MckeemanNode();
	*name(r) = "space";
	*literal(r) = " ";
	return r;
}

}