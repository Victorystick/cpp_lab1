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
            if (a[j][i] != b[j][i]) return false;
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

    Matrix ones(std::size_t size) {
        Matrix m (size, size);

        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                m[i][j] = 1;
            }
        }

        return m;
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

        TS_ASSERT_EQUALS( m.rows(), m.cols());
        TS_ASSERT_EQUALS( m.rows(), 3);

        TS_ASSERT_THROWS( m[ -1 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 0 ][ -1 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 3 ][ 0 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 0 ][ 3 ], std::out_of_range);
    }

    void testCopyConstructor() {
        Matrix m (17);

        Matrix n = m;

        TS_ASSERT_EQUALS( n, m );

        m = a_matrix_3by2();

        n = m;

        TS_ASSERT_EQUALS( n, m );
    }

    void testZeroMatrix() {
        Matrix m (3, 3);
        // m *= 0;

        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( m[ 0 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( m[ 2 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 2 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( m[ 2 ][ 2 ], 0 );
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

    void testNegate() {
        Matrix m = a_matrix_3by2();

        Matrix neg_m = -m;

        TS_ASSERT_EQUALS( neg_m[ 0 ][ 2 ], -m[ 0 ][ 2 ] );
        TS_ASSERT_EQUALS( neg_m[ 0 ][ 1 ], -m[ 0 ][ 1 ] );
        TS_ASSERT_EQUALS( neg_m[ 1 ][ 1 ], -m[ 1 ][ 1 ] );

        Matrix neg_neg_m = -neg_m;

        TS_ASSERT_EQUALS( m, neg_neg_m );
    }

    void testAdd() {
        Matrix m = a_matrix_3by2();
        Matrix n;
        std::stringstream ss(" [ 99 -34 0 ; 2 78 32 ] ");
        ss >> n;

        Matrix o = m + n;
        Matrix p = n + m;
        TS_ASSERT_EQUALS(o, p);

        TS_ASSERT_EQUALS( o[ 0 ][ 0 ], 100 );
        TS_ASSERT_EQUALS( o[ 0 ][ 1 ], -31 );
        TS_ASSERT_EQUALS( o[ 0 ][ 2 ], 5 );
        TS_ASSERT_EQUALS( o[ 1 ][ 0 ], 2 );
        TS_ASSERT_EQUALS( o[ 1 ][ 1 ], 80 );
        TS_ASSERT_EQUALS( o[ 1 ][ 2 ], 32 );

        //Addition of 0-sized matrix
        Matrix x(0,0);
        TS_ASSERT_THROWS( x+m );
        x = x+x;

        //Addition of 1-sized matrix
        x = Matrix(1, 1);
        TS_ASSERT_THROWS(x+m);
        x[0][0] = 1;
        x = x + x;
        TS_ASSERT_EQUALS(x[0][0], 2);


        //Addition of square matricies
        x = Matrix(3);
        y = x;
        y.transpose();

        Matrix z = x+y;
        TS_ASSERT_EQUALS( o[ 0 ][ 0 ], 2 );
        TS_ASSERT_EQUALS( o[ 0 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( o[ 0 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( o[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( o[ 1 ][ 1 ], 2 );
        TS_ASSERT_EQUALS( o[ 1 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( o[ 2 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( o[ 2 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( o[ 2 ][ 2 ], 2 );
    }

    void testSub() {
        Matrix m = a_matrix_3by2(); // "  [ 1 3 5 ; 0 2 0 ]"
        Matrix n;
        std::stringstream ss(" [ -99 34 0 ; -2 -78 -32 ] ");
        ss >> n;

        Matrix o = n - n;

        TS_ASSERT_EQUALS( o, Matrix(2, 3) );

        o = m - n;

        TS_ASSERT_EQUALS( o[ 0 ][ 0 ], 100 );
        TS_ASSERT_EQUALS( o[ 0 ][ 1 ], -31 );
        TS_ASSERT_EQUALS( o[ 0 ][ 2 ], 5 );
        TS_ASSERT_EQUALS( o[ 1 ][ 0 ], 2 );
        TS_ASSERT_EQUALS( o[ 1 ][ 1 ], 80 );
        TS_ASSERT_EQUALS( o[ 1 ][ 2 ], 32 );

        //Subtraction of 0-sized matrix
        Matrix x(0,0);
        TS_ASSERT_THROWS( x+m );
        x = x-x;

        //Subtraction of 1-sized matrix
        x = Matrix(1, 1);
        TS_ASSERT_THROWS(x+m);
        x[0][0] = 1;
        x = x - x;
        TS_ASSERT_EQUALS(x, x(1, 1));

        Matrix i(2);

        i = i - i;

        TS_ASSERT_EQUALS( i, Matrix(2, 2) );

        std::stringstream ss2(" [ 1 1 1 ; 1 2 2 ; 1 2 2 ]");

        i = Matrix(3);

        ss2 >> i;

        i = i - Matrix(3);

        TS_ASSERT_EQUALS( i[ 0 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( i[ 0 ][ 1 ], 1 );
        TS_ASSERT_EQUALS( i[ 0 ][ 2 ], 1 );
        TS_ASSERT_EQUALS( i[ 1 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( i[ 1 ][ 1 ], 1 );
        TS_ASSERT_EQUALS( i[ 1 ][ 2 ], 2 );
        TS_ASSERT_EQUALS( i[ 2 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( i[ 2 ][ 1 ], 2 );
        TS_ASSERT_EQUALS( i[ 2 ][ 2 ], 1 );
    }

    void testScalarMult() {
        Matrix m (2);

        m = m * 3;
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 3 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 3 );

        m = m * 0;
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 0 );

        m Matrix(1,3);
        m[0, 0] = 1;
        m[0, 1] = 2;
        m[0, 2] = 7;

        m = m*9;
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 9 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 18 );
        TS_ASSERT_EQUALS( m[ 0 ][ 2 ], 63 );

        m = Matrix(3,1);
        m[0, 0] = 1;
        m[1, 0] = 2;
        m[2, 0] = 7;

        m = m*9;
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 9 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 18 );
        TS_ASSERT_EQUALS( m[ 2 ][ 0 ], 63 );

        m = Matrix(0)
        m = m*1;
        TS_ASSERT_THROWS(m[0][0]);

        m = Matrix(1)
        m = m*1;
        TS_ASSERT_EQUALS(m[0][0], 1);
        TS_ASSERT_THROWS(m[0][1]);
        TS_ASSERT_THROWS(m[1][0]);
    }

    void testScalarMultAndSub() {
        Matrix m (2);

        m = m * 3;

        m = ones(2) - m;

        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], -2 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 1 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], -2 );
    }

    void testMultiplication() {
        Matrix m = a_matrix_3by2();
        Matrix n;
        std::stringstream ss(" [ 99 -1 ; -34 -1 ; 1 -2 ] ");
        ss >> n;

        Matrix o = m * n;

        TS_ASSERT_EQUALS( o[ 0 ][ 0 ], 2 );
        TS_ASSERT_EQUALS( o[ 0 ][ 1 ], -14 );
        TS_ASSERT_EQUALS( o[ 1 ][ 0 ], -68 );
        TS_ASSERT_EQUALS( o[ 1 ][ 1 ], -2 );

        std::stringstream ss2(" [ 1 1 1 ; 1 2 2 ; 1 2 2 ]");
        Matrix p;

        ss2 >> p;

        p = p * p;

        TS_ASSERT_EQUALS( p[ 0 ][ 0 ], 3 );
        TS_ASSERT_EQUALS( p[ 0 ][ 1 ], 5 );
        TS_ASSERT_EQUALS( p[ 0 ][ 2 ], 5 );
        TS_ASSERT_EQUALS( p[ 1 ][ 0 ], 5 );
        TS_ASSERT_EQUALS( p[ 1 ][ 1 ], 9 );
        TS_ASSERT_EQUALS( p[ 1 ][ 2 ], 9 );
        TS_ASSERT_EQUALS( p[ 2 ][ 0 ], 5 );
        TS_ASSERT_EQUALS( p[ 2 ][ 1 ], 9 );
        TS_ASSERT_EQUALS( p[ 2 ][ 2 ], 9 );

        Matrix i = ones(2);

        i = i * i;

        TS_ASSERT_EQUALS( i[ 1 ][ 0 ], 2);
    }

};

#endif

