#include <parsium/common/container/tree.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("Default ctor") {
	parsium::Tree<int>();
}
