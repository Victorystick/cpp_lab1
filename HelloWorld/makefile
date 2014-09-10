course_catalog = /info/DD2387/labs/
lab = lab1
problem = 0.2_hello_world

all: hello
	@

test: hello
	$(course_catalog)/$(lab)/$(problem)/hw_verifier hello

clean:
	rm *.o

hello: hello.o
	g++ -g -std=c++0x -Wall main.cpp -o hello hello.o

hello.o: hello.cpp
	g++ -c -std=c++0x hello.cpp
