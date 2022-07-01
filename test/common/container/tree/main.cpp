#include <parsium/common/container/tree.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using namespace parsium;

TEST_CASE("Simple case: binary tree") {
	auto tree = Tree<int>();

	REQUIRE(!tree.root_or(nullptr));
}

TEST_CASE("Simple case: empty tree") {
	auto tree = Tree<int>();

	REQUIRE(!tree.root_or(nullptr));
}

TEST_CASE("Simple case: root tree") {
	auto data = 123456;
	auto tree = Tree<int>();
	auto root = tree.construct_root_or(UB, data);

	REQUIRE(root.data() == data);
	REQUIRE(root.child_count() == 0);
	REQUIRE(!root.parent_or(nullptr));
}

TEST_CASE("Simple case: unary tree") {
	TreeNodePtr<int> a;
	FakePtr<TreeNodeRef<int>> b = a.f();


//	auto tree = parsium::Tree<int>();
//
//	TreeNodePtr<int> node = &tree.construct_root_or(UB, 0);
//
//	for(int i = 1; i < 4; ++i) {
//		node = &(*node).add_child(i);
//	}
//
//	node = tree.root_or(nullptr);
//
//	for(int i = 0; i < 4; ++i) {
//		REQUIRE(node);
//		// REQUIRE(node->child_count() == (i < 3 ? 1 : 0));
//	}
}
