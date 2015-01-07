#ifndef MP_Hypercube
#define MP_Hypercube

#include "../Vector/Vector.hpp"

template <int Dimension>
class Hypercube : private Vector<Hypercube<Dimension-1>> {

public:
	Hypercube() : Vector<Hypercube<Dimension-1>>(0) {}
	Hypercube(size_t size) : Vector<Hypercube<Dimension-1>>(size, Hypercube<Dimension-1>(size)) {}
	Hypercube<Dimension-1> & operator[](size_t i) {
		return Vector<Hypercube<Dimension-1>>::operator[](i);
	}
	const Hypercube<Dimension-1> & operator[](size_t i) const {
		return Vector<Hypercube<Dimension-1>>::operator[](i);
	}
};

template <>
class Hypercube<1> : public Vector<int> {
	public:
		Hypercube() : Vector<int>() {};
		Hypercube(size_t size) : Vector<int>(size) {};
};

#endif
