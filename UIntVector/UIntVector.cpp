#include <cstdlib>
#include <stdexcept> // Exceptions
#include "UIntVector.hpp"

void UIntVector::init(const size_t s) {
	length = s;

	vec = new unsigned int[s];

	reset();
}

void UIntVector::reset() {
	for (size_t i = 0; i < length; ++i) {
		vec[i] = 0;
	}
}

/*
	Sets internal array to a copy of other.
	WARNING! destroys length and reference to vec.
	Delete contained data before use.
*/
void UIntVector::copy(const UIntVector & other) {
	length = other.length;
	vec = new unsigned int[length];

	for (size_t i = 0; i < length; ++i) {
		vec[i] = other.vec[i];
	}
}

// default
UIntVector::UIntVector() {
	init(0);
}

UIntVector::UIntVector(const size_t s) {
	init(s);
}

// initializer_list
UIntVector::UIntVector(std::initializer_list<unsigned int> l) {
	length = l.size();
	vec = new unsigned int[length];
	std::copy(l.begin(), l.end(), vec);
}

// copy
UIntVector::UIntVector(const UIntVector & v) {
	copy(v);
}

// move
UIntVector::UIntVector(UIntVector&& v) {
	length = v.length;
	vec = v.vec;

	v.length = 0;
	v.vec = 0;
}

// destuctor
UIntVector::~UIntVector() {
	delete[] vec;
}

// assignment
const UIntVector & UIntVector::operator=(UIntVector temp) {
	std::swap(length, temp.length);
	std::swap(vec, temp.vec);

	return *this;
}

unsigned int & UIntVector::get(const size_t index) const {
	if (index >= length) {
		throw std::out_of_range ("UIntVector index is out of bounds.");
	}
	return vec[index];
}

unsigned int & UIntVector::operator[](const size_t index) {
	return get(index);
}

unsigned int UIntVector::operator[](const size_t index) const {
	return get(index);
}
