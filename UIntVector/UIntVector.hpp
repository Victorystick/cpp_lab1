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
			Copies the elements of the given vector.
		*/
		UIntVector(const UIntVector &);

		/*
			Steals element from given vector.
		 */
		UIntVector(UIntVector &&);

		/*
			Destructor.
			Destroys underlying storage but does not delete contents.
		*/
		~UIntVector();

		// Assignment
		const UIntVector & operator=(const UIntVector & temp);
		const UIntVector & operator=(UIntVector &&);

		/*
			Returns the current number of elements in the vector.
		*/
		size_t size() const { return length; }

		/*
			Sets all elements in the vector to 0.
		*/
		void reset();

		/*
			Element accessor method.
			returns the element at the given position in the vector.
		*/
		unsigned int & get(const size_t) const;

		/*
			Element access operators.
			Equivalent to get() member function.
		*/
		unsigned int & operator[](const size_t);
		unsigned int operator[](const size_t) const;
};
