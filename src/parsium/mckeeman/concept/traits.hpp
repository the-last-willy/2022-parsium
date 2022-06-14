#pragma once

namespace parsium {
namespace mckeeman {

template<typename T>
using Traits = typename std::remove_cvref_t<T>::Traits;

template<typename T>
concept Traits_ = requires {
	typename T::Alternative;
	typename T::Grammar;
	typename T::Item;
	typename T::Rule;
};

template<Traits_ T>
using Alternative = typename std::remove_cvref_t<T>::Alternative;

template<Traits_ T>
using Item = typename std::remove_cvref_t<T>::Item;

template<Traits_ T>
using Grammar = typename std::remove_cvref_t<T>::Grammar;

template<Traits_ T>
using Literal = typename std::remove_cvref_t<T>::Literal;

template<Traits_ T>
using Name = typename std::remove_cvref_t<T>::Name;

template<Traits_ T>
using Rule = typename std::remove_cvref_t<T>::Rule;

}}
