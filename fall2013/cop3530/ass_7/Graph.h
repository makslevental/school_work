/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#ifndef Graph_
#define Graph_
#include <iostream>
#include <vector>

using namespace std;

class Graph{

	public:
		Graph(){}
		Graph(int);
		Graph(int[][2], int, int);
		Graph(const Graph&);
		~Graph(){}
		int numberVertices(){ return numVertices; }
		int numberEdges(){ return numEdges; }
		void addEdge(const int&, const int&);
		vector<int> *adjacencyList(int);
		void print();

	protected:
		int numVertices;
		int numEdges;
		vector<vector<int> > verticesWithAdjacents;

	private:
		void initialize(int);

};

#endif