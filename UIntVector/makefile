TARGET = UIntVector
CXX = g++
CXXSTD = c++0x
CXXFLAGS = -std=$(CXXSTD) -g -Wall -o $@

course_catalog = /info/DD2387/labs
lab = lab1
problem = 0.6_the_simple_container

all: compile test;

compile: $(TARGET).o;

test: cxxtest test_$(TARGET)_gen.cpp $(TARGET).hpp $(TARGET).o test_$(TARGET).cpp
	$(CXX) -o $@_$(TARGET).out -std=$(CXXSTD) -I $(course_catalog)/cxxtest/ $@_$(TARGET)_gen.cpp $(TARGET).o
	./$@_$(TARGET).out

clean:
	rm *.o *.exe *_gen.cpp *.out *~

test_$(TARGET)_gen.cpp: cxxtest $(TARGET).hpp test_$(TARGET).cpp
	$(course_catalog)/cxxtest/cxxtestgen.py --error-printer -o $@ test_$(TARGET).cpp

test_vec.out: test_vec.cpp $(TARGET).hpp $(TARGET).o
	$(CXX) $(CXXFLAGS) $*.cpp ./$(TARGET).o

%.cpp:
	cp $(course_catalog)/$(lab)/$(problem)/$@ .

%.h:
	cp $(course_catalog)/$(lab)/$(problem)/$*.h .

cxxtest:
	cp -R $(course_catalog)/cxxtest/ .

%.out: %.cpp
	$(CXX) $(CXXFLAGS) $*.cpp

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $*.cpp
