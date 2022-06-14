#pragma once

namespace parsium {
namespace mckeeman {
namespace builder {

class Alternative;
class Grammar;
class Item;
class Literal;
class Name;
class Rule;

struct Traits {
	using Alternative = Alternative;
	using Grammar = Grammar;
	using Item = Item;
	using Literal = Literal;
	using Name = Name;
	using Rule = Rule;
};

}}}
