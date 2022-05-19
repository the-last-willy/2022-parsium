#pragma once

namespace parsium {
namespace common {

struct UndefinedBehaviourTag {};

constexpr auto undefined_behaviour = UndefinedBehaviourTag();

constexpr auto ub = UndefinedBehaviourTag();

}}
