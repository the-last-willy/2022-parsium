#pragma once

#include "parsium/mckeeman/builder/item.hpp"

#include <deque>

namespace parsium {
namespace mckeeman {
namespace builder {

class Rule;

/**
 * \section Invariants
 * - `rule_ != nullptr`.
 */
class Alternative {
	Rule* rule_;

	bool does_accept_nothing_ = false;
	std::deque<Item> items_;

public:
	explicit
	Alternative(Rule& rule)
	: rule_(&rule)
	{}

	auto items() const -> const std::deque<Item>&;
	auto items() -> std::deque<Item>&;

	const Rule& rule() const {
		return *rule_;
	}

	Rule& rule() {
		return *rule_;
	}

	//

	Item& add_item(Literal l) {
		return items_.emplace_back(std::move(l));
	}

	Item& add_item(Name n) {
		return items_.emplace_back(std::move(n));
	}

	//

	bool does_accept_nothing() const {
		return does_accept_nothing_;
	}

	void accept_nothing(bool b) {
		does_accept_nothing_ = b;
	}
};

}}}
