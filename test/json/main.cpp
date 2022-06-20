#include <parsium/json/building.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using namespace parsium::json::building;

TEST_CASE("Building") {
	auto json = Json();
	SECTION("Creating number") {
		auto& number = json.create<Number>();
		number.assign(1.f);
	}
}


