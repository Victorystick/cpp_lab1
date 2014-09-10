#include <algorithm>

class UIntVector {
	private:
		size_t length;
		unsigned int* vec;

		void init(const size_t);
		void copy(const UIntVector &);

		friend class UIntVectorTestSuite;
	public:
		UIntVector(); //Default
		explicit UIntVector(const size_t);
		//Explicit or "UIntVector v = 5;" is valid, but makes little sense when read.
		explicit UIntVector(std::initializer_list<unsigned int>);
		//Does not really need to be explicit.

		/*
			Copy
		*/
		UIntVector(const UIntVector &);

		/*
			Move
		 */
		UIntVector(UIntVector &&);

		// Destructor
		~UIntVector();

		// Assignment
		const UIntVector & operator=(UIntVector temp);

		size_t size() const { return length; }

		void reset();

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
		UIntVector(unsigned int (&v)[N]) {
			init(N);
			std::copy(v, v+N, vec);
		}

		unsigned int & get(const size_t) const;
		unsigned int & operator[](const size_t);
		unsigned int operator[](const size_t) const;
};
