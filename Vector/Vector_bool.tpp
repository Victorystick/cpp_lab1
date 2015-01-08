
#define range_check(index, length) if (index >= length) { throw std::out_of_range("Vector index is out of bounds."); }

Vector<bool>::Vector() : len(0), cap(64) {
	data = new uint64_t[1];
}

Vector<bool>::Vector(size_t len) : len(len) {
	cap = (((len - 1) / 64) + 1) * 64;

	data = new uint64_t[cap / 64];
}

Vector<bool>::~Vector() {
	delete[] data;
}

size_t Vector<bool>::size() const {
	return len;
}

size_t Vector<bool>::capacity() const {
	return cap;
}

void Vector<bool>::push_back(bool value) {
	return;
}

Vector<bool>::BoolRef Vector<bool>::operator[](size_t index) {
	range_check(index, len);

	return Vector<bool>::BoolRef(*this, index);
}

bool Vector<bool>::operator[](size_t index) const {
	range_check(index, len);

	return data[index / 64] & (index % 64);
}

bool Vector<bool>::operator==(const Vector<bool> & other) const {
	return data == other.data && len == other.len && cap == other.cap;
}

void Vector<bool>::set_bit(size_t index, bool val) {
	range_check(index, len);

	uint64_t * integer = &data[index / 64];
	index %= 64;

	*integer &= ~(1 << index);
	*integer |= 1 << index;
}

Vector<bool>::const_iterator Vector<bool>::begin() const {
	return Vector<bool>::ConstIterator(*this, 0);
}

Vector<bool>::const_iterator Vector<bool>::end() const {
	return Vector<bool>::ConstIterator(*this, size());
}

Vector<bool>::iterator Vector<bool>::begin() {
	return Vector<bool>::Iterator(*this, 0);
}

Vector<bool>::iterator Vector<bool>::end() {
	return Vector<bool>::Iterator(*this, size());
}
