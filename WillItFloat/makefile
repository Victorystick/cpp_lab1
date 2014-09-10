course_catalog = /info/DD2387/labs
lab = lab1
problem = 0.5_will_it_float

all: count_if_followed_by.o
	@

clean:
	rm *.o

%.cpp:
	cp $(course_catalog)/$(lab)/$(problem)/$*.cpp .

%.h:
	cp $(course_catalog)/$(lab)/$(problem)/$*.h .

%.out: %.cpp
	g++ -g -std=c++0x -Wall $*.cpp -o $*.out

%.o: %.cpp
	g++ -c -std=c++0x $*.cpp

test_%: %.h %.o test_%.cpp
	$(course_catalog)/cxxtest/cxxtestgen.py --error-printer -o testgen_$*.cpp test_$*.cpp
	g++ -o test_$* -I $(course_catalog)/cxxtest/ testgen_$*.cpp $*.o
	./test_$*

valgrind_%: %.cpp %.out
	valgrind --tool=memcheck --leak-check=yes ./$*.out
