CXX=g++

# Change these
cxxtestpath = /info/cprog11/cxxtest/
testcode    = example_test.h

all: runtest01 runtest02 runtest04 \
	runtest06 runtest07 runtest08 runtest09

testcode.cpp: $(testcode)
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

runtest0%: testcode.cpp
	$(CXX) -I $(cxxtestpath) -o runtest0$* testcode.cpp Matrix0$*.o
	./runtest0$*

clean:
	touch runtest01 testcode.cpp
	rm runtest0* testcode.cpp
