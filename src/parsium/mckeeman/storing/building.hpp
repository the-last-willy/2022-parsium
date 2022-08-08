#pragma once

#include "parsium/mckeeman/storing/node.hpp"

#include <memory>
#include <vector>

namespace parsium::mckeeman {

auto storage_alternative(StorageNodeHandle&& h) -> StorageNodeHandle {
	auto ret = std::make_unique<StorageNode>();
	add_child(*ret, std::move(h));
	return ret;
}

auto storage_alternative(std::vector<StorageNodeHandle>&& items) -> StorageNodeHandle {
	auto ret = std::unique_ptr<StorageNode>();
	auto it = ret.get();
	auto count = 0;
	for(std::size_t i = 0; i < size(items); ++i) {
		if(items[i] != nullptr) {
			if(count == 0) {
				ret = std::move(items[i]);
				it = ret.get();
			} else {
				it = add_sibling(*it, std::move(items[i]));
			}
			count += 1;
		}
	}
	return ret;
}

auto storage_alternatives(std::vector<StorageNodeHandle>&& nodes) -> StorageNodeHandle {
	auto ret = std::unique_ptr<StorageNode>();
	auto it = ret.get();
	auto count = 0;
	for(std::size_t i = 0; i < size(nodes); ++i) {
		if(nodes[i] != nullptr) {
			if(count == 0) {
				// No need for an alternative node for a single alternative.
				ret = std::move(nodes[i]);
			} else {
				if(count == 1) {
					// Need to add an alternative node for the first node as it was not inserted.
					ret = storage_alternative(std::move(ret));
					it = ret.get();
				}
				it = add_sibling(*it, storage_alternative(std::move(nodes[i])));
			}
			count += 1;
		}
	}
	return ret;
}

}