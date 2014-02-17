/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include "Graph.h"
#include <cstdlib>

using namespace std;

Graph::Graph(int v){
	
	initialize(v);

}

Graph::Graph(int data[][2], int vertixes, int edges){

	initialize(vertixes);

	for(int i = 0; i < edges; i++)
		addEdge(data[i][0],data[i][1]);

}

void Graph::initialize(int v){
	
	verticesWithAdjacents.reserve(v);
	numVertices = v;
	numEdges = 0;
	vector<int> empty;
	for(int i = 0; i < v; i++){
		verticesWithAdjacents[i].reserve(v);
		verticesWithAdjacents.push_back(empty);
	}
	
}

void Graph::addEdge(const int& a, const int& b){

	verticesWithAdjacents[a].push_back(b);
	numEdges++;

}

vector<int> *Graph::adjacencyList(int vert){
	return &verticesWithAdjacents[vert];
}

void Graph::print(){

	for(int j = 0; j < verticesWithAdjacents.size(); j++){
		cout << j << ":";
		for(int i = 0; i < verticesWithAdjacents[j].size(); i++)
			cout << verticesWithAdjacents[j][i] << " ";
		
		cout << endl;
	}
	
}
/*
int main(){

	int data[20][2];

	srand(time(NULL));
	for(int i = 0; i < 20; i++){
		data[i][0] = rand()%10;
		data[i][1] = rand()%10;
		
	}

	for (int i = 0; i < 20; ++i){
		cout << data[i][0] << " " << data[i][1] << endl;
	}

	cout << "***" << endl;

	Graph g(data, 10, 20);
	g.print();

	int vere;
	cout << "which vertex: ";
	cin >> vere;
	vector<int> *temp = g.adjacencyList(vere);
	for(int i = 0; i < temp->size(); i++)
		cout << (*temp)[i];


}*/