#ifndef MP_Hypercube
#define MP_Hypercube

#include "../Vector/Vector.hpp"

template <int Dimension>
class Hypercube : public Vector<Hypercube<Dimension-1>> {

public:
	Hypercube<Dimension>(size_t size) : Vector<Hypercube<Dimension-1>>(size, Hypercube<Dimension-1>(size)) {}
	Hypercube<Dimension-1> operator[](size_t i) {
		return Vector<Hypercube<Dimension-1>>::operator[](i);
	}
	const Hypercube<Dimension-1> operator[](size_t i) const {
		return Vector<Hypercube<Dimension-1>>::operator[](i);
	}
};

template <>
class Hypercube<1> : private Vector<int> {};

#endif
