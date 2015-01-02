#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

#include "Matrix.h"
#include "/info/cprog09/cxxtest/cxxtest/TestSuite.h"
#include <fstream>
#include <sstream>
#include <climits>

class MatrixTestSuite : public CxxTest::TestSuite
{

    Matrix a_matrix_3by2() {    // [ 1 3 5 ]
        Matrix m;               // [ 0 2 0 ]
        std::stringstream s("  [ 1 3 5 ; 0 2 0 ]");
        s >> m;
        return m;
    }

    void init_matrix( Matrix& m, const char* file )
    {
        std::stringstream stream( file );
        stream >> m;
    }

public:
    void testIndexOperator ( )
    {
        Matrix m( 2, 2 );
        TS_ASSERT( m[ 0 ][ 1 ] == 0 );

        m = a_matrix_3by2();
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 3 );
        TS_ASSERT_EQUALS( m[ 0 ][ 2 ], 5 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 2 );
        TS_ASSERT_EQUALS( m[ 1 ][ 2 ], 0 );

        init_matrix(m, "  [ 1 3 5 ; 0 2 1 ]");
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 3 );
        TS_ASSERT_EQUALS( m[ 0 ][ 2 ], 5 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 2 );
        TS_ASSERT_EQUALS( m[ 1 ][ 2 ], 1 );

        std::stringstream ss;
        ss << m;
        ss >> m;
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 3 );
        TS_ASSERT_EQUALS( m[ 0 ][ 2 ], 5 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 2 );
        TS_ASSERT_EQUALS( m[ 1 ][ 2 ], 1 );

        TS_ASSERT_THROWS( m[-1][0] , std::out_of_range);
        TS_ASSERT_THROWS( m[ 13 ][ 37 ] , std::out_of_range);
    }

    void testOperatorAssign() {
        Matrix m(2,4);
        m[ 0 ][ 0 ] = 99;
        m[ 0 ][ 1 ] = 0;
        m[ 0 ][ 2 ] = INT_MAX;
        m[ 0 ][ 3 ] = 42;

        m[ 1 ][ 0 ] = -99;
        m[ 1 ][ 1 ] = -0;
        m[ 1 ][ 2 ] = INT_MIN;
        m[ 1 ][ 3 ] = -42;

        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 99 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( m[ 0 ][ 2 ], INT_MAX );
        TS_ASSERT_EQUALS( m[ 0 ][ 3 ], 42 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], -99 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 2 ], INT_MIN );
        TS_ASSERT_EQUALS( m[ 1 ][ 3 ], -42 );

        TS_ASSERT_THROWS( m[-1][0] = 1 , std::out_of_range);
        TS_ASSERT_THROWS( m[0][-1] = 4, std::out_of_range);
        TS_ASSERT_THROWS( m[-1][-1] = 1 , std::out_of_range);

        TS_ASSERT_THROWS( m[2][0] = 1 , std::out_of_range);
        TS_ASSERT_THROWS( m[0][4] = 4, std::out_of_range);
        TS_ASSERT_THROWS( m[2][4] = 1 , std::out_of_range);

    }
};

#endif

