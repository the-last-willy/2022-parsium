#pragma once

#include "parsium/mckeeman/parser/multi_head.hpp"

#include <parsium/json/building.hpp>

namespace parsium {
namespace mckeeman {
namespace builder {

class JsonListener {
	json::building::Json builder_;
	std::vector<json::building::Element*> stack_;

public:
	void receive(const MultiHead& mh) {}
};

}}}
