#pragma once

#include "parsium/mckeeman/storing/building.hpp"
#include "parsium/mckeeman/storing/node.hpp"

#include "parsium/common/std/vector.hpp"

#include <array>
#include <cassert>
#include <span>
#include <string>
#include <vector>

namespace parsium::mckeeman {

auto mckeeman_alternative(std::vector<std::unique_ptr<StorageNode>> items) -> StorageNodeHandle;
auto mckeeman_alternatives(std::vector<std::unique_ptr<StorageNode>> alternatives) -> StorageNodeHandle;
auto mckeeman_codepoint(char) -> StorageNodeHandle;
auto mckeeman_exclude(char, StorageNodeHandle&& exclude = {}) -> StorageNodeHandle;
auto mckeeman_exclude(char lower_bound, char upper_bound, StorageNodeHandle&& exclude = {}) -> StorageNodeHandle;
auto mckeeman_name(std::string name) -> StorageNodeHandle;
auto mckeeman_newline() -> StorageNodeHandle;
auto mckeeman_nothing(bool does_accept_nothing) -> StorageNodeHandle;
auto mckeeman_range(char lower_bound, char upper_bound) -> StorageNodeHandle;
auto mckeeman_rules(std::span<std::unique_ptr<StorageNode>> rules) -> StorageNodeHandle;
auto mckeeman_singleton(char codepoint) -> StorageNodeHandle;
auto mckeeman_space() -> StorageNodeHandle;

//////////////////////////////////////////////////////////////////////////////////

StorageNodeHandle mckeeman_alternative(std::vector<std::unique_ptr<StorageNode>> items) {
	if(items.empty()) {
		return nullptr;
	} else {
		auto it = items[0].get();
		assert(it != nullptr);
		for(std::size_t i = 1; i < size(items); ++i) {
			it = add_sibling(*it, std::move(items[i]));
		}
		return std::move(items[0]);
	}
}

StorageNodeHandle mckeeman_alternatives(std::vector<std::unique_ptr<StorageNode>> alternatives) {
	if(alternatives.empty()) {
		return nullptr;
	} else {
		auto ret = StorageNodeHandle();
		auto it = ret.get();
		for(auto& items : alternatives) {
			auto alternative = std::make_unique<StorageNode>();
			add_child(*alternative, std::move(items));
			if(it == nullptr) {
				ret = std::move(alternative);
				it = ret.get();
			} else {
				it = add_sibling(*it, std::move(alternative));
			}
		}
		return ret;
	}
}

auto mckeeman_codepoint(char c) -> StorageNodeHandle {
	return std::make_unique<StorageNode>("codepoint", std::string(1, c));
}

auto mckeeman_exclude(char c, StorageNodeHandle&& exclude) -> StorageNodeHandle {
	auto ret = mckeeman_name("exclude");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(mckeeman_space());
		items.push_back(mckeeman_singleton('-'));
		items.push_back(mckeeman_space());
		items.push_back(mckeeman_singleton(c));
		if(exclude != nullptr) {
			items.push_back(std::move(exclude));
		}
		add_child(*ret, link_as_siblings(std::move(items)));
	}
	return ret;
}

auto mckeeman_exclude(char lower_bound, char upper_bound, StorageNodeHandle&& exclude) -> StorageNodeHandle {
	auto ret = mckeeman_name("exclude");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(mckeeman_space());
		items.push_back(mckeeman_singleton('-'));
		items.push_back(mckeeman_space());
		items.push_back(mckeeman_range(lower_bound, upper_bound));
		if(exclude != nullptr) {
			items.push_back(std::move(exclude));
		}
		add_child(*ret, link_as_siblings(std::move(items)));
	}
	return ret;
}

auto mckeeman_indentation() -> StorageNodeHandle {
	auto ret = mckeeman_name("indentation");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(mckeeman_space());
		items.push_back(mckeeman_space());
		items.push_back(mckeeman_space());
		items.push_back(mckeeman_space());
		add_child(*ret, mckeeman_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_name(std::string name) -> StorageNodeHandle {
	return std::make_unique<StorageNode>(std::move(name));
}

auto mckeeman_newline() -> StorageNodeHandle {
	return std::make_unique<StorageNode>("newline", std::string(1, 0x0A));
}

auto mckeeman_nothing(bool is_accepted) -> StorageNodeHandle {
	auto ret = mckeeman_name("nothing");
	if(is_accepted) {
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(mckeeman_indentation());
		items.push_back(mckeeman_singleton('\''));
		items.push_back(mckeeman_singleton('\''));
		items.push_back(mckeeman_newline());
		add_child(*ret, storage_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_range(char lower_bound, char upper_bound) -> StorageNodeHandle {
	auto ret = mckeeman_name("range");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(mckeeman_singleton(lower_bound));
		items.push_back(mckeeman_space());
		items.push_back(mckeeman_singleton('.'));
		items.push_back(mckeeman_space());
		items.push_back(mckeeman_singleton(upper_bound));
		add_child(*ret, mckeeman_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_rule(StorageNodeHandle rule) -> StorageNodeHandle {
	auto ret = mckeeman_name("rule");
	add_child(*ret, std::move(rule));
	return ret;
}

auto mckeeman_rules(std::vector<std::unique_ptr<StorageNode>> rules) -> StorageNodeHandle {
	auto ret = mckeeman_name("rules");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(mckeeman_rule(std::move(rules[0])));
		if(size(rules) > 1) {
			items.push_back(mckeeman_newline());
			items.push_back(mckeeman_rules(popped_front(std::move(rules))));
		}
		add_child(*ret, mckeeman_alternative(std::move(items)));
	}
	return ret;
}

StorageNodeHandle mckeeman_singleton(char codepoint) {
	auto ret = mckeeman_name("singleton");
	auto items = std::vector<std::unique_ptr<StorageNode>>();
	items.push_back(std::make_unique<StorageNode>("", "\'"));
	items.push_back(mckeeman_codepoint(codepoint));
	items.push_back(std::make_unique<StorageNode>("", "\'"));
	add_child(*ret, mckeeman_alternative(std::move(items)));
	return ret;
}

StorageNodeHandle mckeeman_space() {
	return std::make_unique<StorageNode>("space", std::string(1, 0x20));
}


//////////////////////////////////////////////////////////////////////////////////
//
//// Instance.
//
//MckeemanNode mckeeman_alternative(std::vector<MckeemanNode> items);
//MckeemanNode mckeeman_alternatives(std::vector<MckeemanNode> as);
//MckeemanNode mckeeman_codepoint(char c);
//MckeemanNode mckeeman_grammar(std::vector<MckeemanNode> rules);
//MckeemanNode mckeeman_indentation();
//MckeemanNode mckeeman_item(MckeemanNode item);
//MckeemanNode mckeeman_item(const std::string& s);
//MckeemanNode mckeeman_items(MckeemanNode first_item);
//MckeemanNode mckeeman_letter(char);
//MckeemanNode mckeeman_name(const std::string&);
//MckeemanNode mckeeman_newline();
//MckeemanNode mckeeman_nothing(bool does_accept_nothing);
//MckeemanNode mckeeman_range(char lb, char ub);
//MckeemanNode mckeeman_rule(const std::string& name, bool does_accept_nothing, std::vector<MckeemanNode> alternatives);
//MckeemanNode mckeeman_rules(std::vector<MckeemanNode> rules);
//MckeemanNode mckeeman_singleton(char symbol);
//MckeemanNode mckeeman_space();
//
//////////////////////////////////////////////////////////////////////////////////
//
//// Grammar.
//
//MckeemanNode mckeeman_grammar() {
//	auto rules = std::vector<MckeemanNode>();
//	rules.push_back(mckeeman_rule_of(mckeeman_grammar_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_space_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_newline_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_name_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_letter_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_indentation_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_rules_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_rule_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_nothing_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_alternatives_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_alternative_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_items_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_item_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_literal_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_singleton_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_codepoint_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_hexcode_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_hex_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_range_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_exclude_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_characters_rule()));
//	rules.push_back(mckeeman_rule_of(mckeeman_character_rule()));
//	return mckeeman_grammar(std::move(rules));
//}
//
//// Rule.
//
//
//
//// Generalization.
//
//
//
//// Instance.
//
//MckeemanNode mckeeman_alternative(MckeemanNode alternative) {
//	auto r = MckeemanNode();
//	*name(r) = "alternative";
//	auto items = std::vector<MckeemanNode>();
//	items.push_back(mckeeman_indentation());
//	items.push_back(mckeeman_items(std::move(alternative)));
//	items.push_back(mckeeman_newline());
//	create_alternative(r, std::move(items));
//	return r;
//}
//
//MckeemanNode mckeeman_alternatives(std::vector<MckeemanNode> alternatives) {
//	// assert(size(as) > 0);
//	auto r = MckeemanNode();
//	*name(r) = "alternatives";
//	if(size(alternatives) == 1) {
//		auto items = std::vector<MckeemanNode>();
//		items.push_back(mckeeman_alternative(std::move(alternatives[0])));
//		create_alternative(r, std::move(items));
//	} else if(size(alternatives) > 1) {
//		auto items = std::vector<MckeemanNode>();
//		items.push_back(mckeeman_alternative(std::move(alternatives[0])));
//		items.push_back(mckeeman_alternatives(popped_front(std::move(alternatives))));
//		create_alternative(r, std::move(items));
//	}
//	return r;
//}
//
//MckeemanNode mckeeman_codepoint(char c) {
//	// Missing second alternative.
//	auto r = MckeemanNode();
//	*name(r) = "codepoint";
//	*literal(r) = std::string(1, c);
//	return r;
//}
//
//MckeemanNode mckeeman_grammar(std::vector<MckeemanNode> rules) {
//	auto ret = MckeemanNode();
//	*name(ret) = "grammar";
//	auto items = std::vector<MckeemanNode>();
//	items.push_back(mckeeman_rules(std::move(rules)));
//	create_alternative(ret, std::move(items));
//	return ret;
//}
//
//MckeemanNode mckeeman_indentation() {
//	auto r =  MckeemanNode();
//	*name(r) = "indentation";
//	auto items = std::vector<MckeemanNode>();
//	items.push_back(mckeeman_space());
//	items.push_back(mckeeman_space());
//	items.push_back(mckeeman_space());
//	items.push_back(mckeeman_space());
//	create_alternative(r, std::move(items));
//	return r;
//}
//
//MckeemanNode mckeeman_item(MckeemanNode item) {
//	auto r = MckeemanNode();
//	*name(r) = "item";
//	auto items = std::vector<MckeemanNode>();
//	items.push_back(std::move(item));
//	create_alternative(r, std::move(items));
//	return r;
//}
//
//MckeemanNode mckeeman_item(const std::string& s) {
//	auto r = MckeemanNode();
//	*name(r) = s;
//	return r;
//}
//
//MckeemanNode mckeeman_items(MckeemanNode first_item) {
//	auto r = MckeemanNode();
//	*name(r) = "items";
//	if(!has_next_item(first_item)) {
//		auto items = std::vector<MckeemanNode>();
//		items.push_back(mckeeman_item(std::move(first_item)));
//		create_alternative(r, std::move(items));
//	} else {
//		auto tail = next_item(first_item);
//		first_item.next_item_ = nullptr;
//		auto items = std::vector<MckeemanNode>();
//		items.push_back(mckeeman_item(std::move(first_item)));
//		items.push_back(mckeeman_space());
//		items.push_back(mckeeman_items(std::move(*tail)));
//		create_alternative(r, std::move(items));
//	}
//	return r;
//}
//
//MckeemanNode mckeeman_letter(char c) {
//	auto r = MckeemanNode();
//	*name(r) = "letter";
//	*literal(r) = std::string(1, c);
//	return r;
//}
//
//MckeemanNode mckeeman_name(const std::string& s) {
//	assert(size(s) > 0);
//	auto r = MckeemanNode();
//	*name(r) = "name";
//	*literal(r) = s;
//	return r;
//}
//
//MckeemanNode mckeeman_newline() {
//	auto r = MckeemanNode();
//	*name(r) = "newline";
//	*literal(r) = "\n";
//	return r;
//}
//
//MckeemanNode mckeeman_nothing(
//	bool does_accept_nothing)
//{
//	auto r = MckeemanNode();
//	*name(r) = "nothing";
//	if(does_accept_nothing) {
//		auto items = std::vector<MckeemanNode>();
//		items.push_back(mckeeman_indentation());
//		items.push_back(mckeeman_singleton('"'));
//		items.push_back(mckeeman_singleton('"'));
//		items.push_back(mckeeman_newline());
//		create_alternative(r, std::move(items));
//	}
//	return r;
//}
//
//MckeemanNode mckeeman_range(char lb, char ub) {
//	auto r = MckeemanNode();
//	*name(r) = "range";
//	auto items = std::vector<MckeemanNode>();
//	items.push_back(mckeeman_singleton(lb));
//	items.push_back(mckeeman_space());
//	items.push_back(mckeeman_singleton('.'));
//	items.push_back(mckeeman_space());
//	items.push_back(mckeeman_singleton(ub));
//	create_alternative(r, std::move(items));
//	return r;
//}
//
//MckeemanNode mckeeman_rule(MckeemanNode r)
//{
//	return r;
//}
//
//MckeemanNode mckeeman_rules(std::vector<MckeemanNode> rules) {
//	assert(size(rules) > 0);
//	auto r = MckeemanNode();
//	*name(r) = "rules";
//	if(size(rules) == 1) {
//		auto items = std::vector<MckeemanNode>();
//		items.push_back(mckeeman_rule(std::move(rules[0])));
//		create_alternative(r, std::move(items));
//	} else if(size(rules) > 1) {
//		auto items = std::vector<MckeemanNode>();
//		items.push_back(mckeeman_rule(std::move(rules[0])));
//		items.push_back(mckeeman_rules(popped_front(std::move(rules))));
//		create_alternative(r, std::move(items));
//	}
//	return r;
//}
//
//MckeemanNode mckeeman_singleton(
//	char codepoint)
//{
//	auto r = MckeemanNode();
//	*name(r) = "singleton";
//	auto items = std::vector<MckeemanNode>();
//	items.push_back(mckeeman_codepoint('\''));
//	items.push_back(mckeeman_codepoint(codepoint));
//	items.push_back(mckeeman_codepoint('\''));
//	create_alternative(r, std::move(items));
//	return r;
//}
//
//MckeemanNode mckeeman_space() {
//	auto r = MckeemanNode();
//	*name(r) = "space";
//	*literal(r) = " ";
//	return r;
//}

}