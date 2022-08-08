#pragma once

#include "parsium/mckeeman/kickstarting/instancing.hpp"
#include "parsium/mckeeman/kickstarting/rules.hpp"

#include "parsium/mckeeman/storing/copy.hpp"
#include "parsium/mckeeman/storing/node.hpp"

#include <array>
#include <cassert>
#include <span>
#include <string>
#include <vector>

namespace parsium::mckeeman {

////////////////////////////////////////////////////////////////////////////////

auto mckeeman_grammar() -> StorageNodeHandle;

auto mckeeman_alternative_of(const StorageNode&) -> StorageNodeHandle;
auto mckeeman_alternatives_of(const StorageNode&) -> StorageNodeHandle;
auto mckeeman_grammar_of(std::span<const StorageNodeHandle> rules) -> StorageNodeHandle;
auto mckeeman_item_of(const StorageNode&) -> StorageNodeHandle;
auto mckeeman_items_of(const StorageNode&) -> StorageNodeHandle;
auto mckeeman_literal_of(const StorageNode&) -> StorageNodeHandle;
auto mckeeman_rule_of(const StorageNode&) -> StorageNodeHandle;
auto mckeeman_rules_of(std::span<const StorageNodeHandle> rules) -> StorageNodeHandle;
auto mckeeman_name_of(const StorageNode&) -> StorageNodeHandle;

////////////////////////////////////////////////////////////////////////////////

auto mckeeman_alternative_of(const StorageNode& n) -> StorageNodeHandle {
	auto ret = mckeeman_name("alternative");
	{
		auto items = std::vector<StorageNodeHandle>();
		items.push_back(mckeeman_indentation());
		if(is_alternative(n) && has_child(n)) {
			items.push_back(mckeeman_items_of(*child(n)));
		} else {
			items.push_back(mckeeman_items_of(n));
		}
		items.push_back(mckeeman_newline());
		add_child(*ret, mckeeman_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_alternatives_of(const StorageNode& alternative) -> StorageNodeHandle {
	auto ret = mckeeman_name("alternatives");
	auto child = add_child(*ret, mckeeman_alternative_of(alternative));
	if(is_alternative(alternative) && has_sibling(alternative)) {
		add_sibling(*child, mckeeman_alternatives_of(*sibling(alternative)));
	}
	return ret;
}

auto mckeeman_grammar() -> StorageNodeHandle {
	auto ret = mckeeman_name("grammar");
	{
		auto rules = std::vector<StorageNodeHandle>();
		rules.push_back(mckeeman_grammar_rule());
		rules.push_back(mckeeman_space_rule());
		rules.push_back(mckeeman_newline_rule());
		rules.push_back(mckeeman_name_rule());
		rules.push_back(mckeeman_letter_rule());
		add_child(*ret, mckeeman_rules(std::move(rules)));
	}
	return ret;
}

auto mckeeman_grammar_of(std::span<const StorageNodeHandle> rules) -> StorageNodeHandle {
	auto ret = std::make_unique<StorageNode>("grammar");
	{
		add_child(*ret, mckeeman_rules_of(rules));
	}
	return ret;
}

auto mckeeman_item_of(const StorageNode& n) -> StorageNodeHandle {
	auto ret = mckeeman_name("item");
	if(has_name(n)) {
		add_child(*ret, mckeeman_name_of(n));
	} else {
		add_child(*ret, mckeeman_literal_of(n));
	}
	return ret;
}

auto mckeeman_items_of(const StorageNode& n) -> StorageNodeHandle {
	auto ret = mckeeman_name("items");
	{
		auto items = std::vector<StorageNodeHandle>();
		items.push_back(mckeeman_item_of(n));
		if(has_sibling(n)) {
			items.push_back(mckeeman_space());
			items.push_back(mckeeman_items_of(*sibling(n)));
		}
		add_child(*ret, mckeeman_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_literal_of(const StorageNode& n) -> StorageNodeHandle {
	auto ret = mckeeman_name("literal");
	add_child(*ret, copy(n));
	return ret;
}

auto mckeeman_name_of(const StorageNode& n) -> StorageNodeHandle {
	assert(is_name(n));
	return std::make_unique<StorageNode>("name", *name(n));
}

auto mckeeman_rule_of(const StorageNode& instance) -> StorageNodeHandle {
	auto ret = mckeeman_name("rule");
	{
		auto items = std::vector<StorageNodeHandle>();
		items.push_back(mckeeman_name_of(instance));
		items.push_back(mckeeman_newline());
		items.push_back(mckeeman_nothing(false));
		if(has_child(instance)) {
			items.push_back(mckeeman_alternatives_of(*child(instance)));
		}
		add_child(*ret, mckeeman_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_rules_of(std::span<const StorageNodeHandle> rules) -> StorageNodeHandle {
	assert(!rules.empty());
	auto ret = std::make_unique<StorageNode>("rules");
	{
		auto items = std::vector<StorageNodeHandle>();
		items.push_back(mckeeman_rule_of(*rules[0]));
		if(size(rules) > 1) {
			items.push_back(mckeeman_newline());
			items.push_back(mckeeman_rules_of(rules.subspan<1>()));
		}
		add_child(*ret, mckeeman_alternative(std::move(items)));
	}
	return ret;
}

}
