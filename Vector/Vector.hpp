#ifndef MP_Vector
#define MP_Vector

#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <stdexcept> // Exceptions
#include <type_traits>

template <class T>
class Vector {
	private:
		size_t length;
		size_t cap;
		T* vec;

		void init(const size_t);
		void copy(const Vector &);
		void copy_data(size_t, const T*);
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

		size_t size() const { return length; }

		size_t capacity() const { return cap; }

		T* begin();

		T* end();

		T* find(T const&);

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

#include "Vector.tpp" // Hack for templates

#endif
