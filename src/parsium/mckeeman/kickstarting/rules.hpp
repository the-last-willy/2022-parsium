#pragma once

#include "parsium/mckeeman/kickstarting/instancing.hpp"

#include "parsium/mckeeman/storing/node.hpp"

#include <array>
#include <cassert>
#include <span>
#include <string>
#include <vector>

namespace parsium::mckeeman {

auto mckeeman_alternative_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_alternatives_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_character_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_characters_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_codepoint_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_exclude_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_grammar_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_hex_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_hexcode_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_indentation_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_item_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_items_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_letter_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_literal_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_name_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_newline_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_nothing_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_range_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_rule_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_rules_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_singleton_rule() -> std::unique_ptr<StorageNode>;
auto mckeeman_space_rule() -> std::unique_ptr<StorageNode>;

// In the same order they're introduced.
constexpr auto all_mckeeman_rules = std::array{
	&mckeeman_grammar_rule,
	&mckeeman_space_rule,
	&mckeeman_newline_rule,
	&mckeeman_name_rule,
	&mckeeman_letter_rule,
	&mckeeman_indentation_rule,
	&mckeeman_rules_rule,
	&mckeeman_rule_rule,
	&mckeeman_nothing_rule,
	&mckeeman_alternatives_rule,
	&mckeeman_alternative_rule,
	&mckeeman_items_rule,
	&mckeeman_item_rule,
	&mckeeman_literal_rule,
	&mckeeman_singleton_rule,
	&mckeeman_codepoint_rule,
//	&mckeeman_hexcode_rule,
//	&mckeeman_hex_rule,
	&mckeeman_range_rule,
	&mckeeman_exclude_rule,
	&mckeeman_characters_rule,
	&mckeeman_character_rule,
};

////////////////////////////////////////////////////////////////////////////////

auto mckeeman_alternative_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("alternative");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(std::make_unique<StorageNode>("indentation"));
		items.push_back(std::make_unique<StorageNode>("items"));
		items.push_back(std::make_unique<StorageNode>("newline"));
		add_child(*ret, mckeeman_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_alternatives_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("alternatives");
	{
		auto alternatives = std::vector<std::unique_ptr<StorageNode>>();
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("alternative"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("alternative"));
			items.push_back(std::make_unique<StorageNode>("alternatives"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		add_child(*ret, mckeeman_alternatives(std::move(alternatives)));
	}
	return ret;
}

auto mckeeman_character_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("character");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(mckeeman_range(' ', 127));
		items.push_back(mckeeman_exclude(' ', 127));
		add_child(*ret, storage_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_characters_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("characters");
	{
		auto alternatives = std::vector<std::unique_ptr<StorageNode>>();
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("character"));
			alternatives.push_back(storage_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("character"));
			items.push_back(std::make_unique<StorageNode>("characters"));
			alternatives.push_back(storage_alternative(std::move(items)));
		}
		add_child(*ret, storage_alternatives(std::move(alternatives)));
	}
	return ret;
}

auto mckeeman_codepoint_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("codepoint");
	{
		auto alternatives = std::vector<std::unique_ptr<StorageNode>>();
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(mckeeman_range(' ', 127));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("hexcode"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		add_child(*ret, mckeeman_alternatives(std::move(alternatives)));
	}
	return ret;
}

auto mckeeman_exclude_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("exclude");
	{
		auto alternatives = std::vector<std::unique_ptr<StorageNode>>();
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(mckeeman_codepoint('\"'));
			items.push_back(mckeeman_codepoint('\"'));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("space"));
			items.push_back(mckeeman_singleton('-'));
			items.push_back(std::make_unique<StorageNode>("space"));
			items.push_back(std::make_unique<StorageNode>("singleton"));
			items.push_back(std::make_unique<StorageNode>("exclude"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("space"));
			items.push_back(mckeeman_singleton('-'));
			items.push_back(std::make_unique<StorageNode>("space"));
			items.push_back(std::make_unique<StorageNode>("range"));
			items.push_back(std::make_unique<StorageNode>("exclude"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		add_child(*ret, mckeeman_alternatives(std::move(alternatives)));
	}
	return ret;
}

auto mckeeman_grammar_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("grammar");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(std::make_unique<StorageNode>("rules"));
		add_child(*ret, mckeeman_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_hexcode_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("hexcode");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(std::make_unique<StorageNode>("rules"));
		add_child(*ret, mckeeman_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_indentation_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("indentation");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(std::make_unique<StorageNode>("space"));
		items.push_back(std::make_unique<StorageNode>("space"));
		items.push_back(std::make_unique<StorageNode>("space"));
		items.push_back(std::make_unique<StorageNode>("space"));
		add_child(*ret, storage_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_item_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("item");
	{
		auto alternatives = std::vector<std::unique_ptr<StorageNode>>();
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("literal"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("name"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		add_child(*ret, mckeeman_alternatives(std::move(alternatives)));
	}
	return ret;
}

auto mckeeman_items_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("items");
	{
		auto alternatives = std::vector<std::unique_ptr<StorageNode>>();
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("item"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("item"));
			items.push_back(std::make_unique<StorageNode>("space"));
			items.push_back(std::make_unique<StorageNode>("items"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		add_child(*ret, mckeeman_alternatives(std::move(alternatives)));
	}
	return ret;
}

auto mckeeman_letter_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("letter");
	{
		auto alternatives = std::vector<std::unique_ptr<StorageNode>>();
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(mckeeman_range('a', 'z'));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(mckeeman_range('A', 'Z'));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(mckeeman_singleton('_'));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		add_child(*ret, mckeeman_alternatives(std::move(alternatives)));
	}
	return ret;
}

auto mckeeman_literal_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("literal");
	{
		auto alternatives = std::vector<std::unique_ptr<StorageNode>>();
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("singleton"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("range"));
			items.push_back(std::make_unique<StorageNode>("exclude"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(mckeeman_singleton('\"'));
			items.push_back(std::make_unique<StorageNode>("characters"));
			items.push_back(mckeeman_singleton('\"'));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		add_child(*ret, mckeeman_alternatives(std::move(alternatives)));
	}
	return ret;
}

auto mckeeman_name_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("name");
	{
		auto alternatives = std::vector<std::unique_ptr<StorageNode>>();
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("letter"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("letter"));
			items.push_back(std::make_unique<StorageNode>("name"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		add_child(*ret, mckeeman_alternatives(std::move(alternatives)));
	}
	return ret;
}

auto mckeeman_newline_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("newline");
	{
		add_child(*ret, mckeeman_singleton(0x0A));
	}
	return ret;
}

auto mckeeman_nothing_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("nothing");
	{
		auto alternatives = std::vector<std::unique_ptr<StorageNode>>();
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("", "\""));
			items.push_back(std::make_unique<StorageNode>("", "\""));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("indentation"));
			items.push_back(mckeeman_singleton('\"'));
			items.push_back(mckeeman_singleton('\"'));
			items.push_back(std::make_unique<StorageNode>("newline"));
			alternatives.push_back(mckeeman_alternative(std::move(items)));
		}
		add_child(*ret, mckeeman_alternatives(std::move(alternatives)));
	}
	return ret;
}

auto mckeeman_range_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("range");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(std::make_unique<StorageNode>("singleton"));
		items.push_back(std::make_unique<StorageNode>("space"));
		items.push_back(mckeeman_singleton('.'));
		items.push_back(std::make_unique<StorageNode>("space"));
		items.push_back(std::make_unique<StorageNode>("singleton"));
		add_child(*ret, storage_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_rule_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("rule");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(std::make_unique<StorageNode>("name"));
		items.push_back(std::make_unique<StorageNode>("newline"));
		items.push_back(std::make_unique<StorageNode>("nothing"));
		items.push_back(std::make_unique<StorageNode>("alternatives"));
		add_child(*ret, storage_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_rules_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("rules");
	{
		auto alternatives = std::vector<std::unique_ptr<StorageNode>>();
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("rule"));
			alternatives.push_back(storage_alternative(std::move(items)));
		}
		{
			auto items = std::vector<std::unique_ptr<StorageNode>>();
			items.push_back(std::make_unique<StorageNode>("rule"));
			items.push_back(std::make_unique<StorageNode>("newline"));
			items.push_back(std::make_unique<StorageNode>("rules"));
			alternatives.push_back(storage_alternative(std::move(items)));
		}
		add_child(*ret, storage_alternatives(std::move(alternatives)));
	}
	return ret;
}

auto mckeeman_singleton_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("singleton");
	{
		auto items = std::vector<std::unique_ptr<StorageNode>>();
		items.push_back(mckeeman_singleton('\''));
		items.push_back(std::make_unique<StorageNode>("codepoint"));
		items.push_back(mckeeman_singleton('\''));
		add_child(*ret, storage_alternative(std::move(items)));
	}
	return ret;
}

auto mckeeman_space_rule() -> std::unique_ptr<StorageNode> {
	auto ret = std::make_unique<StorageNode>("space");
	{
		add_child(*ret, mckeeman_singleton(0x20));
	}
	return ret;
}

}