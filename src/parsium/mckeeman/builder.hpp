#pragma once

#include "builder/alternative.hpp"
#include "builder/alternative/items.inl"
#include "builder/grammar.hpp"
#include "builder/grammar/rules.inl"
#include "builder/range_exclude/operator_subtraction.hpp"
#include "builder/rule/alternatives.hpp"
#include "builder/rule/grammar.hpp"
#include "builder/traits.hpp"
#include "concept/grammar/rule.hpp"
#include "concept/grammar.hpp"
#include "concept/name.hpp"
#include "concept/rule.hpp"
#include "concept/traits.hpp"

namespace parsium {
namespace mckeeman {
namespace builder {

static_assert(Grammar_<Grammar>);
static_assert(Name_<Name>);
static_assert(Rule_<Rule>);
static_assert(Traits_<Traits>);

}}}
