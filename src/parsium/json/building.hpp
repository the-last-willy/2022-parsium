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

#include "parsium/json/building/json.hpp"

#include "parsium/json/building/array/at.inl"
#include "parsium/json/building/array/create_at_end.inl"
#include "parsium/json/building/array/elements.inl"
#include "parsium/json/building/array/is_valid.inl"
#include "parsium/json/building/json/is_valid.inl"
#include "parsium/json/building/element/is_valid.inl"
#include "parsium/json/building/member/element.inl"
#include "parsium/json/building/member/is_valid.inl"
#include "parsium/json/building/member/string.inl"
#include "parsium/json/building/number/is_valid.inl"
#include "parsium/json/building/object/create_member_at_end.inl"
#include "parsium/json/building/object/is_valid.inl"
#include "parsium/json/building/object/members.inl"

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
