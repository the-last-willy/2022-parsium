#pragma once

#include "mckeeman_tree.hpp"

namespace parsium {

/**
 * @returns The McKeeman Form grammar tree as if it was parsed by the McKeeman Form itself.
 */
MckeemanRule mckeeman_grammar();

MckeemanRule mckeeman_rule_of(const MckeemanRule&);

MckeemanRule mckeeman_alternative_rule();
MckeemanRule mckeeman_alternatives_rule();
MckeemanRule mckeeman_character_rule();
MckeemanRule mckeeman_characters_rule();
MckeemanRule mckeeman_codepoint_rule();
MckeemanRule mckeeman_exclude_rule();
MckeemanRule mckeeman_grammar_rule();
MckeemanRule mckeeman_hex_rule();
MckeemanRule mckeeman_hexcode_rule();
MckeemanRule mckeeman_indentation_rule();
MckeemanRule mckeeman_item_rule();
MckeemanRule mckeeman_items_rule();
MckeemanRule mckeeman_letter_rule();
MckeemanRule mckeeman_literal_rule();
MckeemanRule mckeeman_name_rule();
MckeemanRule mckeeman_newline_rule();
MckeemanRule mckeeman_nothing_rule();
MckeemanRule mckeeman_range_rule();
MckeemanRule mckeeman_rule_rule();
MckeemanRule mckeeman_rules_rule();
MckeemanRule mckeeman_singleton_rule();
MckeemanRule mckeeman_space_rule();

////////////////////////////////////////////////////////////////////////////////

MckeemanRule mckeeman_grammar() {
	return mckeeman_grammar({
		mckeeman_rule_of(mckeeman_grammar_rule()),
		mckeeman_rule_of(mckeeman_space_rule()),
		mckeeman_rule_of(mckeeman_newline_rule()),
		mckeeman_rule_of(mckeeman_name_rule()),
		mckeeman_rule_of(mckeeman_letter_rule()),
		mckeeman_rule_of(mckeeman_indentation_rule()),
		mckeeman_rule_of(mckeeman_rules_rule()),
		mckeeman_rule_of(mckeeman_rule_rule()),
		mckeeman_rule_of(mckeeman_nothing_rule()),
		mckeeman_rule_of(mckeeman_alternatives_rule()),
		mckeeman_rule_of(mckeeman_alternative_rule()),
		mckeeman_rule_of(mckeeman_items_rule()),
		mckeeman_rule_of(mckeeman_item_rule()),
		mckeeman_rule_of(mckeeman_literal_rule()),
		mckeeman_rule_of(mckeeman_singleton_rule()),
		mckeeman_rule_of(mckeeman_codepoint_rule()),
		mckeeman_rule_of(mckeeman_hexcode_rule()),
		mckeeman_rule_of(mckeeman_hex_rule()),
		mckeeman_rule_of(mckeeman_range_rule()),
		mckeeman_rule_of(mckeeman_exclude_rule()),
		mckeeman_rule_of(mckeeman_characters_rule()),
		mckeeman_rule_of(mckeeman_character_rule())
	});
}

MckeemanRule mckeeman_rule_of(const MckeemanRule& r) {
	bool does_accept_nothing = false;
	auto ret = MckeemanRule();
	ret.rule_ = "rule";
	ret.alternatives_ = {
		MckeemanAlternative{{
			mckeeman_name(r.rule_),
			mckeeman_newline(),
			mckeeman_nothing(does_accept_nothing),
			mckeeman_alternatives(r.alternatives_)
		}}
	};
	return ret;
}

////////////////////////////////////////////////////////////////////////////////

MckeemanRule mckeeman_alternative_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "alternative";
	return ret;
}

MckeemanRule mckeeman_alternatives_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "alternatives";
	return ret;
}

MckeemanRule mckeeman_character_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "character";
	return ret;
}

MckeemanRule mckeeman_characters_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "characters";
	return ret;
}

MckeemanRule mckeeman_codepoint_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "codepoint";
	return ret;
}

MckeemanRule mckeeman_exclude_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "exclude";
	return ret;
}

MckeemanRule mckeeman_grammar_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "grammar";
	ret.alternatives_ = {
		MckeemanAlternative{{
			mckeeman_name("rules")
		}}
	};
	return ret;
}

MckeemanRule mckeeman_hex_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "hex";
	return ret;
}

MckeemanRule mckeeman_hexcode_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "hexcode";
	return ret;
}

MckeemanRule mckeeman_indentation_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "indentation";
	ret.alternatives_ = {
		MckeemanAlternative{{
			mckeeman_space(),
			mckeeman_space(),
			mckeeman_space(),
			mckeeman_space()
		}}
	};
	return ret;
}

MckeemanRule mckeeman_item_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "item";
	return ret;
}

MckeemanRule mckeeman_items_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "items";
	return ret;
}

MckeemanRule mckeeman_letter_rule() {
	// Nothing not handled.
	auto ret = MckeemanRule();
	ret.rule_ = "letter";
	ret.alternatives_ = {
		MckeemanAlternative{{
			mckeeman_range('a', 'z')
		}},
		MckeemanAlternative{{
			mckeeman_range('A', 'Z')
		}},
		MckeemanAlternative{{
			mckeeman_singleton('_')
		}}
	};
	return ret;
}

MckeemanRule mckeeman_literal_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "literal";
	return ret;
}

MckeemanRule mckeeman_name_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "name";
	return ret;
}

MckeemanRule mckeeman_newline_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "newline";
	return ret;
}

MckeemanRule mckeeman_nothing_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "nothing";
	return ret;
}

MckeemanRule mckeeman_range_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "range";
	return ret;
}

MckeemanRule mckeeman_rule_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "rule";
	return ret;
}

MckeemanRule mckeeman_rules_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "rules";
	return ret;
}

MckeemanRule mckeeman_singleton_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "singleton";
	return ret;
}

MckeemanRule mckeeman_space_rule() {
	auto ret = MckeemanRule();
	ret.rule_ = "space";
	ret.alternatives_ = {
		MckeemanAlternative{{
			mckeeman_singleton(' ')
		}}
	};
	return ret;
}

}