#include <parsium/common/container/tree.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("Default ctor") {
	parsium::Tree<int>();
}

TEST_CASE("Empty tree") {
	auto tree = parsium::Tree<int>();

	SECTION("The tree has no root") {
		REQUIRE(!tree.root_or(nullptr));
	}
}

TEST_CASE("Root tree") {
	auto tree = parsium::Tree<int>();
	auto root = tree.construct_root_or(parsium::UB, 1);

	SECTION("The root has no child") {

	}
	SECTION("The root has no parent") {
		REQUIRE(!root.parent_or(nullptr));
	}
}

TEST_CASE("Mutable tree_node to const tree_node conversion") {

}
