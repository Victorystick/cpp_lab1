/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "test_count_if_followed_by.cpp"

static FitTestSuite suite_FitTestSuite;

static CxxTest::List Tests_FitTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FitTestSuite( "test_count_if_followed_by.cpp", 5, "FitTestSuite", suite_FitTestSuite, Tests_FitTestSuite );

static class TestDescription_FitTestSuite_test_a_is_second_to_last : public CxxTest::RealTestDescription {
public:
 TestDescription_FitTestSuite_test_a_is_second_to_last() : CxxTest::RealTestDescription( Tests_FitTestSuite, suiteDescription_FitTestSuite, 9, "test_a_is_second_to_last" ) {}
 void runTest() { suite_FitTestSuite.test_a_is_second_to_last(); }
} testDescription_FitTestSuite_test_a_is_second_to_last;

static class TestDescription_FitTestSuite_test_a_is_last : public CxxTest::RealTestDescription {
public:
 TestDescription_FitTestSuite_test_a_is_last() : CxxTest::RealTestDescription( Tests_FitTestSuite, suiteDescription_FitTestSuite, 16, "test_a_is_last" ) {}
 void runTest() { suite_FitTestSuite.test_a_is_last(); }
} testDescription_FitTestSuite_test_a_is_last;

static class TestDescription_FitTestSuite_test_a_is_3 : public CxxTest::RealTestDescription {
public:
 TestDescription_FitTestSuite_test_a_is_3() : CxxTest::RealTestDescription( Tests_FitTestSuite, suiteDescription_FitTestSuite, 23, "test_a_is_3" ) {}
 void runTest() { suite_FitTestSuite.test_a_is_3(); }
} testDescription_FitTestSuite_test_a_is_3;

static class TestDescription_FitTestSuite_test_a_is_first : public CxxTest::RealTestDescription {
public:
 TestDescription_FitTestSuite_test_a_is_first() : CxxTest::RealTestDescription( Tests_FitTestSuite, suiteDescription_FitTestSuite, 30, "test_a_is_first" ) {}
 void runTest() { suite_FitTestSuite.test_a_is_first(); }
} testDescription_FitTestSuite_test_a_is_first;

#include <cxxtest/Root.cpp>
