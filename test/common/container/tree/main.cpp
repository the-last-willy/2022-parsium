#include <parsium/common/container/tree.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("Default ctor") {
	parsium::Tree<int>();
}

TEST_CASE("Empty tree") {
	auto tree = parsium::Tree<int>();
}

TEST_CASE("Root tree") {
	auto tree = parsium::Tree<int>();
	auto root = tree.construct_root_or(parsium::UB, 1);

	SECTION("The root has no parent") {
		REQUIRE(parent_or(root, parsium::self) == root.index())
	}
}

TEST_CASE("Mutable subtree to const subtree conversion") {

}
