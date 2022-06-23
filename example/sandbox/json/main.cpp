 #include <parsium/json/building.hpp>
 #include <parsium/json/formatting.hpp>

#include <iostream>

using namespace parsium;
using namespace parsium::json;
using namespace parsium::json::building;

int main() {
	auto json = Json();
//	auto& array = json.create<Array>();
//	for(int i = 0; i < 5; ++i) {
//		auto& element = array.create_at_end();
//		auto& number = element.construct<Number>();
//		number = float(i);
//	}
	auto& object = json.create<Object>();
	{
		auto& member = object.create_member_at_end();
		member.string().assign("ok");
		{
			auto& array = member.element().construct<Array>();
			auto& e0 = array.create_at_end();
			e0.construct<Number>().assign(1.f);
			auto& e1 = array.create_at_end();
			e1.construct<String>().assign("nique");
			auto& e2 = array.create_at_end();
			e2.construct<Object>();
			auto& e3 = array.create_at_end();
			e3.construct<Array>();
		}
	}

	auto formatter = formatting::Formatter();
	format(formatter, json);
	std::cout << formatter.string.str() << std::endl;
}
