#include <cxxtest/TestSuite.h>

#include "count_if_followed_by.h"

class FitTestSuite : public CxxTest::TestSuite
{
public:

    void test_a_is_second_to_last( void )
    {
        char vek[] = {'x', 'x', 'a', 'b', 'x'};
        int result = count_if_followed_by(vek, 4, 'a', 'b');
        TS_ASSERT_EQUALS( result, 1 );
    }

    void test_a_is_last( void )
    {
        char vek[] = {'b', 'b', 'a', 'b', 'b'};
        int result = count_if_followed_by(vek, 3, 'a', 'b');
        TS_ASSERT_EQUALS( result, 0 );
    }

    void test_a_is_3( void )
    {
        char vek[] = {'b', 'b', 'a', 'b', 'b', 'b', 'a', 'b'};
        int result = count_if_followed_by(vek, 8, 'b', 'b');
        TS_ASSERT_EQUALS( result, 3 );
    }

    void test_a_is_first( void )
    {
        char vek[] = {'x', 'y', 'z'};
        int result = count_if_followed_by(vek, 3, 'x', 'y');
        TS_ASSERT_EQUALS( result, 1 );
    }
};
