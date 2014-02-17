/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

using namespace std; 

struct chainNode{

	int element;
	chainNode* next;

	chainNode(){};
	chainNode(const int& element);
	chainNode(const int& element, chainNode* next);
};