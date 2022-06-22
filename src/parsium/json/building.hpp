#pragma once

////////////////////////////////////////////////////////////////////////////////

/**
 * - Store all data in `Json`.
 *
 * - Create handles for each object.
 *
 * - Return handles instead of references.
 *
 * - Have a parent pointer in all elements ?
 * Would that even be useful ?
 */

////////////////////////////////////////////////////////////////////////////////

#include "building/json.hpp"

#include "building/array/at.inl"
#include "building/array/create_at_end.inl"
#include "building/array/elements.inl"
#include "building/array/is_valid.inl"
#include "building/json/is_valid.inl"
#include "building/element/is_valid.inl"
#include "building/member/element.inl"
#include "building/member/is_valid.inl"
#include "building/member/string.inl"
#include "building/number/is_valid.inl"
#include "building/object/is_valid.inl"
#include "building/object/members.inl"
#include "building/string/is_valid.inl"

/*******************************************************************************
// Template file.

#pragma once

#include "parsium/json/building/"

#include <parsium/json/>

#include <parsium/>

namespace parsium {
namespace json {
namespace building {



}}}

*******************************************************************************/
