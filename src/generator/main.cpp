#include "unary_predicates.hpp"

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <variant>
#include <vector>

using namespace parsium;

enum class FSM_Unspecified {
	bin,
	ignore,
};

struct Transition {
	std::size_t current_state;
	std::size_t next_state;

	std::variant<EqualUnaryPredicate, RangeUnaryPredicate> condition;
};

struct TransitionSet {
	FSM_Unspecified unspecified_behaviour = FSM_Unspecified::bin;

	std::vector<Transition> transitions;
};

struct CharAlphabet {
	std::vector<char> symbols;
};

template<
    typename Alphabet,
	typename State,
	typename TransitionFunction>
struct DFSM_Model {
	Alphabet alphabet;
	std::size_t state_count;
	State initial_state;
	TransitionFunction transition_function;
	std::vector<State> final_states;
};

struct FSM {

};

template<typename... DFSM_Traits>
void generate(const DFSM_Model<DFSM_Traits...>& dfsm, std::ostream& os) {
	os << "#pragma once\n\n";

	os << "#include <common/input_stream/input_stream.hpp>\n\n";

	os << "namespace dfsm {\n\n";

	os << "using namespace parsium::common;\n\n";

	// Forward declare everything.

	for(std::size_t i = 0; i < dfsm.state_count; ++i) {
		os << "bool state_" << i << "_is_accepted(InputStream& is);\n";
	}
	os << "\n";

	// Define everything.

	for(std::size_t i = 0; i < dfsm.state_count; ++i) {
		os << "bool state_" << i << "_is_accepted(InputStream& is) {\n";
		os << "\tif(!is.is_done()) {\n";
		os << "\t\tchar c = get(is);\n";

		for(const auto& t : dfsm.transition_function.transitions) {
			if(t.current_state == i) {
				if(std::holds_alternative<EqualUnaryPredicate>(t.condition)) {
					os << "\t\tif(" << std::get<EqualUnaryPredicate>(t.condition).text("c") << ") {\n";
				} else if(std::holds_alternative<RangeUnaryPredicate>(t.condition)) {
					os << "\t\tif(" << std::get<RangeUnaryPredicate>(t.condition).text("c") << ") {\n";
				}
				os << "\t\t\treturn state_" << t.next_state << "_is_accepted(is);\n";
				os << "\t\t}\n";
			}
		}
		os << "\t\treturn false;\n";

		os << "\t} else {\n";

		bool is_accepting = std::find(begin(dfsm.final_states), end(dfsm.final_states), i) != end(dfsm.final_states);
		os << "\t\treturn " << (is_accepting ? "true" : "false") << ";\n";

		os << "\t}\n";
		os << "}\n\n";
	}
	os << "\n";

	// Accepting function.

	os << "bool is_accepted(InputStream is) {\n";
	os << "\treturn state_" << dfsm.initial_state << "_is_accepted(is);\n";
	os << "}\n\n";

	// Done.

	os << "} // namespace dfsm\n";
}


std::size_t even_number_of_a_transition(std::size_t s, char c) {
	return s;
}

TransitionSet even_a_even_b_even_c() {
	auto transition_set = TransitionSet();

	transition_set.transitions.emplace_back(Transition{0, 1, EqualUnaryPredicate('a')});
	transition_set.transitions.emplace_back(Transition{0, 3, EqualUnaryPredicate('b')});
	transition_set.transitions.emplace_back(Transition{0, 5, EqualUnaryPredicate('c')});
	transition_set.transitions.emplace_back(Transition{1, 0, EqualUnaryPredicate('a')});
	transition_set.transitions.emplace_back(Transition{2, 3, EqualUnaryPredicate('b')});
	transition_set.transitions.emplace_back(Transition{2, 5, EqualUnaryPredicate('c')});
	transition_set.transitions.emplace_back(Transition{3, 2, EqualUnaryPredicate('b')});
	transition_set.transitions.emplace_back(Transition{4, 5, EqualUnaryPredicate('c')});
	transition_set.transitions.emplace_back(Transition{5, 4, EqualUnaryPredicate('c')});

	return transition_set;

//	if(s == 0) {
//		if(c == 'a') {
//			return 1;
//		} else if(c == 'b') {
//			return 3;
//		} else if(c == 'c') {
//			return 5;
//		}
//	} else if(s == 1) {
//		if(c == 'a') {
//			return 0;
//		} else if(c == 'b') {
//			return -1;
//		} else if(c == 'c') {
//			return -1;
//		}
//	} else if(s == 2) {
//		if(c == 'a') {
//			return -1;
//		} else if(c == 'b') {
//			return 3;
//		} else if(c == 'c') {
//			return 5;
//		}
//	} else if(s == 3) {
//		if(c == 'a') {
//			return -1;
//		} else if(c == 'b') {
//			return 2;
//		} else if(c == 'c') {
//			return -1;
//		}
//	} else if(s == 4) {
//		if(c == 'a') {
//			return -1;
//		} else if(c == 'b') {
//			return -1;
//		} else if(c == 'c') {
//			return 5;
//		}
//	} else if(s == 5) {
//		if(c == 'a') {
//			return -1;
//		} else if(c == 'b') {
//			return -1;
//		} else if(c == 'c') {
//			return 4;
//		}
//	}
//	return -1;
}

int main() {
	auto path = std::filesystem::path("D:/dev/project/parser-gen/src/generated/fsm.hpp");
	auto file = std::ofstream(path.c_str());
    auto dfsm = DFSM_Model<CharAlphabet, std::size_t, TransitionSet>{
		CharAlphabet{{'a', 'b', 'c'}},
		6,
		0,
		even_a_even_b_even_c(),
		{0, 2, 4}
	};
	generate(dfsm, file);
}
