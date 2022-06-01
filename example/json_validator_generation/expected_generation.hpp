#pragma once

struct Parser {
	char next_symbol;
	bool is_halted;
};

char discard_next_symbol(Parser& p) {

}

char next_symbol(const Parser& p) {
	return p.next_symbol;
}

bool is_halted(const Parser& p) {
	return p.is_halted;
}

//

bool parse_integer(Parser& p);
bool parse_digits(Parser& p);
bool parse_digit(Parser& p);
bool parse_onenine(Parser& p);
bool parse_zero(Parser& p);

bool parse_integer(Parser& p) {
	if(is_halted(p)) {
		return false;
	} else {
		if(parse_zero(p)) {
			discard_next_symbol(p);
		} else if(next_symbol(p) >= '0' && next_symbol(p) <= '9') {

		} else if(next_symbol(p) == '-') {

		} else {
			return false;
		}
	}
}

bool parse_digits(Parser& p) {
	if(is_halted(p)) {
		return false;
	} else {
		if(parse_zero(p)) {
			return true;
		} else if(parse_onenine(p)) {
			return parse_digits(p);
		} else {
			return false;
		}
	}
}

bool parse_digit(Parser& p) {
	if(is_halted(p)) {
		return false;
	} else {
		if(parse_zero(p)) {
			return true;
		} else if(parse_onenine(p)) {
			return true;
		} else {
			return false;
		}
	}
}

bool parse_onenine(Parser& p) {
	if(is_halted(p)) {
		return false;
	} else {
		if(next_symbol(p) >= '0' && next_symbol(p) <= '9') {
			discard_next_symbol(p);
			return true;
		} else {
			return false;
		}
	}
}

bool parse_zero(Parser& p) {
	if(is_halted(p)) {
		return false;
	} else {
		if(next_symbol(p) == '0') {
			discard_next_symbol(p);
			return true;
		} else {
			return false;
		}
	}
}

int main() {

}
