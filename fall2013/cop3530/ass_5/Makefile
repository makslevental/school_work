

# Name: Maksim Levental

# UF ID: 3186-7826

# Gator ID: mlevental86

# Discussion Section #: 1085


# *****************************************************
# Parameters to control Makefile operation

#CXX = g++
CXX = g++ -W -Wall -ansi -pedantic
CXXFLAGS = -o
DEBUGGER = -ggdb
# ****************************************************
# Entries to bring the executable up to date

main: main.o PriorityQueue.o MinHeap.o BinaryTree.o Arraylist.o myException.o
	$(CXX) $(DEBUGGER) -o main main.o PriorityQueue.o MinHeap.o BinaryTree.o Arraylist.o myException.o

main.o: main.cpp
	$(CXX) -c main.cpp

PriorityQueue.o: PriorityQueue.cpp
	$(CXX) -c PriorityQueue.cpp

MinHeap.o: MinHeap.cpp
	$(CXX) -c MinHeap.cpp

BinaryTree.o: BinaryTree.cpp
	$(CXX) -c BinaryTree.cpp

Arraylist.o: Arraylist.cpp
	$(CXX) -c Arraylist.cpp

myException.o: myException.cpp
	$(CXX) -c myException.cpp

# MinHeap: MinHeap.cpp BinaryTree.cpp Arraylist.cpp myException.cpp 
# 	$(CXX) $(DEBUGGER) -o MinHeap MinHeap.cpp BinaryTree.cpp Arraylist.o myException.o

# BinaryTree: BinaryTree.cpp Arraylist.cpp myException.cpp 
# 	$(CXX) $(DEBUGGER) -o BinaryTree BinaryTree.cpp Arraylist.o myException.o

# PriorityQueue: PriorityQueue.cpp MinHeap.cpp BinaryTree.cpp Arraylist.cpp myException.cpp 
# 	$(CXX) $(DEBUGGER) -o PriorityQueue MinHeap.cpp PriorityQueue.cpp BinaryTree.cpp Arraylist.o myException.o


tarfile: 
	tar -cf maksim_levental_3186_7826.tar main.cpp PriorityQueue.cpp \
			PriorityQueue.h Arraylist.cpp Arraylist.h myException.cpp myException.h \
			MinHeap.cpp MinHeap.h BinaryTree.cpp BinaryTree.h Makefile Linearlist.h

clean:
	rm -rf *.o main maksim_levental_3186_7826.tar

# kill:
# 	find ./ -name '*~' | xargs rm
