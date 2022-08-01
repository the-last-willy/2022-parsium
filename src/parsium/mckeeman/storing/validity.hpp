#pragma once

namespace parsium::mckeeman {

class StorageNode;

auto is_valid(const StorageNode&) -> bool;

//auto are_children_valid(const StorageNode&) -> bool;
//auto are_parents_valid(const StorageNode&) -> bool;
//auto are_siblings_valid(const StorageNode&) -> bool;

auto is_shallowly_valid(const StorageNode&) -> bool;

auto is_alternative_shallowly_valid(const StorageNode&) -> bool;
auto is_item_shallowly_valid(const StorageNode&) -> bool;

}