#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

#include "Matrix.h"
#include "/info/cprog09/cxxtest/cxxtest/TestSuite.h"
#include <fstream>
#include <sstream>
#include <climits>

bool operator==(const Matrix & a, const Matrix & b) {
    if (a.rows() != b.rows() || a.cols() != b.cols() ) return false;
    for (unsigned int i = 0; i < a.cols(); ++i) {
        for (unsigned int j = 0; j < a.rows(); ++j) {
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

        for (unsigned int i = 0; i < size; ++i)
        {
            for (unsigned int j = 0; j < size; ++j)
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
        TS_ASSERT_EQUALS( m.rows(), (std::size_t)3);

        TS_ASSERT_THROWS( m[ -1 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 0 ][ -1 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 3 ][ 0 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 0 ][ 3 ], std::out_of_range);
    }

    void testCopyConstructor() {
        Matrix m (17);

        Matrix n = m;

        TS_ASSERT_EQUALS( n, m );

        Matrix o = a_matrix_3by2();

        Matrix p = o;

        TS_ASSERT_EQUALS( p, o );
        TS_ASSERT_EQUALS( p[0][0], o[0][0] );
    }

    void testCopyAssignment() {
        Matrix m;
        Matrix i ( 2 );

        m = i; // copy-assign

        TS_ASSERT_EQUALS( m, i );

        i = Matrix(3); // copy-assign

        m = i; // copy-assign

        TS_ASSERT_EQUALS( m, i );
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
        TS_ASSERT_THROWS( m[ 2 ][ 0 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 0 ][ 2 ], std::out_of_range);

        m = a_matrix_3by2();
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 3 );
        TS_ASSERT_EQUALS( m[ 0 ][ 2 ], 5 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 2 );
        TS_ASSERT_EQUALS( m[ 1 ][ 2 ], 0 );

        TS_ASSERT_THROWS( m[ 2 ][ 0 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 0 ][ 3 ], std::out_of_range);
        TS_ASSERT_THROWS( m[ 2 ][ 3 ], std::out_of_range);

        init_matrix(m, "  [ 1 3 5 ; 0 2 1 ]");
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 1 );
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

    void testStreamInAndOut() {
        Matrix m;
        init_matrix(m, " [ 1 3 5 ; 0 2 1 ]");
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
        init_matrix(m, "  [ 99 -34 ; 0 2 ; 78 32]");

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

        Matrix n = Matrix(2);
        n[0][1] = INT_MIN + 1;
        n[1][0] = INT_MAX;

        n = -n;

        TS_ASSERT_EQUALS( n[ 0 ][ 1 ], INT_MAX );
        TS_ASSERT_EQUALS( n[ 1 ][ 0 ], INT_MIN + 1 );

        n = -n;

        TS_ASSERT_EQUALS( n[1][0], INT_MAX );
    }

    void testTranspose() {
        Matrix n (2), m = n;
        m.transpose();

        TS_ASSERT_EQUALS( n, m );

        TS_ASSERT_EQUALS( n[ 0 ][ 0 ], m[ 0 ][ 0 ] );
        TS_ASSERT_EQUALS( n[ 0 ][ 1 ], m[ 0 ][ 1 ] );
        TS_ASSERT_EQUALS( n[ 1 ][ 0 ], m[ 1 ][ 0 ] );
        TS_ASSERT_EQUALS( n[ 1 ][ 1 ], m[ 1 ][ 1 ] );

        TS_ASSERT_EQUALS( n.cols(), m.rows() );
        TS_ASSERT_EQUALS( n.rows(), m.cols() );
    }

    void testAdd() {
        Matrix m = a_matrix_3by2();
        Matrix n;
        init_matrix(n, " [ 99 -34 0 ; 2 78 32 ] ");

        Matrix o = m + n;
        Matrix p = n + m;
        TS_ASSERT_EQUALS(o, p);

        TS_ASSERT_EQUALS( o[ 0 ][ 0 ], 100 );
        TS_ASSERT_EQUALS( o[ 0 ][ 1 ], -31 );
        TS_ASSERT_EQUALS( o[ 0 ][ 2 ], 5 );
        TS_ASSERT_EQUALS( o[ 1 ][ 0 ], 2 );
        TS_ASSERT_EQUALS( o[ 1 ][ 1 ], 80 );
        TS_ASSERT_EQUALS( o[ 1 ][ 2 ], 32 );

        TS_ASSERT_EQUALS( p[ 0 ][ 0 ], 100 );
        TS_ASSERT_EQUALS( p[ 0 ][ 1 ], -31 );
        TS_ASSERT_EQUALS( p[ 0 ][ 2 ], 5 );
        TS_ASSERT_EQUALS( p[ 1 ][ 0 ], 2 );
        TS_ASSERT_EQUALS( p[ 1 ][ 1 ], 80 );
        TS_ASSERT_EQUALS( p[ 1 ][ 2 ], 32 );

        //Addition of 0-sized matrix
        Matrix x(0,0);
        TS_ASSERT_THROWS( x + m, std::out_of_range );
        x = x + x;

        //Addition of 1-sized matrix
        x = Matrix(1, 1);
        TS_ASSERT_THROWS( x + m, std::out_of_range);
        x[0][0] = 1;
        x = x + x;
        TS_ASSERT_EQUALS(x[0][0], 2);


        //Addition of square matricies
        x = Matrix(3);

        Matrix z = x + x;
        TS_ASSERT_EQUALS( z[ 0 ][ 0 ], 2 );
        TS_ASSERT_EQUALS( z[ 0 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( z[ 0 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( z[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( z[ 1 ][ 1 ], 2 );
        TS_ASSERT_EQUALS( z[ 1 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( z[ 2 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( z[ 2 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( z[ 2 ][ 2 ], 2 );

        z = z + x;
        TS_ASSERT_EQUALS( z[ 0 ][ 0 ], 3 );
        TS_ASSERT_EQUALS( z[ 0 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( z[ 0 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( z[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( z[ 1 ][ 1 ], 3 );
        TS_ASSERT_EQUALS( z[ 1 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( z[ 2 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( z[ 2 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( z[ 2 ][ 2 ], 3 );

        Matrix i (3);
        Matrix just_1, result;
        std::stringstream ss2(" [ 1 0 0 ; 0 0 0 ; 0 0 0 ]  [ 2 0 0 ; 0 1 0 ; 0 0 1 ] [ 1 0 ; 0 0 ]");
        ss2 >> just_1 >> result;

        TS_ASSERT_EQUALS( i + just_1, result );

        result = i + just_1;

        TS_ASSERT_EQUALS( result[ 0 ][ 0 ], 2 );
        TS_ASSERT_EQUALS( result[ 0 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( result[ 0 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( result[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( result[ 1 ][ 1 ], 1 );
        TS_ASSERT_EQUALS( result[ 1 ][ 2 ], 0 );
        TS_ASSERT_EQUALS( result[ 2 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( result[ 2 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( result[ 2 ][ 2 ], 1 );

        Matrix just_1_2;
        ss2 >> just_1_2;
        i = ones(2);
        result = i + just_1_2;

        TS_ASSERT_EQUALS( result[ 0 ][ 0 ], 2 );
        TS_ASSERT_EQUALS( result[ 0 ][ 1 ], 1 );
        TS_ASSERT_EQUALS( result[ 1 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( result[ 1 ][ 1 ], 1 );

        result = just_1_2 + i;

        TS_ASSERT_EQUALS( result[ 0 ][ 0 ], 2 );
        TS_ASSERT_EQUALS( result[ 0 ][ 1 ], 1 );
        TS_ASSERT_EQUALS( result[ 1 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( result[ 1 ][ 1 ], 1 );
    }

    void testSub() {
        Matrix m = a_matrix_3by2();
        Matrix n;
        init_matrix(n, " [ -99 34 0 ; -2 -78 -32 ] ");

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
        TS_ASSERT_THROWS( x - m, std::out_of_range );
        x = x - x;

        //Subtraction of 1-sized matrix
        x = Matrix(1, 1);
        TS_ASSERT_THROWS( x - m, std::out_of_range );
        x[0][0] = 1;
        x = x - x;
        TS_ASSERT_EQUALS(x, Matrix(1, 1));

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

        ss2 << i;

        TS_ASSERT_EQUALS(ss2.str(), std::string("[ 0 1 1 \n; 1 1 2 \n; 1 2 1 ]"));
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

        m = Matrix(1, 3);
        m[0][0] = 1;
        m[0][1] = 2;
        m[0][2] = 7;

        m = m*9;
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 9 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 18 );
        TS_ASSERT_EQUALS( m[ 0 ][ 2 ], 63 );

        m = Matrix(3,1);
        m[0][0] = 1;
        m[1][0] = 2;
        m[2][0] = 7;

        m = m*9;
        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 9 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 18 );
        TS_ASSERT_EQUALS( m[ 2 ][ 0 ], 63 );

        m = Matrix(0);
        m = m*1;
        TS_ASSERT_THROWS(m[0][0], std::out_of_range);

        m = Matrix(1);
        m = m*1;
        TS_ASSERT_EQUALS(m[0][0], 1);
        TS_ASSERT_THROWS(m[0][1], std::out_of_range);
        TS_ASSERT_THROWS(m[1][0], std::out_of_range);
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
        std::stringstream ss(" [ 99 -1 ; -34 -1 ; 1 -2 ] [ 1 1 1 ; 1 2 2 ; 1 2 2 ]");
        std::stringstream sout;
        ss >> n;

        Matrix o = m * n;

        TS_ASSERT_EQUALS( o[ 0 ][ 0 ], 2 );
        TS_ASSERT_EQUALS( o[ 0 ][ 1 ], -14 );
        TS_ASSERT_EQUALS( o[ 1 ][ 0 ], -68 );
        TS_ASSERT_EQUALS( o[ 1 ][ 1 ], -2 );

        sout << o;

        TS_ASSERT_EQUALS( sout.str(), std::string("[ 2 -14 \n; -68 -2 ]"));

        Matrix p;

        ss >> p;

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

        sout.str(""); // reset
        sout << p;

        TS_ASSERT_EQUALS( sout.str(), std::string("[ 3 5 5 \n; 5 9 9 \n; 5 9 9 ]"));

        Matrix i = ones(2);

        i = i * i;

        TS_ASSERT_EQUALS( i[ 1 ][ 0 ], 2);
    }

    void testMatrix01() {
    #ifdef TEST01
        Matrix m = ones(2), i (2);

        m = (i * 2) - m;

        TS_ASSERT_EQUALS( m[ 0 ][ 0 ],  1 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], -1 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], -1 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ],  1 );
    #endif
    }

    void testMatrix02() {
    #ifdef TEST02
        Matrix m = ones(2), i (2);

        m = m * i;

        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 1 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 1 );
    #endif
    }

    void testMatrix03() {
    #ifdef TEST03
        Matrix m (2), n;

        n = m;

        TS_ASSERT_EQUALS( n[ 0 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( n[ 0 ][ 1 ], 0 );
        TS_ASSERT_EQUALS( n[ 1 ][ 0 ], 0 );
        TS_ASSERT_EQUALS( n[ 1 ][ 1 ], 1 );
    #endif
    }

    /// 4 ....

    void testMatrix05() {
    #ifdef TEST05
        std::stringstream ss;
        Matrix m;

        init_matrix(m, "[ 1 ]");

        ss << m;

        TS_ASSERT_EQUALS( m.cols(), (std::size_t)1 );
        TS_ASSERT_EQUALS( m.rows(), (std::size_t)1 );
        TS_ASSERT_EQUALS( ss.str(), "[ 1 ]" );

        TS_ASSERT_THROWS_NOTHING(
            init_matrix(m, "[ 1 1 1 1 ; 1 1 1 1 ; 1 1 1 1 ; 1 1 1 1 ]") );

        TS_ASSERT_EQUALS( m.cols(), (std::size_t)4 );
        TS_ASSERT_EQUALS( m.rows(), (std::size_t)4 );
    #endif
    }

    void testMatrix06() {
    #ifdef TEST06
        Matrix m = ones(1);

        m.transpose();

        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 1 );
    #endif
    }

    void testMatrix07() {
    #ifdef TEST07
        Matrix m = ones(2), i (2);

        TS_ASSERT_EQUALS( m + i, i );
        TS_ASSERT_EQUALS( i + m, i );
    #endif
    }

    void testMatrix08() {
    #ifdef TEST08
        Matrix m = ones(2), i (2);

        TS_ASSERT_EQUALS( i + m, i );
    #endif
    }

    void testMatrix09() {
    #ifdef TEST09
        // Inverted TEST01
        Matrix m = ones(2), i (2);

        m = (i * 2) - m;

        TS_ASSERT_EQUALS( m[ 0 ][ 0 ],  1 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], -1 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], -1 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ],  1 );

        m = ones(2);

        m = m * i;

        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 1 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 1 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 1 );

        m = ones(2) * 3;
        i = i * 17;

        m = m + i;

        TS_ASSERT_EQUALS( m[ 0 ][ 0 ], 20 );
        TS_ASSERT_EQUALS( m[ 0 ][ 1 ], 3 );
        TS_ASSERT_EQUALS( m[ 1 ][ 0 ], 3 );
        TS_ASSERT_EQUALS( m[ 1 ][ 1 ], 20 );
    #endif
    }

};

#endif

