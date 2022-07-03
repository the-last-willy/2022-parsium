#pragma once

#include "parsium/mckeeman/parser/head.hpp"

#include "parsium/mckeeman/builder/alternative.hpp"

#include <parsium/common/container/naive_tree.hpp>

#include <map>
#include <vector>

namespace parsium::mckeeman::parser {

class Cursor2 {
public:
	const builder::Alternative* alternative = nullptr;
	std::size_t item = 0;
};

class Head2 {
public:
	NaiveTree<Cursor2>::MutableNodePtr node_ = nullptr;
	std::size_t character = 0;
};

class MultiHead2 {
public:
	NaiveTree<Cursor2> tree_;
	std::vector<Head2> heads_;

public:
};

}