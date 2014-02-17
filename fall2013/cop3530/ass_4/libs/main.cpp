
#include <iostream>
#include "RatinMaze.h"
using namespace std;

void print_header (string h, int fromX,int fromY,int toX,int toY)  {
    cout << h << "from " << "(" << fromY << "," << fromX << ") to ("
         << toY << "," << toX << "):" << endl;
}

int main (){

    RatInMaze* rim = new RatInMaze();
	char maze[13][15]={
		'0','0','0','1','0','0','0','0','0','0','1','0','0','0','0',
		'0','0','0','1','0','0','1','0','0','0','0','0','0','0','0',
		'0','0','0','0','0','0','0','1','1','1','1','1','1','1','1',
		'0','0','0','1','1','1','0','0','1','0','0','1','0','0','0',
		'0','0','0','0','0','1','1','0','0','1','0','0','1','0','0',
		'1','1','0','0','0','1','1','0','0','1','0','0','0','0','0',
		'0','1','1','0','0','1','1','0','0','1','0','0','0','0','0',
		'0','0','1','0','0','1','1','0','0','1','0','0','0','0','0',
		'0','1','1','0','0','1','0','0','0','0','0','0','0','0','0',
		'0','0','1','0','0','0','1','1','1','1','1','1','1','1','1',
		'0','0','1','0','1','0','0','0','0','0','0','0','0','0','0',
		'0','0','1','0','1','0','0','0','1','0','0','0','0','0','0',
		'0','0','0','0','1','0','0','1','0','0','0','0','0','0','0' };

/*	rim->load(maze,13,15);
	print_header("Queue search ", -1,1,10,10);
	rim->print(rim->searchQueue(-1,1,10,10));

	rim->load(maze,13,15);
	print_header("Stack search ", 0,0,41,1);
	rim->print(rim->searchStack(0,0,41,1));*/


	int fromX = 0;
	int fromY = 7;
	int toX =  14;
	int toY =  6;


	rim->load(maze,13,15);
	print_header("Rat (stack) searching ",fromX,fromY,toX,toY);
	rim->print(rim->searchStack(fromX,fromY,toX,toY));

	rim->load(maze,13,15);
	print_header("Multiple rats searching ",fromX,fromY,toX,toY);
	rim->print(rim->searchQueue(fromX,fromY,toX,toY));

	rim->load(maze,13,15);
	print_header("Smart rat searching ",fromX,fromY,toX,toY);
	rim->print(rim->searchStackSmart(fromX,fromY,toX,toY));
}



