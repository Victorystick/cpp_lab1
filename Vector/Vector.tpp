//#include "Vector.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <memory>

template <typename T>
void Vector<T>::init(size_t s) {
	std::allocator<T> _;

	s = s < 2 ? 2 : s;

	// vec = new T[s];
	vec = _.allocate(s);
	cap = s;
}

template <typename T>
void Vector<T>::deinit(T v[]) {
	std::allocator<T> _;

	for (T & t : *this) {
		_.destroy(&t);
	}
}

template <typename T>
void Vector<T>::internal_reset() {
	std::allocator<T> _;

	for (T & t : *this) {
		_.construct(&t);
	}
}

template <typename T>
void Vector<T>::reset() {
	T empty;

	for (T & t : *this) {
		t = empty;
	}
}

template <typename T>
void Vector<T>::set_all(const T & value) {
	for (T & t : *this) {
		t = value;
	}
}

/*
	Sets internal array to a copy of other.
	WARNING! Destroy length and reference to vec.
	Delete contained data before use.
*/
template <typename T>
void Vector<T>::copy(const Vector<T> & other) {
	std::allocator<T> _;

	if (vec != nullptr || other.size() > capacity()) {
		deinit(vec);
		_.deallocate(vec, capacity());
		vec = nullptr;

	} else if (other.size() <= capacity()) {

		if (size() < other.size()) {
			for (size_t i = size(); i < other.size(); ++i) {
				_.construct(&vec[i]);
			}
		} else {
			for (size_t i = other.size(); i < size(); ++i) {
				_.destroy(&vec[i]);
			}
		}
	}

	length = other.length;

	if (vec == nullptr) {
		init(other.cap);
		internal_reset();
	}

	copy_data(other.vec, length);
}

template <typename T>
void Vector<T>::copy_data(const T* other, const size_t end,
	                        const size_t start, const int shift) {
	if (shift > 0) {
		for (size_t i = end - 1; i < end && i >= start; --i) {
			vec[i + shift] = other[i];
		}
	} else {
		for (size_t i = start; i < end; ++i) {
			vec[i + shift] = other[i];
		}
	}
}

template <typename T>
void Vector<T>::is_ok() const {
	static_assert(std::is_move_constructible<T>::value,
		"The T type of Vector<T> must be move constructible.");
	static_assert(std::is_move_assignable<T>::value,
		"The T type of Vector<T> must be move assignable.");
}

// default
template <typename T>
Vector<T>::Vector() : length(0), cap(0), vec(nullptr) {
	is_ok();
}

template <typename T>
Vector<T>::Vector(const size_t s) : length(s) {
	is_ok();

	init(s);
	internal_reset();
}

template <typename T>
Vector<T>::Vector(const size_t s, const T value) : length(s) {
	is_ok();

	init(s);
	internal_reset();
	set_all(value);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> l) {
	is_ok();

	init(l.size());
	length = l.size();
	internal_reset();
	std::copy(l.begin(), l.end(), vec);
}

// copy
template <typename T>
Vector<T>::Vector(const Vector<T> & v) {
	is_ok();

	init(v.size());

	copy(v);
}

// move
template <typename T>
Vector<T>::Vector(Vector<T>&& v) {
	is_ok();

	length = v.length;
	vec = v.vec;
	cap = v.cap;

	v.length = 0;
	v.vec = nullptr;
	v.cap = 0;
}

template <typename T>
Vector<T>::~Vector() {
	if (vec != nullptr) {
		std::allocator<T> _;

		deinit(vec);

		_.deallocate(vec, capacity());
	}
}

template <typename T>
const Vector<T> & Vector<T>::operator=(const Vector<T> & other) {
	if (other.vec != vec) {
		copy(other);
	}

	return *this;
}

template <typename T>
const Vector<T> & Vector<T>::operator=(Vector<T> && other) {
	if (other.vec == vec) {
		return *this;
	}

	this->~Vector();

	length = other.length;
	vec = other.vec;
	cap = other.cap;

	other.vec = nullptr;
	other.length = 0;
	other.cap = 0;

	return *this;
}

template <typename T>
T & Vector<T>::operator[](const size_t index) {
	if (index >= length) {
		throw std::out_of_range ("Vector index is out of bounds.");
	}
	return vec[index];
}

template <typename T>
const T & Vector<T>::operator[](const size_t index) const {
	if (index >= length) {
		throw std::out_of_range ("Vector index is out of bounds.");
	}
	return vec[index];
}

template <typename T>
void Vector<T>::push_back(const T val) {
	if (length >= cap) {
		more_memory();
	}

	std::allocator<T> _;

	_.construct(&vec[length]);
	vec[length] = val;

	++length;
}

template <typename T>
void Vector<T>::more_memory() {
	size_t old_cap = capacity();

	if (capacity() < 2) {
		cap = 2; // 1.6 * 0 == 0. Not what we want.
		// floor(1.6 * 1) == 1. Stuck on cap==1.
	}

	T* other = vec;

	init((size_t)((double)capacity() * 1.6));

	if (other != nullptr) {
		std::allocator<T> _;

		internal_reset();

		copy_data(other, length);

		deinit(other);
		_.deallocate(other, old_cap);
	}
}

template <typename T>
void Vector<T>::clear() {
	deinit(vec);
	length = 0;
}

template <typename T>
size_t Vector<T>::size() const {
	return length;
}

template <typename T>
size_t Vector<T>::capacity() const {
	return cap;
}

template <typename T>
void Vector<T>::print() const {
	int i = 0;

	for (const T & t : *this) {
		std::clog << i++ << "=" << t << std::endl;
	}
}

template <typename T>
void Vector<T>::insert(const size_t index, const T val) {
	if (index > length) {
		throw std::out_of_range ("Vector index is out of bounds.");
	}

	if (index == length) {
		push_back(val);
		return;
	}

	if (length >= cap) {
		more_memory();
	}

	std::allocator<T> _;
	_.construct(&vec[length]);

	copy_data(vec, length, index, 1);
	vec[index] = val;
	++length;
}

template <typename T>
void Vector<T>::erase(const size_t index) {
	if (index >= length) {
		throw std::out_of_range ("Vector index is out of bounds.");
	}

	std::allocator<T> _;

	--length;

	if (index != length) {
		copy_data(vec, length + 1, index + 1, -1);
	}

	_.destroy(&vec[length]);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
	return vec;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
	return &vec[length];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::find(const T & val) {
	for (auto it = begin(); it != end(); ++it) {
		if (*it == val) {
			return it;
		}
	}

	return end();
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
	return vec;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const {
	return &vec[length];
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::find(const T & val) const{
	for (auto it = begin(); it != end(); ++it) {
		if (*it == val) {
			return it;
		}
	}

	return end();
}

