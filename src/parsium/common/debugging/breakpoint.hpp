#pragma once

/**
 * Only MSVC is currently implemented.
 * On other compilers, it will simply do nothing.
 */

namespace parsium {

/**
 * Triggers a breakpoint if the parameter is `false`.
 * @returns The parameter it was passed.
 */
auto breakpoint_on_false(bool) -> bool;

/**
 * Triggers a breakpoint.
 * @TODO Support Clang and GCC.
 */
void breakpoint();

}
