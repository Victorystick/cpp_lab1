#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

#include "Matrix.h"
#include "/info/cprog09/cxxtest/cxxtest/TestSuite.h"
#include <fstream>
#include <sstream>
#include <climits>

bool operator==(const Matrix & a, const Matrix & b) {
    if (a.rows() != b.rows() || a.cols() != b.cols() ) return false;
    for (int i = 0; i < a.cols(); ++i) {
        for (int j = 0; j < a.rows(); ++j) {
            if (a[i][j] != b[i][j]) return false;
        }
    }

    return true;
}

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
    void testIdentityConstructor() {
        Matrix m (3);

        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( m[ 0 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 1 );
        TS_ASSERT_EQUALS( m[ 1 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( m[ 2 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 2 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( m[ 2 ][ 2 ], 1 );

        TS_ASSERT_THROWS( m[ -1 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 0 ][ -1 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 3 ][ 0 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 0 ][ 3 ], std::out_of_range);
    }

    void testIndexOperator() {
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

        TS_ASSERT_THROWS( m[ 2 ][ 0 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 0 ][ 3 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 2 ][ 3 ], std::out_of_range);

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

    void testStreamInOperator() {
        Matrix m(3,2);
        std::stringstream s("  [ 99 -34 ; 0 2 ; 78 32]");
        s >> m;

        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 99 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], -34 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 2 );
        TS_ASSERT_EQUALS( m[ 2 ][ 0 ], 78 );
        TS_ASSERT_EQUALS( m[ 2 ][ 1 ], 32 );
    }

    void testStreamOperator() {
        const char * init_string = "[ 1 2 \n; 3 4 ]";
        Matrix m;
        init_matrix(m, init_string);

        std::stringstream ss;

        ss << m;

        TS_ASSERT_EQUALS(ss.str(), init_string);
    }

    void testAdd() {
        Matrix m = a_matrix_3by2();
        Matrix n;
        stringstream(" [ 99 -34 0 ; 2 78 32 ] ") >> n;

        Matrix o = m + n;
        Matrix p = n + m;
        TS_ASSERT_EQUALS(o, p);

        TS_ASSERT_EQUALS( o[ 0 ][ 0 ], 100 );
        TS_ASSERT_EQUALS( o[ 0 ][ 1 ], -31 );
        TS_ASSERT_EQUALS( o[ 0 ][ 2 ], 5 );
        TS_ASSERT_EQUALS( o[ 2 ][ 1 ], 2 );
        TS_ASSERT_EQUALS( o[ 2 ][ 0 ], 80 );
        TS_ASSERT_EQUALS( o[ 2 ][ 2 ], 32 );
    }

    void testSub() {
        Matrix m = a_matrix_3by2();
        Matrix n;
        stringstream(" [ -99 +34 0 ; -2 -78 -32 ] ") >> n;

        Matrix o = m + n;
        Matrix p = n + m;
        TS_ASSERT_EQUALS(o, p);

        TS_ASSERT_EQUALS( o[ 0 ][ 0 ], 100 );
        TS_ASSERT_EQUALS( o[ 0 ][ 1 ], -31 );
        TS_ASSERT_EQUALS( o[ 0 ][ 2 ], 5 );
        TS_ASSERT_EQUALS( o[ 2 ][ 1 ], 2 );
        TS_ASSERT_EQUALS( o[ 2 ][ 0 ], 80 );
        TS_ASSERT_EQUALS( o[ 2 ][ 2 ], 32 );
    }
};

#endif
