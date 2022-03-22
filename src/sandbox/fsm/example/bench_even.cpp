#include <iostream>

namespace v0 {

struct State {
	using transition_function_type = const State& (*)(char);

	bool accepting;
	transition_function_type transition_function;

	State() = default;

	constexpr
	State(transition_function_type fn, bool accepting)
		: accepting(accepting)
		, transition_function(fn)
	{}
};

const State& bin_state();
const State& bin_state_transition(char);
const State& state_0();
const State& state_0_transition(char);
const State& state_1();
const State& state_1_transition(char);

const State& bin_state() {
	static State s(&bin_state_transition, false);
	return s;
}

const State& bin_state_transition(char) {
	return bin_state();
}

const State& state_0() {
	static const State s(&state_0_transition, false);
	return s;
}

const State& state_0_transition(char c) {
	if(c == 'a') {
		return state_0();
	} else if(c == 'b') {
		return state_1();
	} else {
		return bin_state();
	}
}

const State& state_1() {
	static const State s(&state_1_transition, true);
	return s;
}

const State& state_1_transition(char c) {
	if(c == 'a') {
		return state_1();
	} else if(c == 'b') {
		return state_1();
	} else {
		return bin_state();
	}
}

bool accepted(const std::string& s) {
	const State* state = &state_0();
	for(auto c : s) {
		state = &state->transition_function(c);
	}
	return state->accepting;
}

}

namespace v1 {

struct State {
	using transition_function_type = const State& (*)(const char*, const char*);

	bool accepting;
	transition_function_type transition_function;

	State() = default;

	constexpr
	State(transition_function_type fn, bool accepting)
		: accepting(accepting)
		, transition_function(fn)
	{}
};

const State& bin_state();
const State& bin_state_transition(const char* b, const char* e);
const State& state_0();
const State& state_0_transition(const char* b, const char* e);
const State& state_1();
const State& state_1_transition(const char* b, const char* e);

const State& bin_state() {
	static State s(&bin_state_transition, false);
	return s;
}

const State& bin_state_transition(const char* b, const char* e) {
	if(b != e) {
		return bin_state_transition(b + 1, e);
	} else {
		return bin_state();
	}
}

const State& state_0() {
	static const State s(&state_0_transition, false);
	return s;
}

const State& state_0_transition(const char* b, const char* e) {
	if(b != e) {
		auto c = *b;
		if(c == 'a') {
			return state_0_transition(b + 1, e);
		} else if(c == 'b') {
			return state_1_transition(b + 1, e);
		} else {
			return bin_state_transition(b + 1, e);
		}
	} else {
		return state_0();
	}
}

const State& state_1() {
	static const State s(&state_1_transition, true);
	return s;
}

const State& state_1_transition(const char* b, const char* e) {
	if(b != e) {
		auto c = *b;
		if(c == 'a') {
			return state_1_transition(b + 1, e);
		} else if(c == 'b') {
			return state_1_transition(b + 1, e);
		} else {
			return bin_state_transition(b + 1, e);
		}
	} else {
		return state_1();
	}
}

bool accepted(const std::string& s) {
	return state_0_transition(s.c_str(), s.c_str() + size(s)).accepting;
}

}

namespace v2 {

bool accepted(const std::string& s) {
	auto b = s.c_str();
	auto e = b + size(s);

	state0:

	if(b == e) {
		return true;
	} else {
		auto c = *b;
		b++;
		if(c == 'a') {
			goto state1;
		} else if(c == 'b') {
			goto state0;
		} else {
			goto binstate;
		}
	}

	state1:

	if(b == e) {
		return false;
	} else {
		auto c = *b;
		b++;
		if(c == 'a') {
			goto state0;
		} else if(c == 'b') {
			goto state1;
		} else {
			goto binstate;
		}
	}

	binstate:

	if(b == e) {
		return false;
	} else {
		b++;
		goto binstate;
	}
}

}

const std::string& rand_str() {
	static std::string s;
	if(size(s) > 0) {
		return s;
	} else {
		std::srand(time(0));
		for(int i = 0; i < 1000; ++i) {
			s.push_back((std::rand() % 2) ? 'a' : 'b');
		}
		return s;
	}
}

int main() {
	auto s = std::string("a");
	std::cout << v0::accepted(s) << std::endl;
	std::cout << v1::accepted(s) << std::endl;
	std::cout << v2::accepted(s) << std::endl;
}
