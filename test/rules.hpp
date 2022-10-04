#pragma once

#include "src.hpp"

auto character_rule() -> Rule {
	auto rule = Rule();
	rule.name = "character";
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Literal(RangeExclude(Range(' ', 127), std::vector<Exclude>({Exclude('\"')})))));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
}

auto characters_rule() -> Rule {
	auto rule = Rule();
	rule.name = "characters";
	// Order of alternatives is reversed here.
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Name("character")));
		items.push_back(Item(Name("characters")));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Name("character")));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
}

auto codepoint_rule() -> Rule {
	auto rule = Rule();
	rule.name = "codepoint";
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Literal(Range(' ', 127))));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
}

auto exclude_rule() -> Rule {
	auto rule = Rule();
	rule.name = "exclude";
	rule.does_accept_nothing = true;
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Name("space")));
		items.push_back(Item(Literal(Codepoint('-'))));
		items.push_back(Item(Name("space")));
		items.push_back(Item(Name("singleton")));
		items.push_back(Item(Name("exclude")));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	// Disabled until look-ahead is properly handled.
//	{
//		auto items = std::vector<Item>();
//		items.push_back(Item(Name("space")));
//		items.push_back(Item(Literal(Codepoint('-'))));
//		items.push_back(Item(Name("range")));
//		items.push_back(Item(Name("exclude")));
//		rule.alternatives_.push_back(Alternative(std::move(items)));
//	}
	return rule;
}

auto indentation_rule() -> Rule {
	auto rule = Rule();
	rule.name = "indentation";
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Literal(Codepoint(' '))));
		items.push_back(Item(Literal(Codepoint(' '))));
		items.push_back(Item(Literal(Codepoint(' '))));
		items.push_back(Item(Literal(Codepoint(' '))));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
};

auto item_rule() -> Rule {
	auto rule = Rule();
	rule.name = "item";
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Name("literal")));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Name("name")));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
};

auto items_rule() -> Rule {
	auto rule = Rule();
	rule.name = "items";
	// Wrong order of alternatives.
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Name("item")));
		items.push_back(Item(Name("space")));
		items.push_back(Item(Name("items")));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Name("item")));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
};

auto letter_rule() -> Rule {
	auto rule = Rule();
	rule.name = "letter";
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Literal(Range('a', 'z'))));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Literal(Range('A', 'Z'))));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Literal(Codepoint('_'))));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
}

auto literal_rule() -> Rule {
	auto rule = Rule();
	rule.name = "literal";
	// Order is messed up here.
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Name("range")));
		items.push_back(Item(Name("exclude")));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Name("singleton")));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Literal(Codepoint('\"'))));
		items.push_back(Item(Name("characters")));
		items.push_back(Item(Literal(Codepoint('\"'))));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
}

auto name_rule() -> Rule {
	auto rule = Rule();
	rule.name = "name";
	// Order of alternatives is reversed here.
	{
		auto alternative = Alternative();
		alternative.items_.push_back(Item(Name("letter")));
		alternative.items_.push_back(Item(Name("name")));
		rule.alternatives_.push_back(std::move(alternative));
	}
	{
		auto alternative = Alternative();
		alternative.items_.push_back(Item(Name("letter")));
		rule.alternatives_.push_back(std::move(alternative));
	}
	return rule;
}

auto space_rule() -> Rule {
	auto rule = Rule();
	rule.name = "space";
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Literal(Codepoint(' '))));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
};

auto singleton_rule() -> Rule {
	auto rule = Rule();
	rule.name = "singleton";
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Literal(Codepoint('\''))));
		items.push_back(Item(Name("codepoint")));
		items.push_back(Item(Literal(Codepoint('\''))));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
}

auto newline_rule() -> Rule {
	auto rule = Rule();
	rule.name = "newline";
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Literal(Codepoint('\n'))));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
};

auto range_rule() -> Rule {
	auto rule = Rule();
	rule.name = "range";
	{
		auto items = std::vector<Item>();
		items.push_back(Item(Name("singleton")));
		items.push_back(Item(Name("space")));
		items.push_back(Item(Literal(Codepoint('.'))));
		items.push_back(Item(Name("space")));
		items.push_back(Item(Name("singleton")));
		rule.alternatives_.push_back(Alternative(std::move(items)));
	}
	return rule;
};

auto mckeeman_grammar() -> Grammar {
	auto grammar = Grammar();
	auto add_rule = [&grammar](Rule&& r) {
		grammar.named_rules_.insert({r.name, std::move(r)});
	};
	add_rule(character_rule());
	add_rule(characters_rule());
	add_rule(codepoint_rule());
	add_rule(exclude_rule());
	add_rule(indentation_rule());
	add_rule(item_rule());
	add_rule(items_rule());
	add_rule(letter_rule());
	add_rule(literal_rule());
	add_rule(name_rule());
	add_rule(newline_rule());
	add_rule(range_rule());
	add_rule(singleton_rule());
	add_rule(space_rule());
	return grammar;
}
