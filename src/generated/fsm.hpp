#pragma once

#include <common/input_stream/input_stream.hpp>

namespace dfsm {

using namespace parsium::common;

bool state_0_is_accepted(InputStream& is);
bool state_1_is_accepted(InputStream& is);
bool state_2_is_accepted(InputStream& is);
bool state_3_is_accepted(InputStream& is);
bool state_4_is_accepted(InputStream& is);
bool state_5_is_accepted(InputStream& is);

bool state_0_is_accepted(InputStream& is) {
	if(!is.is_done()) {
		char c = is.peek();
		is.advance();
		if(c == 'a') {
			return state_1_is_accepted(is);
		}
		if(c == 'b') {
			return state_3_is_accepted(is);
		}
		if(c == 'c') {
			return state_5_is_accepted(is);
		}
		return false;
	} else {
		return true;
	}
}

bool state_1_is_accepted(InputStream& is) {
	if(!is.is_done()) {
		char c = is.peek();
		is.advance();
		if(c == 'a') {
			return state_0_is_accepted(is);
		}
		return false;
	} else {
		return false;
	}
}

bool state_2_is_accepted(InputStream& is) {
	if(!is.is_done()) {
		char c = is.peek();
		is.advance();
		if(c == 'b') {
			return state_3_is_accepted(is);
		}
		if(c == 'c') {
			return state_5_is_accepted(is);
		}
		return false;
	} else {
		return true;
	}
}

bool state_3_is_accepted(InputStream& is) {
	if(!is.is_done()) {
		char c = is.peek();
		is.advance();
		if(c == 'b') {
			return state_2_is_accepted(is);
		}
		return false;
	} else {
		return false;
	}
}

bool state_4_is_accepted(InputStream& is) {
	if(!is.is_done()) {
		char c = is.peek();
		is.advance();
		if(c == 'c') {
			return state_5_is_accepted(is);
		}
		return false;
	} else {
		return true;
	}
}

bool state_5_is_accepted(InputStream& is) {
	if(!is.is_done()) {
		char c = is.peek();
		is.advance();
		if(c == 'c') {
			return state_4_is_accepted(is);
		}
		return false;
	} else {
		return false;
	}
}


bool is_accepted(InputStream is) {
	return state_0_is_accepted(is);
}

} // namespace dfsm
