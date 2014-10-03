#include <cxxtest/TestSuite.h>
#include <stdexcept>

#include "UIntVector.hpp"

class UIntVectorTestSuite : public CxxTest::TestSuite
{
public:
	void test_zero_initialization( void )
	{
		UIntVector v(5);
		TS_ASSERT_EQUALS( v[0], 0 );
		TS_ASSERT_EQUALS( v[1], 0 );
		TS_ASSERT_EQUALS( v[2], 0 );
		TS_ASSERT_EQUALS( v[3], 0 );
		TS_ASSERT_EQUALS( v[4], 0 );
	}

	void test_array_assignment( void ) {
		UIntVector v;
		v = UIntVector({1,2,5});
		TS_ASSERT_EQUALS(v[0], 1);
		TS_ASSERT_EQUALS(v[1], 2);
		TS_ASSERT_EQUALS(v[2], 5);
	}

	void test_index_operator( void ) {
		//Create a array of pre-defined values
		unsigned int data[]{2, 3, 5, 99, 42, 0, 2};
		UIntVector v(data); // And turn it into a UIntVector
		TS_ASSERT_EQUALS( v[0], 2); // Assert index operator can access the values
		TS_ASSERT_EQUALS( v[3], 99);
		TS_ASSERT_THROWS( v[7], std::out_of_range); // And that out of bounds accesses should be punished.
		v[2] = 6; // Attempt to change a value in array
		TS_ASSERT_EQUALS( v[2], 6); // And check that value sticks.
	}

	void test_moving( void ) {
		UIntVector v({2,3,5,99,42,0,2});
		unsigned int * arr = v.vec;

		UIntVector w(std::move(v));
		//TODO check w have stolen the array from v
		// Includes checking same adress and that v does no longer have access to it.
		TS_ASSERT_EQUALS(w.length, 7)
		TS_ASSERT_EQUALS(w.vec, arr)

		TS_ASSERT_EQUALS(v.length, 0)
		TS_ASSERT_DIFFERS(v.vec, arr)
	}

	void test_copying ( void ) {
		UIntVector v({2,3,5,99,42,0,2});
		unsigned int * arr = v.vec;

		UIntVector w = v;
		TS_ASSERT_EQUALS(w.length, 7)
		TS_ASSERT_EQUALS(v.length, 7)
		TS_ASSERT_DIFFERS(w.vec, arr)
		TS_ASSERT_EQUALS(v.vec, arr)

		// Verify values
		for (int i=0; i<v.size(); i++) {
			TS_ASSERT_EQUALS(w[i], v[i])
		}
	}

	void test_copy_assignment ( void ) {
		UIntVector v({2,3,5,99,42,0,2});
		unsigned int * arr = v.vec;

		UIntVector w;
		w = v; //Copy assignment
		TS_ASSERT_EQUALS(w.length, 7)
		TS_ASSERT_EQUALS(v.length, 7)
		TS_ASSERT_DIFFERS(w.vec, arr)
		TS_ASSERT_EQUALS(v.vec, arr)

		// Verify values
		for (int i=0; i<v.size(); i++) {
			TS_ASSERT_EQUALS(w[i], v[i])
		}
	}

	void test_move_assignment ( void ) {
		UIntVector v({2,3,5,99,42,0,2});
		unsigned int * arr = v.vec;

		UIntVector w;
		w = std::move(v);
		//TODO check w have stolen the array from v
		// Includes checking same adress and that v does no longer have access to it.
		TS_ASSERT_EQUALS(w.length, 7)
		TS_ASSERT_EQUALS(w.vec, arr)

		TS_ASSERT_EQUALS(v.length, 0)
		TS_ASSERT_DIFFERS(v.vec, arr)
	}

	void test_kattis2 ( void ) {
		UIntVector A({1, 2, 3, 4});
		UIntVector B(10);
		TS_ASSERT_EQUALS(A.size(), 4)

		UIntVector C(0);
		C = A;
		A = B;
		UIntVector D = C;

		TS_ASSERT_EQUALS(A.size(), 10)
		TS_ASSERT_EQUALS(B.size(), 10)
		TS_ASSERT_EQUALS(C.size(), 4)

		A[1] = 10;
		B[2] = 11;
		C[3] = 12;

		TS_ASSERT_EQUALS(A[1], 10)
		TS_ASSERT_EQUALS(B[2], 11)
		TS_ASSERT_EQUALS(C[3], 12)

		A.reset();
		TS_ASSERT_EQUALS(A.size(), 10)

		C = std::move(A);

		TS_ASSERT_EQUALS(A.length, 0);
		TS_ASSERT_EQUALS(A.vec, nullptr);
	}
};
