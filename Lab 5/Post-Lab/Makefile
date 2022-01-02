# Makefile
# October 7th, 2021
# Asadbek Shamsiev, as9vd

CXX=clang++ $(CXXFLAGS)
CXXFLAGS=-Wall # Enable all warnings
DEBUG=-g

avltree: AVLNode.o AVLTree.o AVLPathTest.o
	$(CXX) $(DEBUG) AVLNode.o AVLTree.o AVLPathTest.o
	@echo "Tree is ready!"

AVLNode.o: AVLNode.cpp AVLNode.h

AVLTree.o: AVLTree.cpp AVLTree.h

AVLPathTest.o: AVLPathTest.cpp

.PHONY: clean

clean:
	-rm -f *.o tree