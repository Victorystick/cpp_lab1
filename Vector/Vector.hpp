#ifndef MP_Vector
#define MP_Vector

#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <stdexcept> // Exceptions
#include <type_traits>

/*
Vector class for storing arbitrary type.
*/
template <class T>
class Vector {
	private:
		size_t length;
		size_t cap;
		T* vec;

		void init(size_t);
		void deinit(T v[]);
		void internal_reset();
		void copy(const Vector &);
		void more_memory();
		void copy_data(const T[], const size_t, const size_t = 0, const int = 0);
		void is_ok() const;
		void set_all(const T &);

		void print() const;

		friend class VectorTestSuite;
	public:
		/*
			Initializes a empty vector.
		*/
		Vector(); //Default

		/*
			Initializes a vector of a given length.
			Must be called explicitly since "Vector<int> v = 5;" would otherwise be valid but probably not expected.
		*/
		explicit Vector(const size_t);

		/*
			Initializes a vector with a list of items.
			The resulting size will be the length of the list and the capacity >= the length.
		*/
		Vector(std::initializer_list<T>);

		/*
			Allows initialization using a "template" object.
			The resulting Vector will contain n copies of the second paramenter.
		*/
		Vector(const size_t, const T);

		/*
			Makes a copy of the parameter Vector.
			The elements are copied using the types copy-assign operator.
		*/
		Vector(const Vector &);

		/*
			Steals the elements of the given vector to create a new.
			The resulting elements will have the same elements and the same length and capacity.
		 */
		Vector(Vector &&);

		/*
			Destroys the vector.
			If contents was newed by user, they must first be deleted by user.
		*/
		~Vector();

		/*
			Copies the given vector into this.
			Length, capacity and elements are copied.
		*/
		const Vector<T> & operator=(const Vector<T> & temp);

		/*
			Moves given vectors elements into this.
			Length, capacity and elements are taken.
		*/
		const Vector<T> & operator=(Vector<T> &&);

		/*
			Allows element access through indexing operator
		*/
		T & operator[](const size_t);
		const T & operator[](const size_t) const;

		/*
			Sets all elements of Vector to the contained types default constructor.
		*/
		void reset();

		/*
			Adds a new element to the back to the vector.
		*/
		void push_back(T);

		/*
			Inserts a new element at a given position in the vector.
		*/
		void insert(std::size_t, T);

		/*
			Sets the length of the vector to 0.
		*/
		void clear();

		/*
			Erases the element at the given position in the vector.
		*/
		void erase(std::size_t);

		/*
			Returns the current number of elements stored in the vector.
		*/
		size_t size() const;

		/*
			Returns the maximum number of elements the vector can store before it needs
			to resize its internal storage.
		*/
		size_t capacity() const;

		/// Iterators

		/*
			The type of iterator used for non-const vectors
			Actual type can change in future implementations.
		*/
		typedef T* iterator;

		/*
			The type of iterator used for const vectors.
			Actual type can change in future implementations.
		*/
		typedef const T* const_iterator;

		iterator begin();

		iterator end();

		iterator find(T const&);

		const_iterator begin() const;

		const_iterator end() const;

		const_iterator find(T const&) const;

		/*
			An Array reference keeps the array typing information AND
			can be passed as parameter
			This allows us to define a constructor that actually takes
			an array as its input and constructs from it.

			The template is because like in Go, the array length is part of the type
			So we are creating enough versions of it for all different
			lengths of arrays we use.

			Also, it is located here in the header because any implicit generation
			of templates needs access to the definition
			That means (mostly) the templating information needs to be in the header.
		*/
		template<size_t N>
		Vector(T (&v)[N]) : length(N) {
			init(N);
			std::copy(v, v+N, vec);
		}
};

// Apparently, this is the recomended way of solving issue with requiring implementation to allow implicit generation of templated types.
#include "Vector.tpp"
// #include "Vector_bool.tpp"

#endif
