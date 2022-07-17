#pragma once

#include "parsing_tree.hpp"

#include <cassert>
#include <string>

namespace parsium {

////////////////////////////////////////////////////////////////////////////////
// Helpers.

template<typename T>
std::vector<T> popped_front(std::vector<T> v) {
	if(!v.empty()) {
		v.erase(begin(v));
	}
	return v;
}

////////////////////////////////////////////////////////////////////////////////

MckeemanRule mckeeman_grammar();

// Rules.

// Instances.

MckeemanRule mckeeman_alternative(const std::vector<MckeemanRule>& items);
MckeemanRule mckeeman_alternatives(const std::vector<MckeemanAlternative>& as);
MckeemanRule mckeeman_codepoint(char c);
MckeemanRule mckeeman_grammar(const std::vector<MckeemanRule>& rules);
MckeemanRule mckeeman_indentation();
MckeemanRule mckeeman_item(const MckeemanRule& item);
MckeemanRule mckeeman_items(const std::vector<MckeemanRule>& items);
MckeemanRule mckeeman_letter(char);
MckeemanRule mckeeman_name(const std::string&);
MckeemanRule mckeeman_newline();
MckeemanRule mckeeman_nothing(bool does_accept_nothing);
MckeemanRule mckeeman_range(char lb, char ub);
MckeemanRule mckeeman_rule(const std::string& name, bool does_accept_nothing, const std::vector<MckeemanAlternative>& alternatives);
MckeemanRule mckeeman_rules(const std::vector<MckeemanRule>& rules);
MckeemanRule mckeeman_singleton(char symbol);
MckeemanRule mckeeman_space();

////////////////////////////////////////////////////////////////////////////////

MckeemanRule mckeeman_alternative(const std::vector<MckeemanRule>& items) {
	auto r = MckeemanRule();
	r.rule_ = "alternative";
	r.alternatives_ = {
		MckeemanAlternative{{
			mckeeman_indentation(),
			mckeeman_items(items),
			mckeeman_newline()
		}}
	};
	return r;
}

MckeemanRule mckeeman_alternatives(const std::vector<MckeemanAlternative>& as) {
	// assert(size(as) > 0);
	auto r = MckeemanRule();
	r.rule_ = "alternatives";
	if(size(as) == 1) {
		r.alternatives_ = {
			MckeemanAlternative{{
				mckeeman_alternative(as[0].items_)
			}}
		};
	} else if(size(as) > 1) {
		r.alternatives_ = {
			MckeemanAlternative{{
				mckeeman_alternative(as[0].items_),
				mckeeman_alternatives(popped_front(as))
			}}
		};
	}
	return r;
}

MckeemanRule mckeeman_codepoint(char c) {
    // Missing second alternative.
	auto r = MckeemanRule();
	r.rule_ = "codepoint";
	r.data_ = std::string(1, c);
	return r;
}

MckeemanRule mckeeman_grammar(const std::vector<MckeemanRule>& rules) {
	auto ret = MckeemanRule();
	ret.rule_ = "grammar";
	ret.alternatives_ = {
		MckeemanAlternative{{
			mckeeman_rules(rules)
		}}
	};
	return ret;
}

MckeemanRule mckeeman_indentation() {
    auto r =  MckeemanRule();
	r.rule_ = "indentation";
    r.alternatives_ = {
		MckeemanAlternative{{
			mckeeman_space(),
			mckeeman_space(),
			mckeeman_space(),
			mckeeman_space()
		}}
    };
	return r;
}

MckeemanRule mckeeman_item(const MckeemanRule& item) {
	auto r = MckeemanRule();
	r.rule_ = "item";
	r.alternatives_ = {
		MckeemanAlternative{{
			item
		}}
	};
	return r;
}

MckeemanRule mckeeman_items(const std::vector<MckeemanRule>& items) {
	assert(size(items) > 0);
	auto r = MckeemanRule();
	r.rule_ = "items";
	if(size(items) == 1) {
		r.alternatives_ = {
			MckeemanAlternative{{
				mckeeman_item(items[0])
			}}
		};
	} else if(size(items) > 1) {
		r.alternatives_ = {
			MckeemanAlternative{{
				mckeeman_item(items[0]),
				mckeeman_space(),
				mckeeman_items(popped_front(items))
			}}
		};
	}
	return r;
}

MckeemanRule mckeeman_letter(char c) {
	auto r = MckeemanRule();
	r.rule_ = "letter";
	r.data_ = std::string(1, c);
	return r;
}

MckeemanRule mckeeman_name(const std::string& s) {
    assert(size(s) > 0);
	auto r = MckeemanRule();
	r.rule_ = "name";
	if constexpr(false) {
		if(size(s) == 1) {
			r.alternatives_ = {
				MckeemanAlternative{{
					mckeeman_letter(s[0])
				}}
			};
		} else {
			r.alternatives_ = {
				MckeemanAlternative{{
					mckeeman_letter(s[0]),
					mckeeman_name(s.substr(1))
				}}
			};
		}
	} else {
		r.data_ = s;
	}
	return r;
}

MckeemanRule mckeeman_newline() {
	auto r = MckeemanRule();
	r.rule_ = "newline";
	r.data_ = "\n";
	return r;
}

MckeemanRule mckeeman_nothing(
    bool does_accept_nothing)
{
	auto r = MckeemanRule();
	r.rule_ = "nothing";
    if(does_accept_nothing) {
		r.alternatives_ = {{{
		   mckeeman_indentation(),
		   mckeeman_singleton('"'),
		   mckeeman_singleton('"'),
		   mckeeman_newline()
	   }}};
    }
	return r;
}

MckeemanRule mckeeman_range(char lb, char ub) {
	auto r = MckeemanRule();
	r.rule_ = "range";
	r.alternatives_ = {
		MckeemanAlternative{{
			mckeeman_singleton(lb),
			mckeeman_space(),
			mckeeman_singleton('.'),
			mckeeman_space(),
			mckeeman_singleton(ub)
		}}
	};
	return r;
}

MckeemanRule mckeeman_rule(const MckeemanRule& r)
{
	return r;
}

MckeemanRule mckeeman_rules(const std::vector<MckeemanRule>& rules) {
	assert(size(rules) > 0);
	auto r = MckeemanRule();
	r.rule_ = "rules";
	if(size(rules) == 1) {
		r.alternatives_ = {
			MckeemanAlternative{{
				mckeeman_rule(rules[0])
			}}
		};
	} else if(size(rules) > 1) {
		r.alternatives_ = {{{
			mckeeman_rule(rules[0]),
			mckeeman_rules(popped_front(rules))
		}}};
	}
	return r;
}

MckeemanRule mckeeman_singleton(
    char codepoint)
{
	auto r = MckeemanRule();
	r.rule_ = "singleton";
	r.alternatives_ = {
		MckeemanAlternative{{
			mckeeman_codepoint('\''),
			mckeeman_codepoint(codepoint),
			mckeeman_codepoint('\'')
		}}
	};
	return r;
}

MckeemanRule mckeeman_space() {
	auto r = MckeemanRule();
	r.rule_ = "space";
	r.data_ = " ";
	return r;
}

}