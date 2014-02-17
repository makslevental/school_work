// find a path in a maze

#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include "arrayStack.h"
#include "position.h"
#include "make2dArray.h"
#include "arrayQueue.h"

using namespace std;
// globals
int **maze, size;
position maze2[12][12];
arrayStack<position>* stac_k;
arrayStack<position>* path;  // pointer to stack
arrayQueue<position*>* path2;  // pointer to stack

// initialize offsets
position offset[4];

void welcome() {};

void inputMaze()
{// Input the maze.
   ifstream myfile;
   myfile.open("maze.input");
   //cout << "Enter maze size" << endl;
   myfile >> size;
   
   make2dArray(maze, size + 2, size + 2);
   cout << "Enter maze in row major order" << endl;
   for (int i = 1; i <= size; i++){
      for (int j = 1; j <= size; j++){
               myfile >> maze[i][j];
               maze2[i][j].row = i;
               maze2[i][j].col = j;
               maze2[i][j].discovered = maze[i][j];   
      }
   }
      // initialize wall of obstacles around maze
   for (int i = 0; i <= size + 1; i++) 
   {
      maze[0][i] = maze[size + 1][i] = 1; // bottom and top
      maze2[0][i].discovered = maze2[size + 1][i].discovered = 1; // bottom and top
      maze[i][0] = maze[i][size + 1] = 1; // left and right
      maze2[i][0].discovered = maze2[i][size + 1].discovered = 1;
   }

   maze2[10][11].discovered = 0;

   offset[0].row = 0; offset[0].col = 1;   // right
   offset[1].row = 1; offset[1].col = 0;   // down
   offset[2].row = 0; offset[2].col = -1;  // left
   offset[3].row = -1; offset[3].col = 0;  // up

   for (int i = 0; i <= size+1; i++){
      {for (int j = 0; j <= size+1; j++)
         //cout << maze[i][j] << " ";
         cout << maze2[i][j].discovered << " ";
      }
         cout << endl;
   }
   myfile.close();

}

bool recursive_findpath(position pos){


   if(maze[pos.row][pos.col] == 1) 
         return false;
   if(pos.row == 10 && pos.col == 10){
      cout << "success" << endl; 

    }
   else{


         maze[pos.row][pos.col] = 1;
         char buffer[50];
         //sprintf (buffer, "row %d col %d", pos.row, pos.col) ;
         //cout << buffer << endl;
         //perror(buffer);
         position east;
         east.row = pos.row + offset[0].row;
         east.col = pos.col + offset[0].col;
         position south;
         south.row = pos.row + offset[1].row;
         south.col = pos.col + offset[1].col;
         position west;
         west.row = pos.row + offset[2].row;
         west.col = pos.col + offset[2].col;
         position north;
         north.row = pos.row + offset[3].row;
         north.col = pos.col + offset[3].col;
         if(recursive_findpath(east)){
                     stac_k->push(east);
                     return true;}
         if(recursive_findpath(south)){
                     stac_k->push(south);
                     return true;}
         if(recursive_findpath(west)){
                     stac_k->push(west);
                     return true;}
         if(recursive_findpath(north)){
                     stac_k->push(north);
                     return true;}
         
      }
   }



// for queue
bool findPath2(){

   ofstream myfile;
   myfile.open("maze.output");
   path2 = new arrayQueue<position*>;


   position* here;
   maze2[1][1].extr = "beg";
   here = &maze2[1][1];
   //maze[1][1] = 1; // prevent return to entrance
   int option = 0; // next move
   int lastOption = 3;
   
   // search for a path
   path2->push(here);
   
   while(!path2->empty()){
      
      int r, c;  
      here = path2->front();
      myfile << "row " << here->row << "col " << here->col << endl;
      path2->pop();
      //if(maze[here.row][here.col] == 1) continue;
      //maze[here.row][here.col] = 1;
      here->print();

 
      if(here->row == size && here->col == size) break;
      
      //scan around here
      int option = 0; 
      position* around;   
      while (option <= lastOption) 
      {
         r = (here->row + offset[option].row);
         c = (here->col + offset[option].col);
         
         around = &maze2[r][c];
         
         if (maze2[r][c].discovered == 0){path2->push(around); maze2[r][c].discovered = 1; maze2[r][c].ptr = here;}
         option++;
     
      }

      myfile << "empty " << path2->empty() << endl;
   }
   cout << "*********************************" << endl;
   if(path2->empty() && !(here->row == size && here->col == size)) return false;
   return true;  // at exit

}
bool findPath()
   {// Find a path from (1,1) to the exit (size, size).
   // Return true if successful, false if impossible.

   path = new arrayStack<position>;


   // initialize wall of obstacles around maze
   for (int i = 0; i <= size + 1; i++) 
   {
   maze[0][i] = maze[size + 1][i] = 1; // bottom and top
   maze[i][0] = maze[i][size + 1] = 1; // left and right
   }

   position here;
   here.row = 1;
   here.col = 1;
   maze[1][1] = 1; // prevent return to entrance
   int option = 0; // next move
   int lastOption = 3;

   // search for a path
   while (here.row != size || here.col != size)

   {// not exit
   // find a neighbor to move to
   int r, c;      
   while (option <= lastOption) 
   {
      r = here.row + offset[option].row;
      c = here.col + offset[option].col;
      if (maze[r][c] == 0) break;
      option++; // next option
   }

   // was a neighbor found?
   if (option <= lastOption)
   {// move to maze[r][c]
      path->push(here);
      here.row = r;
      here.col = c;
      maze[r][c] = 1; // set to 1 to prevent revisit
      option = 0;
   }
   else
   {// no neighbor to move to, back up
      if (path->empty())
         return false;   // no place to back up to
      position next = path->top();
      path->pop();
      if (next.row == here.row)
         option = 2 + next.col - here.col;
      else option = 3 + next.row - here.row;
      here = next;
   }
   }

   return true;  // at exit
}
bool findPath3()
   {// Find a path from (1,1) to the exit (size, size).
   // Return true if successful, false if impossible.

   path = new arrayStack<position>;


   // initialize wall of obstacles around maze
   for (int i = 0; i <= size + 1; i++) 
   {
   maze[0][i] = maze[size + 1][i] = 1; // bottom and top
   maze[i][0] = maze[i][size + 1] = 1; // left and right
   }

   position here;
   here.row = 1;
   here.col = 1;
   maze[1][1] = 1; // prevent return to entrance
   int option = 0; // next move
   int lastOption = 3;

   // search for a path
   while (here.row != size || here.col != size)
   {// not exit
      // find a neighbor to move to
      int r, c;


      while (option <= lastOption) 
      {
         r = here.row + offset[option].row;
         c = here.col + offset[option].col;
         if (maze[r][c] == 0) break;
         option++; // next option
      }

      // was a neighbor found?
      if (option <= lastOption)
      {// move to maze[r][c]
         path->push(here);
         here.row = r;
         here.col = c;
         maze[r][c] = 1; // set to 1 to prevent revisit
         option = 0;
      }
      else
      {// no neighbor to move to, back up
         if (path->empty())
            return false;   // no place to back up to
         position next = path->top();
         path->pop();
         if (next.row == here.row)
            option = 2 + next.col - here.col;
         else option = 3 + next.row - here.row;
         here = next;
      }
   }

   return true;  // at exit
}
void outputPath()
{// Output path to exit.
   cout << "The path is" << endl;
   position here;
   while (!path->empty())
   {
      here = path->top();
      path->pop();
      cout << here.row << ' ' << here.col << endl;
   }
}

int main()
{
   welcome();
   inputMaze();
   //else
   //   cout << "No path" << endl;
   position* trace;
   if(findPath2()){
      
      trace = &maze2[size][size];
   
      while(trace->extr != "beg"){
   
         maze[trace->row][trace->col] = 8;
         trace = trace->ptr;
   
      }
      for (int i = 0; i <= size+1; i++){
         {for (int j = 0; j <= size+1; j++)
            cout << maze[i][j] << " ";
   
         }
         cout << endl;
      }
   }
   /*
   position start;
   start.row = 1;
   start.col = 1; 
   stac_k = new arrayStack<position>;
   cout << stac_k->empty() << endl;
   recursive_findpath(start);
   
   while(!stac_k->empty()){

      cout << "row " << stac_k->top().row << " col " << stac_k->top().col << endl;
      stac_k->pop();
   }
   */
   
}

void find_direction(position& off[], position pos){



}