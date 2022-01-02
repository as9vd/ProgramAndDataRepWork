# Makefile
# October 18th, 20201
# Asadbek Shamsiev, as9vd

CXX=clang++ $(CXXFLAGS)
CXXFLAGS=-Wall # Enable all warnings
# DEBUG=-g

hash: hashtable.o timer.o wordPuzzle.o
# 	$(CXX) $(DEBUG) hashtable.o timer.o wordPuzzle.o
	$(CXX) hashtable.o timer.o wordPuzzle.o
	@echo "Ready!"

hashtable.o: hashtable.cpp hashtable.h

timer.o: timer.cpp timer.h

wordPuzzle.o: wordPuzzle.cpp

.PHONY: clean

clean:
	-rm -f *.o hash