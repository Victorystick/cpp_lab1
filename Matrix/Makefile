CXXFLAGS=-std=c++11 -Wall -Wextra -g

# Change these
cxxtestpath = /info/cprog11/cxxtest/
testcode    = example_test.h

all: runtest01 runtest02 runtest03 runtest04 runtest05 runtest06 runtest07 runtest08 runtest09

testcode.cpp: $(testcode)
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

runtest0%: testcode.cpp
	$(CXX) $(CXXFLAGS) -I $(cxxtestpath) -o runtest0$* -DTEST0$* testcode.cpp Matrix0$*.o
	./runtest0$*

runtestown: owntest
	./owntest

Matrix.o: ../Vector/Vector.tpp Matrix.cpp Matrix.h
	$(CXX) $(CXXFLAGS) Matrix.cpp -o Matrix.o -c

owntest: Matrix.o example_test.h testcode.cpp
	$(CXX) $(CXXFLAGS) -I $(cxxtestpath) -o owntest testcode.cpp Matrix.o

clean:
	touch runtest01 testcode.cpp
	rm runtest0* testcode.cpp
