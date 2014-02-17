#ifndef position_
#define position_

struct position
{
   int row,  // row number of position
       col;  // column number of position
   int discovered;
   position* ptr; //to previous node
   string extr;
   void print(){
   	cout << "position row " << row << "position col" << col << endl;
   }

};

#endif
