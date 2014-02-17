/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include "DijkstraSP.h"
#include "myException.h"
using namespace std;

int main(){

	DirectedWeightedEdgeGraph *g; 

	double data[9][3];

	data[0][0] = 0;
	data[0][1] = 3;
	data[0][2] = 30;

	data[1][0] = 0;
	data[1][1] = 4;
	data[1][2] = 100;

	data[2][0] = 0;
	data[2][1] = 1;
	data[2][2] = 10;

	data[3][0] = 1;
	data[3][1] = 2;	
	data[3][2] = 50;

	data[4][0] = 2;
	data[4][1] = 4;
	data[4][2] = 10;

	data[5][0] = 2;
	data[5][1] = 5;
	data[5][2] = 5;

	data[6][0] = 3;
	data[6][1] = 2;
	data[6][2] = 20;

	data[7][0] = 3;
	data[7][1] = 5;
	data[7][2] = 15;

	data[8][0] = 4;
	data[8][1] = 3;
	data[8][2] = 60;

	g = new DirectedWeightedEdgeGraph(data, 6, 9);
	DijkstraSP *dijk = new DijkstraSP(g,0);
	cout << endl;
	dijk->showPathesByDistance();
	cout << endl;

}