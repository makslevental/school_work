
#include "Linearlist.h"

using namespace std; 






//THIS ALL GOES INTO HEADER FILE AS WELL
class arrayList: public linearList {
   public:
      // constructor, copy constructor and destructor
      arrayList(int initialCapacity = 100);
      arrayList(const arrayList&);
      ~arrayList() {delete [] element;}

// ADT methods
      virtual bool empty() const {return listSize == 0;}
      virtual int size() const {return listSize;}
      virtual int* get(int theIndex) const;
      virtual int indexOf(const int& theElement) const;
      virtual void erase(int theIndex);
      virtual void insert(int theIndex, const int& theElement);
      virtual void MaxMin();
//      void output(ostream& out) const;
      virtual void changeLength1D(int*&, int, int);
      // additional methods
      virtual void traverse();
      virtual int capacity() const {return arrayLength;}

protected:
      void checkIndex(int theIndex) const;
            // throw illegalIndex if theIndex invalid
      int* element;      // 1D array to hold list elements
      int arrayLength;       // capacity of the 1D array
      int listSize;          // number of elements in list
};



