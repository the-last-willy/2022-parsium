#pragma once

#include "parsium/json/building/member.hpp"
#include "parsium/json/building/object.hpp"

namespace parsium {
namespace json {
namespace building {

inline
const std::vector<Member>& Object::members() const {
	return members_;
}

inline
std::vector<Member>& Object::members() {
	return members_;
}

}}}
