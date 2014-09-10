#ifndef MP_Vector
#define MP_Vector

#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <stdexcept> // Exceptions
#include <type_traits>

template <class T>
class VectorIterator :
public std::iterator<std::input_iterator_tag, T> {
	T* vec;
public:
	VectorIterator(T* vec);
	VectorIterator(const VectorIterator & it);
	VectorIterator& operator++();
	VectorIterator operator++(int);
	bool operator==(const VectorIterator & other) const;
	bool operator!=(const VectorIterator & other) const;
	T& operator*();
	const T& operator*() const;
};

template <class T>
class Vector {
	private:
		size_t length;
		size_t cap;
		T* vec;

		void init(const size_t);
		void copy(const Vector &);
		void more_memory();
		void copy_data(const size_t, const T*, const size_t = 0, const size_t = 0);
		void is_ok();
		void set_all(const T &);

		/*class RandomAccessVectorIterator : public std::iterator<std::random_access_iterator_tag, T> {

		};*/

		friend class VectorTestSuite;
	public:
		Vector(); //Default
		explicit Vector(const size_t);
		//Explicit or "Vector v = 5;" is valid, but makes little sense when read.
		explicit Vector(std::initializer_list<T>);
		//Does not really need to be explicit.

		// Initial size and value.
		Vector(const size_t, const T);

		/*
			Copy
		*/
		Vector(const Vector &);

		/*
			Move
		 */
		Vector(Vector &&);

		// Destructor
		~Vector();

		// Assignment
		const Vector & operator=(Vector temp);

		T & operator[](const size_t);

		T operator[](const size_t) const;

		T & get(const size_t) const;

		void reset();

		void push_back(T);

		void insert(std::size_t, T);

		void clear();

		void erase(std::size_t);

		size_t size() const;

		size_t capacity() const;

		VectorIterator<T> begin();

		VectorIterator<T> end();

		VectorIterator<T> find(T const&);

		void print();

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

		// class iterator {
		// 	T* vec;
		// public:
		// 	iterator(T* vec);
		// 	iterator(const T & it);
		// 	iterator& operator++();
		// 	iterator operator++(int);
		// 	bool operator==(const iterator & other) const;
		// 	bool operator!=(const iterator & other) const;
		// 	T& operator*();
		// };
};

#include "Vector.tpp" // Hack for templates

#endif
