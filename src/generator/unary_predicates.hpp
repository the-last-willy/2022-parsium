#pragma once

#include <algorithm>
#include <memory>
#include <string>

namespace parsium {

struct UnaryPredicate {
	virtual ~UnaryPredicate() = default;
	virtual bool evaluate(char symbol) const = 0;
	virtual std::string text(const std::string& symbol) const = 0;
};

struct AndUnaryPredicate : public UnaryPredicate {
	std::unique_ptr<UnaryPredicate> left_operand;
	std::unique_ptr<UnaryPredicate> right_operand;

	AndUnaryPredicate(std::unique_ptr<UnaryPredicate>&& lhs, std::unique_ptr<UnaryPredicate>&& rhs)
		: left_operand(std::move(lhs))
		, right_operand(std::move(rhs))
	{}

	bool evaluate(char symbol) const override {
		return left_operand->evaluate(symbol) and right_operand->evaluate(symbol);
	}

	std::string text(const std::string& symbol) const override {
		return left_operand->text(symbol) + " && " + right_operand->text(symbol);
	}
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

struct InUnaryPredicate : public UnaryPredicate {
	std::vector<char> elements = {};

	InUnaryPredicate(const std::vector<char>& elements)
	: elements(elements)
	{}

	bool evaluate(char symbol) const override {
		return std::find(begin(elements), end(elements), symbol) != end(elements);
	}

	std::string text(const std::string&) const override {
		return "";
	}
};

struct NotUnaryPredicate : public UnaryPredicate {
	std::unique_ptr<UnaryPredicate> operand;

	NotUnaryPredicate(std::unique_ptr<UnaryPredicate>&& op)
	: operand(std::move(op))
	{}

	bool evaluate(char symbol) const override {
		return not operand->evaluate(symbol);
	}

	std::string text(const std::string& symbol) const override {
		return "!" + operand->text(symbol);
	}
};

struct RangeUnaryPredicate : public UnaryPredicate {
	char lower_bound;
	char upper_bound;

	RangeUnaryPredicate(char lb, char ub)
	: lower_bound(lb)
	, upper_bound(ub)
	{}

	bool evaluate(char symbol) const override {
		return symbol >= lower_bound and symbol <= upper_bound;
	}

	std::string text(const std::string& symbol) const override {
		return symbol + " >= " + std::to_string(lower_bound) + " && " + symbol + " >= " + std::to_string(upper_bound);
	}
};

}
