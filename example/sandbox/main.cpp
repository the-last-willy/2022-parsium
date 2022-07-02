#include <parsium/common/container/tree.hpp>

#include <iostream>

using namespace parsium;

int main() {
	auto tree = parsium::Tree<int>();

	TreeNodePtr<int> node = &tree.construct_root_or(UB, 0);

//	for(int i = 1; i < 4; ++i) {
//		node = &(*node).add_child(i);
//	}
	node = tree.root_or(nullptr);

	std::cout << node->data() << " " << node->child_count() << std::endl;

	node->add_child(1);

	std::cout << node->data() << " " << node->child_count() << std::endl;

	node->add_child(2);

	std::cout << node->data() << " " << node->child_count() << std::endl;

//	for(int i = 0; i < 4; ++i) {
//		std::cout << i << " " << node->child_count() << std::endl;
//
//		node = &node->child_or(UB, 0);
//	}
}
