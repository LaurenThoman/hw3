CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: llrec-test stack-test heap-test

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------

heap-test: heap-test.cpp heap.h
	$(CXX) $(CXXFLAGS) heap-test.cpp -o $@

llrec-test: llrec.cpp llrec-test.cpp llrec.h
	$(CXX) $(CXXFLAGS) llrec.cpp llrec-test.cpp -o $@

stack-test: stack-test.cpp stack.h
	$(CXX) $(CXXFLAGS) stack-test.cpp -o $@

clean:
	rm -f *.o rh llrec-test *~

.PHONY: clean 