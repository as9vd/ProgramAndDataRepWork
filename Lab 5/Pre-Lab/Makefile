# Makefile
# October 4th, 20201
# Asadbek Shamsiev, as9vd

CXX=clang++ $(CXXFLAGS)
CXXFLAGS=-Wall # Enable all warnings
DEBUG=-g

tree: TreeCalc.o TreeNode.o TreeCalcTest.o
	$(CXX) $(DEBUG) TreeCalc.o TreeNode.o TreeCalcTest.o
	@echo "Tree is ready!"

TreeCalc.o: TreeCalc.cpp TreeCalc.h

TreeNode.o: TreeNode.cpp TreeNode.h

TreeCalcTest.o: TreeCalcTest.cpp

.PHONY: clean

clean:
	-rm -f *.o tree