#pragma once

#include <memory>
#include <string>

namespace parsium {

struct UnaryPredicate {
	virtual bool evaluate(char symbol) const = 0;
	virtual std::string text(const std::string& symbol) const = 0;
};

struct AndUnaryPredicate {
	std::unique_ptr<UnaryPredicate> left_operand;
	std::unique_ptr<UnaryPredicate> right_predicate;
};

struct EqualUnaryPredicate : public UnaryPredicate {
	char value;

	EqualUnaryPredicate(char c)
	: value(c)
	{}

	bool evaluate(char symbol) const override {
		return symbol == value;
	}

	std::string text(const std::string& symbol) const override {
		return symbol + " == " + std::to_string(value);
	}
};

struct NotUnaryPredicate : public UnaryPredicate {

};

struct RangeUnaryPredicate : public UnaryPredicate {
	char lower_bound;
	char upper_bound;

	bool evaluate(char symbol) const override {
		return symbol >= lower_bound and symbol <= upper_bound;
	}

	std::string text(const std::string& symbol) const override {
		return symbol + " >= " + std::to_string(lower_bound) + " && " + symbol + " >= " + std::to_string(upper_bound);
	}
};

}
