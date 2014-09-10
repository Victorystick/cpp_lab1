#include <cstdlib>
#include <stdexcept> // Exceptions
#include <type_traits>
#include "Vector.hpp"

template <typename T>
void Vector<T>::init(const size_t s) {
	cap = s;
	vec = new T[s];
}

template <typename T>
void Vector<T>::reset() {
	set_all(T());
}

template <typename T>
void Vector<T>::set_all(const T & value) {
	for (size_t i = 0; i < length; ++i) {
		vec[i] = value;
	}
}

/*
	Sets internal array to a copy of other.
	WARNING! destroys length and reference to vec.
	Delete contained data before use.
*/
template <typename T>
void Vector<T>::copy(const Vector<T> & other) {
	length = other.length;

	if (length > cap) {
		init(length);
	}

	copy_data(length, other.vec);
}

template <typename T>
void Vector<T>::copy_data(size_t length, const T* other) {
	for (size_t i = 0; i < length; ++i) {
		vec[i] = other[i];
	}
}

template <typename T>
void Vector<T>::is_ok() {
	static_assert(std::is_move_constructible<T>::value,
		"The T type of Vector<T> must be move constructible.");
	static_assert(std::is_move_assignable<T>::value,
		"The T type of Vector<T> must be move assignable.");
}

// default
template <typename T>
Vector<T>::Vector() : length(0) {
	is_ok();

	init(16);
}

template <typename T>
Vector<T>::Vector(const size_t s) : length(s) {
	is_ok();

	init(s);
	reset();
}

template <typename T>
Vector<T>::Vector(const size_t s, const T value) : length(s) {
	is_ok();

	init(s);
	set_all(value);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> l) {
	is_ok();

	init(l.size());
	length = cap;
	std::copy(l.begin(), l.end(), vec);
}

// copy
template <typename T>
Vector<T>::Vector(const Vector<T> & v) : cap(0) {
	is_ok();

	copy(v);
}

// move
template <typename T>
Vector<T>::Vector(Vector<T>&& v) {
	is_ok();

	length = v.length;
	vec = v.vec;

	v.length = 0;
	v.vec = 0;
}

template <typename T>
Vector<T>::~Vector() {
	delete[] vec;
}

template <typename T>
const Vector<T> & Vector<T>::operator=(Vector<T> temp) {
	std::swap(length, temp.length);
	std::swap(cap, temp.cap);
	std::swap(vec, temp.vec);

	return *this;
}

template <typename T>
T & Vector<T>::get(const size_t index) const {
	if (index >= length) {
		throw std::out_of_range ("Vector index is out of bounds.");
	}
	return vec[index];
}

template <typename T>
T & Vector<T>::operator[](const size_t index) {
	return get(index);
}

template <typename T>
T Vector<T>::operator[](const size_t index) const {
	return get(index);
}

template <typename T>
void Vector<T>::push_back(const T val) {
	if (length >= cap) {
		if (cap < 2) {
			cap = 2; // 1.6 * 0 == 0. Not what we want.
			// floor(1.6 * 1) == 1. Stuck on cap==1.
		}
		cap = (size_t)((double)cap * 1.6);
		T* other = vec;
		vec = new T [ cap ];
		copy_data(length, other);
		delete[] other;
	}
	vec[length] = val;

	++length;
}

template <typename T>
void Vector<T>::clear() {
	length = 0;
}
