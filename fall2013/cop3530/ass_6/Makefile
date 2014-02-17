

# Name: Maksim Levental

# UF ID: 3186-7826

# Gator ID: mlevental86

# Discussion Section #: 1085


# *****************************************************
# Parameters to control Makefile operation

CXX = g++
CXXFLAGS = -o
DEBUGGER = -ggdb
# ****************************************************
# Entries to bring the executable up to date

main: main.o MaxWinnerTree.o BinaryTree.o BinPacking.o myException.o
	$(CXX) -o main main.cpp MaxWinnerTree.cpp BinaryTree.cpp BinPacking.cpp myException.cpp

main.o: main.cpp
	$(CXX) -c main.cpp	

MaxWinnerTree.o: MaxWinnerTree.cpp
	$(CXX) -c MaxWinnerTree.cpp

BinPacking.o: BinPacking.cpp
	$(CXX) -c BinPacking.cpp

BinaryTree.o: BinaryTree.cpp
	$(CXX) -c BinaryTree.cpp

myException.o: myException.cpp
	$(CXX) -c myException.cpp

tarfile: 
	tar -cf maksim_levental_3186_7826.tar main.cpp MaxWinnerTree.cpp \
	BinaryTree.cpp BinPacking.cpp myException.cpp Makefile \
	MaxWinnerTree.h BinaryTree.h BinPacking.h myException.h
        
clean:
	rm -rf *.o main maksim_levental_3186_7826.tar
	
kill:
	find ./ -name '*~' | xargs rm

