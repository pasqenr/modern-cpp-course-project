# SimpleList

### Description

The aim of this project is to create a simple double linked list implementation in C++ for the *Modern C++ Programming* 
course project. There are two possible implementations:

* Unordered list;
* Ordered list.

The first is a classic list. The second one it's a list that keep itself ordered adjusting the structure when
insertions and deletions are performed. In the list the structure stores nodes. To avoid the use of null pointers
the list keep two special nodes in head and tail as sentinels.

The project is built as a static library. The only executable produced is the one that contains the tests. That
also provide some examples of code.

### How to run

Create the *Makefile* using CMake:
```bash
cd build/
cmake -DCMAKE_BUILD_TYPE=Release ..
```

Where the `DCMAKE_BUILD_TYPE` can be one of:

* Debug
* Release
* SANITIZE

To enable all the commands and flags be sure to override the compiler if it's set to GCC by default:
```bash
cd build/
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ ..
```

Available commands:

* `make`: compile the static library and the test executable;
* `make install`: compile and put the (test) executable in the bin/ folder;
* `make test`: run only the tests (needs `make` before to compile the program);
* `make all test`: compile and run all the tests;
* `make clean-all`: clean all the files generated by the makefile;
* `make stats`: code statistics (lines of code);
* `make cyclo`: code cyclomatic complexity;
* `make doc`: generate doxygen documentation;
* `make infer`: Facebook's static analysis tool;
* `make scan`: Clang's static analyzer; 
* `make tidy`: Clang's linter;
* `make check`: Cppcheck static analyzer;
* `make format`: Clang style formatter.

### Notes

This project isn't intended to be used in any real or hobby project. There are several choice made to meet the first
deadline as fast as possible but with a complete and working project.
Still, I'm happy to have learnt the basics of C++ and CMake and I hope to learn a lot more in the future.