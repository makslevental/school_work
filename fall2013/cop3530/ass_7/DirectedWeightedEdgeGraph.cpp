/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include "DirectedWeightedEdgeGraph.h"
#include <cstdlib>

using namespace std;

DirectedWeightedEdgeGraph::DirectedWeightedEdgeGraph(int v){
	
	initialize(v);

}

DirectedWeightedEdgeGraph::DirectedWeightedEdgeGraph(double data[][3], int vertices, int edges){

	initialize(vertices);

	for(int i = 0; i < edges; i++){
		DirectedWeightedEdge *temp = new DirectedWeightedEdge(data[i][0],data[i][1],data[i][2]);
		addEdge(temp);
	}
}

void DirectedWeightedEdgeGraph::initialize(int v){
	
	verticesWithAdjacents.reserve(v);
	numVertices = v;
	numEdges = 0;
	vector<DirectedWeightedEdge> empty;
	for(int i = 0; i < v; i++){
		verticesWithAdjacents[i].reserve(v);
		verticesWithAdjacents.push_back(empty);
	}
	
}

void DirectedWeightedEdgeGraph::addEdge(DirectedWeightedEdge *e){

	verticesWithAdjacents[e->from()].push_back(*e);
	numEdges++;

}

vector<DirectedWeightedEdge> *DirectedWeightedEdgeGraph::adjacencyList(int vert){
	return &verticesWithAdjacents[vert];
}



void DirectedWeightedEdgeGraph::print(){

	for(int j = 0; j < verticesWithAdjacents.size(); j++){
		cout << j << ":";
		for(int i = 0; i < verticesWithAdjacents[j].size(); i++)
			verticesWithAdjacents[j][i].print();
		
		cout << endl;
	}
	
}/*

int main(){

	double data[20][3];

	srand(time(NULL));
	for(int i = 0; i < 20; i++){
		data[i][0] = rand()%10;
		data[i][1] = rand()%10;
		int k = rand()%10;
		double d = (double)k;
		data[i][2] = k/3.14;
	}	

	for (int i = 0; i < 20; ++i){
		cout << data[i][0] << " " << data[i][1] << " " << data[i][2] << endl;
	}

	cout << "***" << endl;

	DirectedWeightedEdgeGraph g(data, 10, 20);
	g.print();

	int vere;
	cout << "which vertex: ";
	cin >> vere;
	vector<DirectedWeightedEdge> *temp = g.adjacencyList(vere);
	for(int i = 0; i < temp->size(); i++)
		(*temp)[i].print();


}*/