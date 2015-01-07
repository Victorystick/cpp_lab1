#ifndef MP_Hypercube
#define MP_Hypercube

#include "../Vector/Vector.hpp"

/*
	Defines a N-dimensional cube.
	Each dimension is of same size.
*/
template <int Dimension>
class Hypercube : public Vector<Hypercube<Dimension-1>> {

public:
	//To bad we need a default constructor for our Vector implementation, but what to do...
	Hypercube() : Vector<Hypercube<Dimension-1>>(0) {}

	/*
		Initializes a Hypercube<Dimension> with a given size.
		The resulting cube contains a total of size^Dimension elements.
	*/
	Hypercube(size_t size) : Vector<Hypercube<Dimension-1>>(size, Hypercube<Dimension-1>(size)) {}
};

/*
	Template specialization to handle base-case of 1 dimensional cube.
	Then we wish to inherit from a int vector instead.
*/
template <>
class Hypercube<1> : public Vector<int> {
	public:
		Hypercube() : Vector<int>() {};
		Hypercube(size_t size) : Vector<int>(size) {};
};

#endif
