#include <cxxtest/TestSuite.h>
#include <stdexcept>
#include <string>
#include <iostream>

#include "Vector.hpp"

class VectorTestSuite : public CxxTest::TestSuite
{
public:
	void test_three_strings( void )
	{
		Vector<std::string> v({"a", "be", "ce"});
		TS_ASSERT_EQUALS( v[0], "a" );
		TS_ASSERT_EQUALS( v[1], "be" );
		TS_ASSERT_EQUALS( v[2], "ce" );
	}

	void test_zero_initialization( void )
	{
		Vector<int> v(5);
		TS_ASSERT_EQUALS( v[0], 0 );
		TS_ASSERT_EQUALS( v[1], 0 );
		TS_ASSERT_EQUALS( v[2], 0 );
		TS_ASSERT_EQUALS( v[3], 0 );
		TS_ASSERT_EQUALS( v[4], 0 );
	}

	void test_array_assignment( void ) {
		Vector<int> v;
		v = Vector<int>({1,2,5});
		TS_ASSERT_EQUALS(v[0], 1);
		TS_ASSERT_EQUALS(v[1], 2);
		TS_ASSERT_EQUALS(v[2], 5);
	}

	void test_index_operator( void ) {
		Vector<int> v({2, 3, 5, 99, 42, 0, 2}); //Create a array of pre-defined values
		TS_ASSERT_EQUALS( v[0], 2); // Assert index operator can access the values
		TS_ASSERT_EQUALS( v[3], 99);
		TS_ASSERT_THROWS( v[7], std::out_of_range); // And that out of bounds accesses should be punished.
		v[2] = 6; // Attempt to change a value in array
		TS_ASSERT_EQUALS( v[2], 6); // And check that value sticks.
	}

	void test_moving( void ) {
		Vector<int> v({2,3,5,99,42,0,2});
		int * arr = v.vec;

		Vector<int> w(std::move(v));
		//TODO check w have stolen the array from v
		// Includes checking same adress and that v does no longer have access to it.
		TS_ASSERT_EQUALS(w.length, 7)
		TS_ASSERT_EQUALS(w.vec, arr)

		TS_ASSERT_EQUALS(v.length, 0)
		TS_ASSERT_DIFFERS(v.vec, arr)
	}

	void test_copying ( void ) {
		Vector<int> v({2,3,5,99,42,0,2});
		int * arr = v.vec;

		Vector<int> w = v;
		TS_ASSERT_EQUALS(w.length, 7)
		TS_ASSERT_EQUALS(v.length, 7)
		TS_ASSERT_DIFFERS(w.vec, arr)
		TS_ASSERT_EQUALS(v.vec, arr)

		// Verify values
		for (int i=0; i<v.size(); i++) {
			TS_ASSERT_EQUALS(w[i], v[i])
		}
	}

	void test_push_back( void ) {
		Vector<int> v;
		v.push_back(1);
		TS_ASSERT_EQUALS(v.size(), 1)
		TS_ASSERT_EQUALS(v[0], 1)

		v.push_back(2);
		TS_ASSERT_EQUALS(v.size(), 2)
		TS_ASSERT_LESS_THAN_EQUALS(2,v.capacity()) // Capacity invariant holds.
		TS_ASSERT_EQUALS(v[0], 1) // Test old data is still there
		TS_ASSERT_EQUALS(v[1], 2) // Test new data is there

		for (int i = 3; i < 42; i++) {
			v.push_back(i);
			TS_ASSERT_EQUALS(v.size(), i)
			TS_ASSERT_LESS_THAN_EQUALS(i,v.capacity()) // Capacity invariant holds.
			TS_ASSERT_EQUALS(v[i-2], i-1) // Test last data is still there
			TS_ASSERT_EQUALS(v[i-1], i) // Test new data is there
		}

	}

	void test_insert( void ) {
		Vector<int> v({2,3,5});
		TS_ASSERT_EQUALS(v.size(), 3);

		v.insert(3, 6);
		TS_ASSERT_EQUALS(v.size(), 4);

		v.insert(2, 4);
		TS_ASSERT_EQUALS(v.size(), 5);

		v.insert(0, 1);
		TS_ASSERT_EQUALS(v.size(), 6);

		v.insert(0, 0);
		TS_ASSERT_EQUALS(v.size(), 7);

		for (int i = 0; i < v.size(); ++i) {
			TS_ASSERT_EQUALS(v[i], i);
		}
	}

	void test_clear( void ) {
		Vector<int> v({2,3,5,99,42,0,2});
		v.clear();
		TS_ASSERT_EQUALS(v.size(), 0);
		TS_ASSERT_THROWS( v[0], std::out_of_range);
	}

	void test_erase() {
		Vector<int> v({1,2,3,4,5});
		TS_ASSERT_EQUALS(v.size(), 5);

		v.erase(5);
		TS_ASSERT_EQUALS(v.size(), 5);
		TS_ASSERT_EQUALS(v[0], 1);
		TS_ASSERT_EQUALS(v[1], 2);
		TS_ASSERT_EQUALS(v[2], 3);
		TS_ASSERT_EQUALS(v[3], 4);
		TS_ASSERT_EQUALS(v[4], 5);

		{
			Vector<int> w = v;

			w.erase(4);
			TS_ASSERT_EQUALS(w.size(), 4);
			TS_ASSERT_EQUALS(w[0], 1);
			TS_ASSERT_EQUALS(w[1], 2);
			TS_ASSERT_EQUALS(w[2], 3);
			TS_ASSERT_EQUALS(w[3], 4);
		}

		v.erase(2);
		TS_ASSERT_EQUALS(v.size(), 4);
		TS_ASSERT_EQUALS(v[0], 1);
		TS_ASSERT_EQUALS(v[1], 2);
		TS_ASSERT_EQUALS(v[2], 4);
		TS_ASSERT_EQUALS(v[3], 5);

		v.erase(0);
		TS_ASSERT_EQUALS(v.size(), 3);
		TS_ASSERT_EQUALS(v[0], 2);
		TS_ASSERT_EQUALS(v[1], 4);
		TS_ASSERT_EQUALS(v[2], 5);
	}

	void test_size( void ) {
		Vector<int> v({2,3,5,99,42,0,2});
		TS_ASSERT_EQUALS(v.size(), v.length);
		for (int i = 1; i < 42; i++) {
			v.push_back(i);
			TS_ASSERT_EQUALS(v.size(), v.length)
		}
	}

	void test_capacity( void ) {
		//TODO write testcase
		Vector<int> v({2,3,5,99,42,0,2});
		TS_ASSERT_EQUALS(v.capacity(), v.cap);
		for (int i = 1; i < 42; i++) {
			v.push_back(i);
			TS_ASSERT_EQUALS(v.capacity(), v.cap)
		}
	}

	void test_iterator_begin_and_end() {
		Vector<int> v({2,3,5,99,42,0,2});

		int i = 0;
		// for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		for (VectorIterator<int> it = v.begin(); it != v.end(); ++it) {
			TS_ASSERT_EQUALS(*it, v[i]);
			i++;
		}
	}

	void test_begin( void ) {
		Vector<std::string> v({"a", "b", "c"});

		TS_ASSERT_EQUALS(*v.begin(), "a");
	}

	void test_end( void ) {
		Vector<std::string> v({"a", "b", "c"});

		TS_ASSERT_EQUALS(*v.end(), "c");
	}

	void test_find( void ) {
		Vector<int> v({2,3,5,99,42,0,2});
		Vector<int> target({99,42,0,2});

		int i = 0;
		// for (Vector<int>::iterator it = v.find(99); it != v.end(); ++it) {
		for (VectorIterator<int> it = v.find(99); it != v.end(); ++it) {
			TS_ASSERT_EQUALS(*it, target[i++]);
		}

		Vector<std::string> strs({"yo", "mama", "so", "fat"});

		TS_ASSERT_EQUALS(*strs.find("sexy"), "fat");
	}
};
