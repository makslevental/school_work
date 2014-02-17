/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include "Chain.h"

chainNode::chainNode(const int& element){
	this->element = element;
}

chainNode::chainNode(const int& element, chainNode* next){
	this->element = element;
	this->next = next;
}