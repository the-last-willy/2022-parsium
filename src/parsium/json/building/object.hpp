#pragma once

#include <parsium/common/tag/shallow.hpp>

#include <vector>

namespace parsium {
namespace json {
namespace building {

class Member;

class Object {
	std::vector<Member> members_;

public:
	auto members() const -> const std::vector<Member>&;
	auto members() -> std::vector<Member>&;

	auto is_valid(decltype(shallow)) const -> bool;

	// Should be a function of members.
	auto create_member_at_end() -> Member&;
};

}}}
