#include <parsium/json/building.hpp>
#include <parsium/json/formatting.hpp>

#include <iostream>

using namespace parsium;
using namespace parsium::json;
using namespace parsium::json::building;

int main() {
	auto json = Json();
	auto& array = json.create<Array>();
	for(int i = 0; i < 5; ++i) {
		auto& element = array.create_at_end();
		auto& number = element.construct<Number>();
		number = float(i);
	}

	auto formatter = formatting::Formatter();
	format(formatter, json);
	std::cout << formatter.string.str() << std::endl;
}
