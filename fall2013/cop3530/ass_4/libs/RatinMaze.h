#ifndef _RatInMaze
#define _RatInMaze

using namespace std;
//forward declarations

// forward declarations because stack includes RatInMaze objects so RatInMaze
// can't include stack.h
class stack;
class queue;
class RatInMaze{
	public:
		RatInMaze(){};
		~RatInMaze();
		void load(char charmaze[][15], int rows, int columns);
		bool searchStack(int fromX, int fromY, int toX, int toY);
		bool searchQueue(int fromX, int fromY, int toX, int toY);
		bool searchStackSmart(int fromX, int fromY, int toX, int toY);
		bool inside(int fromX, int fromY, int toX, int toY);
		void print(bool yesNo);

		struct position{
			int row, col;
			int discovered;
			int visited;
			int deadend;
		    position* ptr; //to previous node
		 	string extr;
		 	int queee;
			void print(){
				cout << "position row " << row << "position col" << col << endl;
			}
			~position(){ptr = NULL;}
		};
		void sortOffset(RatInMaze::position pos);
	private: 
		// charmaze copy	
		int** cmaze;
		// number of rows and columns in the maze, including edge walls
		int rows;
		int cols;
		// 2d array of position elements for maze positions
		position **maze;
		stack* stak;
		queue* qoi;
		// array for position displacements when picking directions
		position offset[4];
		position offsetfirm[4];
		// coordinates of the beginning and end of maze
		int beginning[2];
		int ending[2];
		// flags for which method for traversing the maze was run
		bool quy;
		bool stick;
		bool quadrant[3];
		// number of steps taken in the maze
		int steps;
		
};
#endif