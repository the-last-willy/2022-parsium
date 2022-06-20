#include <parsium/json/building.hpp>
#include <parsium/json/formatting.hpp>

#include <iostream>

using namespace parsium;
using namespace parsium::json;
using namespace parsium::json::building;

int main() {
	auto json = Json();
	auto& number = json.create<Number>();
	number.assign(1.f);
	auto formatter = formatting::Formatter();
	format(formatter, number);
	std::cout << formatter.string.str() << std::endl;
}
