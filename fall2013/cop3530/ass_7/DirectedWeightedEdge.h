/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#ifndef DirectedWeightedEdge_
#define DirectedWeightedEdge_
#include <iostream>

using namespace std;

class DirectedWeightedEdge{

	public:
		struct CompareEdge{
			bool operator()(const DirectedWeightedEdge& p1, const DirectedWeightedEdge& p2) {
			    // return "true" if "p1" is ordered before "p2", for example:
			    return p1.priority < p2.priority;
			}
		};

		DirectedWeightedEdge(int, int, double);
		DirectedWeightedEdge(int, int, double, double);
		DirectedWeightedEdge(const DirectedWeightedEdge&);
		void operator=(const DirectedWeightedEdge&); 
		int from();
		int to();
		void print();
		double mass();
		void setPriority(double);
		double getPriority();

	protected:
		int v;
		int w;
		double weight;
		double priority;
};

#endif