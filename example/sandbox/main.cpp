#include <parsium/formatting/tree.hpp>
#include <parsium/mckeeman_formatter.hpp>
#include <parsium/parsing_tree.hpp>

#include <iostream>

using namespace parsium;

int main() {
    auto tree = mckeeman_nothing(true);

    auto f = TreeFormatter();
    format(f, tree);
    std::cout << f.string_.str() << std::endl;
}
