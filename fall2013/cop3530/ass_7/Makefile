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

main: main.o DirectedWeightedEdge.o DirectedWeightedEdgeGraph.o DijkstraSP.o myException.o
	$(CXX) -o main main.o DijkstraSP.o DirectedWeightedEdge.o DirectedWeightedEdgeGraph.o

main.o: main.cpp
	$(CXX) -c main.cpp

#djsp: DijkstraSP.o DirectedWeightedEdge.o DirectedWeightedEdgeGraph.o
#	$(CXX) -o djsp DijkstraSP.o DirectedWeightedEdge.o DirectedWeightedEdgeGraph.o

DijkstraSP.o: DijkstraSP.cpp
	$(CXX) -c DijkstraSP.cpp

DirectedWeightedEdge.o: DirectedWeightedEdge.cpp
	$(CXX) -c DirectedWeightedEdge.cpp

DirectedWeightedEdgeGraph.o: DirectedWeightedEdgeGraph.cpp
	$(CXX) -c DirectedWeightedEdgeGraph.cpp

myException.o: myException.cpp
	$(CXX) -c myException.cpp

clean:
	rm -rf *.o main maksim_levental_3186_7826.tar

tarfile: 
	tar -cf maksim_levental_3186_7826.tar main.cpp DijkstraSP.cpp DirectedWeightedEdge.cpp \
	DirectedWeightedEdgeGraph.cpp myException.cpp DijkstraSP.h DirectedWeightedEdge.h \
	DirectedWeightedEdgeGraph.h myException.h Makefile