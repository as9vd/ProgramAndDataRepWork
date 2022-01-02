# Makefile
# October 5th, 20201
# Asadbek Shamsiev, as9vd

CXX=clang++ $(CXXFLAGS)
CXXFLAGS=-Wall # Enable all warnings
DEBUG=-g

bsttree: BinaryNode.o BinarySearchTree.o BSTPathTest.o
	$(CXX) $(DEBUG) BinaryNode.o BinarySearchTree.o BSTPathTest.o
	@echo "BST is ready!"

BinaryNode.o: BinaryNode.cpp BinaryNode.h

BinarySearchTree.o: BinarySearchTree.cpp BinarySearchTree.h

BSTPathTest.o: BSTPathTest.cpp

.PHONY: clean

clean:
	-rm -f *.o bsttree