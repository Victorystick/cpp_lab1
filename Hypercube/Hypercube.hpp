#ifndef MP_Hypercube
#define MP_Hypercube

template <int Dimension>
class Hypercube<Dimension> : public Vector< Hypercube<Dimension-1> > {};

class Hypercube<1> : private Vector<int> {};

#endif
