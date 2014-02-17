/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#ifndef DijkstraSP_
#define DijkstraSP_
#include <map>
#include "DirectedWeightedEdgeGraph.h"

using namespace std;

class DijkstraSP{

	public:
		DijkstraSP(DirectedWeightedEdgeGraph*, int);
		double distT(int);
		bool hasPathTo(int);
		vector<DirectedWeightedEdge> *pathTo(int);
		void relax(DirectedWeightedEdge*);
		void showPathTo(int);
		void showPathesByDistance();
		
	protected:
		double* distTo;
		vector<DirectedWeightedEdge> edgeTo;
		map<double, int> pq;

};

#endif