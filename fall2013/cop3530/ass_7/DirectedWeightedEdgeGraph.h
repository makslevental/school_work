/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#ifndef DirectedWeightedEdgeGraph_
#define DirectedWeightedEdgeGraph_

#include "DirectedWeightedEdge.h"
#include <cstdlib>
#include <vector>
using namespace std;

class DirectedWeightedEdgeGraph{

	public:
		DirectedWeightedEdgeGraph(int);
		DirectedWeightedEdgeGraph(double[][3], int, int);
		int numberVertices(){ return numVertices; }
		int numberEdges(){ return numEdges; }
		void addEdge(DirectedWeightedEdge*);
		vector<DirectedWeightedEdge> *adjacencyList(int);
		vector<vector<DirectedWeightedEdge> > *allEdges(){ return &verticesWithAdjacents; };
		void print();

	protected:
		int numVertices;
		int numEdges;
		vector<vector<DirectedWeightedEdge> > verticesWithAdjacents;

	private:
		void initialize(int);

};


#endif