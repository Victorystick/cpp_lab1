Matrix flaws
============

* [x] 1: { matrix1 } - { matrix2 } // First row and column are zeroes
* [x] 2: { matrix1 } * { matrix2 } // Last value of first column is 1 too large
* [x] 3: { matrix1 } = { matrix2 } // Copy-assign doubles values
* [ ] 4:
* [x] 5: stream >> { matrix } // Initializes as size 3 identity, and attempts to copy values.
* [x] 6: { matrix }.transpose() // matrix[0][0] was set to 0
* [x] 7: { matrix1 } + { matrix2 } // If one of the elements being added is 0, the result is also 0.
* [x] 8: { matrix1 } + { matrix2 } // If the element of the first matrix is 0, the result is also 0.
* [x] 9: Inverse of 1. Same as 2. { matrix1 } + { matrix2 } // Last value of last column is minimum of elements.


#################################################################
Read and edit makefile. Asign 'testcode' to your tests
in Makefile:
    testcode    = example_test.h

Generate your cxxtest with

 make testcode.cpp

Test Matrix01.o with

 make runtest01

Run the test

 ./runtest01

#################################################################
Compiled on (uname -a):

 Linux share-01.csc.kth.se 3.2.0-53-generic #81-Ubuntu SMP Thu Aug 22 21:01:03 UTC 2013 x86_64 x86_64 x86_64 GNU/Linux

with (gcc --version)

 gcc (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3

reached via

 ssh u-shell.csc.kth.se

result is 64-bit (file Matrix02.o)

 Matrix02.o: ELF 64-bit LSB relocatable, x86-64, version 1 (SYSV), not stripped

for 32-bit files look in 32bit subdir

