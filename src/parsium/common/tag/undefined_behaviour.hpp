#pragma once

namespace parsium {

struct UndefinedBehaviourTag {};

constexpr auto undefined_behaviour = UndefinedBehaviourTag();

constexpr auto UB = UndefinedBehaviourTag();

}
