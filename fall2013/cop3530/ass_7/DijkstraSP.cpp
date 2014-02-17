/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include "DijkstraSP.h"
#include <stack>

DijkstraSP::DijkstraSP(DirectedWeightedEdgeGraph *g, int v){
	distTo = new double[g->numberVertices()];
	for(int i = 0; i < g->numberVertices(); i++){
		distTo[i] = 9999999999;
		edgeTo.push_back(*(new DirectedWeightedEdge(0,0,0, distTo[i])));
	}

	distTo[v] = 0;
	edgeTo[v] = *(new DirectedWeightedEdge(-1,-1,-1,0));

	pq.insert( pair<double,int>(distTo[v], v) );

	while(!pq.empty()){

		map<double, int>::iterator it=pq.begin();
		int k = it->second;
		pq.erase(it);

		vector<DirectedWeightedEdge> *adjacents = g->adjacencyList(k);
		for(int i = 0; i < adjacents->size(); i++)
			relax( &(*adjacents)[i] );
		
	}

}
// left off at relax method
void DijkstraSP::relax(DirectedWeightedEdge *e){
	int from = e->from(), to = e->to();
	if(distTo[to] > distTo[from] + e->mass()){
		double oldDist = distTo[to];
		distTo[to] = distTo[from] + e->mass();
		edgeTo[to] = *(new DirectedWeightedEdge(from, to, e->mass(), distTo[to]));

		for (map<double,int>::iterator it=pq.begin(); it!=pq.end(); ++it)
		    if(it->second == to){
		    	pq.erase(it);
		    	break;
	    	}
   
	    pq.insert( pair<double, int>(distTo[to], to));
	}
}

double DijkstraSP::distT(int v){
	return distTo[v];
}

bool DijkstraSP::hasPathTo(int v){
	return distTo[v]<9999999999;
}

void DijkstraSP::showPathTo(int v){
	if(hasPathTo(v) == false)
		cout << "no path";
	else{
		stack<int> order;
		int k = v;
		
		while(edgeTo[k].mass() != -1){
			// cout << edgeTo[k].to() +1 << " ";
			order.push(k+1);
			k = edgeTo[k].from();
		}
		order.push(1);
		while(!order.empty()){
			cout << order.top() << " ";
			order.pop();
		}

	}
}

void DijkstraSP::showPathesByDistance(){
	map<double, int> pathes;
	for(int i = 0; i < 6; i++)
		pathes.insert( pair<double, int>(distTo[i], i) );

	std::map<double, int>::iterator it;
	for(it = pathes.begin(); it != pathes.end(); it++){
		cout << it->first << ": ";
		showPathTo(it->second);
		if(it->second == 0) cout << 1;
		cout << endl;
	}


}
/*
int main(){
	DirectedWeightedEdgeGraph *g; 

	double data[9][3];

	data[0][0] = 1-1;
	data[0][1] = 4-1;
	data[0][2] = 30;

	data[1][0] = 1-1;
	data[1][1] = 5-1;
	data[1][2] = 100;

	data[2][0] = 1-1;
	data[2][1] = 2-1;
	data[2][2] = 10;

	data[3][0] = 2-1;
	data[3][1] = 3-1;	
	data[3][2] = 50;

	data[4][0] = 3-1;
	data[4][1] = 5-1;
	data[4][2] = 10;

	data[5][0] = 3-1;
	data[5][1] = 6-1;
	data[5][2] = 5;

	data[6][0] = 4-1;
	data[6][1] = 3-1;
	data[6][2] = 20;

	data[7][0] = 4-1;
	data[7][1] = 6-1;
	data[7][2] = 15;

	data[8][0] = 5-1;
	data[8][1] = 4-1;
	data[8][2] = 60;

	g = new DirectedWeightedEdgeGraph(data, 6, 9);
	// g->print();
	// convention is that first vertex is actually zeroeth
	DijkstraSP *dijk = new DijkstraSP(g,0);

	// for(int i = 0; i < 6; i++)
	// 	cout << dijk->distT(i) << endl;
	cout << endl;
	dijk->showPathesByDistance();
	cout << endl;
}

*/