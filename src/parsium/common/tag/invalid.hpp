#pragma once

namespace parsium {

/**
 * Should be used to select an overload that returns an invalid value in case of failure.
 * The function `bool(is_valid(return))` should be a valid expression.
 */
struct {} constexpr invalid;

}
