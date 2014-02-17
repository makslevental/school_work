/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include "DirectedWeightedEdge.h"
#include <vector>
using namespace std;

DirectedWeightedEdge::DirectedWeightedEdge(int a, int b, double fatty){
	v = a;
	w = b;
	weight = fatty;
}

DirectedWeightedEdge::DirectedWeightedEdge(int a, int b, double fatty, double pri){
	v = a;
	w = b;
	weight = fatty;
	priority = pri;
}	


DirectedWeightedEdge::DirectedWeightedEdge(const DirectedWeightedEdge& e){
	v = e.v;
	w = e.w;
	weight = e.weight;
}

void DirectedWeightedEdge::operator=(const DirectedWeightedEdge& obj)
{
    v = obj.v;
    w = obj.w;
    weight = obj.weight;

    return;
}

int DirectedWeightedEdge::from(){
	return v;
}

int DirectedWeightedEdge::to(){
	return w;
}

double DirectedWeightedEdge::mass(){
	return weight;
}

void DirectedWeightedEdge::print(){
	cout << v << "-(" << weight << ")->" << w << " ";
}

void DirectedWeightedEdge::setPriority(double x){
	priority = x;
}

double DirectedWeightedEdge::getPriority(){
	return priority;
}
/*
int main(){

	DirectedWeightedEdge *dir = new DirectedWeightedEdge(0,1,2.3);

	vector<DirectedWeightedEdge> vec[10];
	vec[0].push_back(*dir);
	vec[0][0].print();
	dir = new DirectedWeightedEdge(2,3,3.5);
	vec[0][0] = *dir;
	vec[0][0].print();


}*/