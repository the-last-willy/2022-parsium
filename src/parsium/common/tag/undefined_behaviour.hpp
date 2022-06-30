#pragma once

namespace parsium {

/**
 * Should be used to select an overload of which the behaviour is not defined when preconditions are violated.
 *
 * This is useful for performance reasons when preconditions are externally guaranteed (ex: in bounds indices).
 * These should be closely monitored and manually reviewed.
 */
struct {} constexpr UB;

}
