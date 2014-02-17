#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <map>
#include "stack.h"
#include "queue.h"
#include "RatinMaze.h"


// unit test
/*int main(){
	
	RatInMaze* rim;
	rim = new RatInMaze;
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

char maze[13][15]={
		'0','0','0','1','0','0','0','0','0','0','1','0','0','0','0',
		'0','0','0','1','0','0','1','0','0','0','0','0','0','0','0',
		'0','0','0','0','0','0','0','1','1','1','1','1','1','1','1',
		'0','0','0','1','1','1','0','0','1','0','0','1','0','0','0',
		'0','0','0','0','0','1','1','0','0','1','0','0','1','0','0',
		'1','1','0','0','0','1','1','0','0','1','0','0','0','0','0',
		'0','1','1','0','0','1','1','0','0','1','0','0','0','0','0',
		'0','0','1','0','0','1','1','0','0','1','0','0','0','0','0',
		'1','1','1','0','0','1','0','0','0','0','0','0','0','0','0',
		'0','0','1','0','0','0','1','1','1','1','1','1','1','1','1',
		'0','0','1','0','1','0','0','0','0','0','0','0','0','0','0',
		'0','0','1','0','1','0','0','0','1','0','0','0','0','0','0',
		'0','0','0','0','1','0','0','1','0','0','0','0','0','0','0' };


	rim->load(maze,13,15);
	// print_header("Queue search ", -1,1,10,10);
	rim->print(rim->searchQueue(-1,1,10,10));

	rim->load(maze,13,15);
	// print_header("Stack search ", 0,0,41,1);
	rim->print(rim->searchStack(0,0,41,1));

	rim->load(maze,13,15);
    rim->print(rim->searchStack(0,0,3,3));
	rim->load(maze,13,15);
	rim->print(rim->searchQueue(7,0,6,14));
	rim->load(maze,13,15);
	rim->print(rim->searchStackSmart(7,0,6,14));
}	*/

RatInMaze::~RatInMaze(){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			maze[i][j].~position(); //call destructor for every entry in each columns
		}
		delete[] maze[i]; //delete columns themselves
	}
	delete[] maze; //delete head row
}

void RatInMaze::load(char charmaze[][15], int rows, int columns){

	// quadrant tells you for what reason a search failed if it failed
	// check bottom of print method
	quadrant[0] = quadrant[1] = quadrant[2] = false;
	stak = new stack;
	qoi = new queue;
	maze = new position*[rows+2];
	// keep a copy of the charmaze inside the rim object
	cmaze = new int*[rows+2];
	this->rows = rows+2;
	this->cols = columns+2;
	// mem allocation for for both char pointer and position pointer
	for(int i = 0; i <= rows+1; i++){
		cmaze[i] = new int[columns+2];
		maze[i] = new position[columns+2];
	}
    // initialize wall of obstacles around maze
    for (int i = 0; i <= columns+1; i++){
    	maze[0][i].row = 0;
		maze[0][i].col = i;
        maze[0][i].discovered = maze[rows + 1][i].discovered = 1; // bottom and top    
        maze[0][i].visited = maze[rows + 1][i].visited = 1;
    }  
    for (int i = 0; i <= rows+1; i++){
    	maze[i][0].row = i;
		maze[i][0].col = 0;		
    	maze[i][0].discovered = maze[i][columns + 1].discovered = 1;
    	maze[i][0].visited = maze[i][columns + 1].visited = 1;

    }  
	for(int i = 1; i <= rows; i++){
		for(int j = 1; j <= columns; j++){
			// set coordinates of each position object that make up the maze to be the coordinate of its location
			maze[i][j].row = i;
			maze[i][j].col = j;
			// copy walls from charmaze into position matrix by setting discovered = 1
			(charmaze[i-1][j-1] == '1') ? (maze[i][j].discovered = 1) : 0;
			// charmaze copy looks like maze
			cmaze[i][j] = maze[i][j].discovered;
		}
	}
	
	offset[0].row = 0; offset[0].col = 1;   // right
	offset[1].row = 1; offset[1].col = 0;   // down
	offset[2].row = 0; offset[2].col = -1;  // left
	offset[3].row = -1; offset[3].col = 0;  // up

	offsetfirm[0].row = 0; offsetfirm[0].col = 1;   // right
	offsetfirm[1].row = 1; offsetfirm[1].col = 0;   // down
	offsetfirm[2].row = 0; offsetfirm[2].col = -1;  // left
	offsetfirm[3].row = -1; offsetfirm[3].col = 0;  // up
  
}

void RatInMaze::print(bool yesNo){

	int steps = 0;
	int deadends = 0;
	cout << endl;
	if(yesNo){	

		if(this->stick){
			for(int i = 1; i < rows-1; i++){
				for(int j = 1; j < cols-1; j++){
					
					if(maze[i][j].visited == 2){
						if(maze[i][j].deadend == 1) deadends++;
						cout << "2 ";
						steps++;
					}
					else{
						cout << cmaze[i][j] << " ";
						if(maze[i][j].deadend == 1) deadends++;
					}
				}
				cout << endl;
				
			}
			cout << "\n*****************************" << endl;
			// after method prints if method is to be called flag needs to be reset that this maze traversal was done
			stick = false;
		}


		if(this->quy){
			RatInMaze::position* here;	
			here = &maze[this->ending[0]][this->ending[1]];
			while(here->extr != "beg"){
				here->queee = 5;
				here = here->ptr;
			}
			for(int i = 1; i < rows-1; i++){
				for(int j = 1; j < cols-1; j++){
					
					if(maze[i][j].queee == 5){
						cout << "2 ";
						steps++;
					}
					else
						cout << cmaze[i][j] << " ";
				}
				cout << endl;
				
			}
			cout << "\n*****************************" << endl;
			// after method prints if method is to be called flag needs to be reset that this maze traversal was done
			quy = false;
		}
	}
	else{
		if(quadrant[0] == true) cout << "Starting point is not inside the maze!" << endl;
		if(quadrant[1] == true) cout << "Ending point is not inside the maze!" << endl;
		if(quadrant[2] == true) cout << "There is no path from starting point to ending point!" << endl;
		cout << "Search canceled." << endl;
		return;
	}
	cout << this->steps-deadends << " squares traveled." << endl;
	cout << "Path contains " << steps << " squares" << endl << endl;

}

bool RatInMaze::searchQueue(int fromX, int fromY, int toX, int toY){
	if(!inside(fromY+1, fromX+1, toY+1, toX+1)) return false;
    // Return true if successful, false if impossible.

	// these initializations are necessary for print method. not actually used in this method
	// because queue backtracks
	this->beginning[0] = fromY+1;
	this->beginning[1] = fromX+1;
	this->ending[0] = toY+1;
	this->ending[1] = toX+1;

    RatInMaze::position* here;
	here = &maze[fromY+1][fromX+1];
	here->ptr = &maze[fromY+1][fromX];
	here->ptr->extr = "beg";
    qoi->push_position_ptr(here);
    here->discovered = 1; // prevent return to entrance
    this->steps = 1;
    // search for a path
    while (!qoi->empty()){// not exit //never marks end point
    	this->steps++;
	    here = qoi->front_position_ptr();
	    qoi->pop_position_ptr();

	    if(here->row == toY+1 && here->col == toX+1) {this->steps++; break;}


	    for(int option = 0; option < 4; option++){
	    	int r = here->row + offset[option].row;
	        int c = here->col + offset[option].col;

	        if (maze[r][c].discovered == 0){
	        	qoi->push_position_ptr(&maze[r][c]); 
	        	maze[r][c].discovered = 1; 
	        	maze[r][c].ptr = here;
	        }
	    }
    }
   if(qoi->empty() && !(here->row == toY+1 && here->col == toX+1)){quadrant[2] = true; return false;}
   
   return this->quy = true;  // at exit
}

bool RatInMaze::searchStack(int fromX, int fromY, int toX, int toY){
	if(!inside(fromY+1, fromX+1, toY+1, toX+1)) return false;
    // Return true if successful, false if impossible.

    RatInMaze::position* here;
	here = &maze[fromY+1][fromX+1];
    here->discovered = 1; // prevent return to entrance
    int option = 0;
	this->steps = 1;

    // search for a path
    while (true/*here->row <= toY+1 || here->col <= toX+1*/){// not exit //never marks end point
    	
	    // find a neighbor to move to
	    if(here->row == toY+1 && here->col == toX+1) {here->visited = 2; break;}

	    this->steps++;
	    bool neighbor = false;
	    // here->print();
    	
	    int r, c;      
	    for(option = 0; option < 4; option++){
	    	r = here->row + offset[option].row;
	        c = here->col + offset[option].col;
	        if (maze[r][c].discovered == 0) {neighbor = true; maze[r][c].discovered = 1; break;}
	    }


	    here->visited = 2;
	    // was a neighbor found?
	    if (neighbor){// move to maze[r][c]
	        stak->push_position_ptr(here);
	        maze[r][c].ptr = here;
	        here = &maze[r][c];
	    }
	    else{// no neighbor to move to, back up
	    	here->deadend = 1;
	    	here->visited = 0;
	        if (stak->empty()){
	        	quadrant[2] = true;
	        	return false;   // no place to back up to
	        }
	        else{
	        	here = stak->top_position_ptr();
	        	stak->pop_position_ptr();
        	}
	    }
    }
    
    this->stick = true;
    return true;  // at exit
}
bool RatInMaze::searchStackSmart(int fromX, int fromY, int toX, int toY){
	if(!inside(fromY+1, fromX+1, toY+1, toX+1)) return false;
    // Return true if successful, false if impossible.

	this->beginning[0] = fromY+1;
	this->beginning[1] = fromX+1;
	this->ending[0] = toY+1;
	this->ending[1] = toX+1;

    RatInMaze::position* here;
	here = &maze[fromY+1][fromX+1];
    here->discovered = 1; // prevent return to entrance

	this->steps = 1;

    // search for a path
    while (here->row <= toY+1 || here->col <= toX+1){// not exit //never marks end point
    	
	    // find a neighbor to move to
	    if(here->row == toY+1 && here->col == toX+1){here->visited = 2; break;}
	    this->steps++;
	    bool neighbor = false;
    	// here->print();
	    int r, c;

	    // sort offsets by direction square nearest exit
	    sortOffset(*here);
	    for(int option = 0; option < 4; option++){
	    	r = here->row + offset[option].row;
	        c = here->col + offset[option].col;
	        if (maze[r][c].discovered == 0) {neighbor = true; maze[r][c].discovered = 1; break;}
	    }
	    here->visited = 2;
	    // was a neighbor found?
	    if (neighbor){// move to maze[r][c]
	        stak->push_position_ptr(here);
	        maze[r][c].ptr = here;
	        here = &maze[r][c];
	    }
	    else{// no neighbor to move to, back up
	    	here->deadend = 1;
	    	here->visited = 0;
	        if (stak->empty()){
	        	quadrant[2] = true;
	        	return false;   // no place to back up to
	        }
	        else{
	        	here = stak->top_position_ptr();
	        	stak->pop_position_ptr();
        	}
	    }
    }
    this->stick = true;
    return true;  // at exit
}

bool RatInMaze::inside(int fromX, int fromY, int toX, int toY){
	if(fromX < 1 || fromX > cols || fromY < 1 || fromY > rows){quadrant[0] = true; return false;}
	if(toY < 1 || toY > rows || toX < 1 || toX > cols){quadrant[1] = true; return false;}

	return true;
}

// uses multimap associative map to sort by closest direction square to exit
void RatInMaze::sortOffset(RatInMaze::position pos){

	RatInMaze::position temp[4];
	std::multimap<int,RatInMaze::position> mymap;
	// std::multimap<int,RatInMaze::position>::key_compare mycomp = mymap.key_comp();

	for(int i = 0; i < 4; i++){
		
		temp[i].row = pos.row + offsetfirm[i].row;
		temp[i].col = pos.col + offsetfirm[i].col;
		int a = (temp[i].row - this->ending[0])*(temp[i].row - this->ending[0]);
		int b = (temp[i].col - this->ending[1])*(temp[i].col - this->ending[1]);
		mymap.insert(std::make_pair(a + b,offsetfirm[i]));
	}
	
	int i = 0;
	for(std::multimap<int,RatInMaze::position>::iterator it = mymap.begin(), end = mymap.end(); it != end; it++, i++){
		temp[i].row = it->second.row;
		temp[i].col = it->second.col;
	}

	for(int j = 0; j < 4; j++) {
		offset[j].row = temp[j].row;
		offset[j].col = temp[j].col;
		// cout << offset[j].row << offset[j].col << endl;
	}
	// cout << endl;

}