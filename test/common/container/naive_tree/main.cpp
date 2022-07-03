#include <parsium/common/container/naive_tree.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

using namespace parsium;

TEST_CASE("Binary tree") {
	constexpr auto depth = 2;
	auto tree = NaiveTree<int>();
	{ // Construction.

	}
	SECTION("Validation") {

	}
}

TEST_CASE("Empty tree") {
	auto tree = NaiveTree<int>();
	REQUIRE(!tree.has_root());
}

TEST_CASE("Pair tree") {
	auto tree = NaiveTree<int>();
	{ // Construction.
		auto first = tree.construct_root(1);
		auto second = first->add_child(2);
		{ // Validates first.
			REQUIRE(first->child_count() == 1);
			REQUIRE(*first->data() == 1);
		} { // Validates second.
			REQUIRE(second->child_count() == 0);
			REQUIRE(*second->data() == 2);
		}
	}
	SECTION("Destroy second") {
		auto first = tree.root();
		first->remove_child(0);
		{ // Validates first.
			REQUIRE(first->child_count() == 0);
			REQUIRE(*first->data() == 1);
		}
	}
}

TEST_CASE("Singleton tree") {
	auto data = 123456;
	auto tree = NaiveTree<int>();
	{ // Construction.
		tree.construct_root(data);
	}
	SECTION("Validation") {
		REQUIRE(tree.has_root());
		auto root = tree.root();
		REQUIRE(!root->has_parent());
		REQUIRE(root->child_count() == 0);
		REQUIRE(*root->data() == data);
	}
}

TEST_CASE("Unary tree") {
	constexpr auto depth = 4;
	auto tree = NaiveTree<int>();
	NaiveTreeNode<int>* node = nullptr;
	{ // Constructing the tree.
		node = tree.construct_root(0);
		for(int i = 1; i < depth; ++i) {
			node = node->add_child(i);
			*node->data() = i;
			REQUIRE(node->has_parent());
		}
	} { // Traversing the tree.
		node = tree.root();
		for(int i = 0; i < depth - 1; ++i) {
			REQUIRE(node->child_count() == 1);
			REQUIRE(*node->data() == i);
			node = node->child(0);
		}
		{ // Last node.
			REQUIRE(node->child_count() == 0);
			REQUIRE(*node->data() == depth - 1);
		}
	}

}
