/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#ifndef chain_ 
#define chain_


#include "Linearlist.h"
#include "ChainNode.h"

using namespace std; 

//THIS ALL GOES INTO HEADER FILE AS WELL
class chain : public linearList {
   public:
      // constructor, copy constructor and destructor
      chain(int initialCapacity = 10);
      chain(const chain&);
      ~chain();

      // ADT methods
      bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      int* get(int theIndex) const;
      int indexOf(const int& theElement) const;
      void erase(int theIndex);
      void insert(int theIndex, const int& theElement);
      void MaxMin();
      void traverse();
      void output(ostream& out) const;
      friend std::ostream& operator<<(ostream& out, const chain& x){

			x.output(out);
			return(out);

      }
            // iterators to start and end of list
      class iterator;
      iterator begin() {return iterator(firstNode);}
      iterator end() {return iterator(NULL);}

      // iterator for chain
      class iterator 
      {
         public:
            // typedefs required by C++ for a forward iterator
            typedef forward_iterator_tag iterator_category;
            typedef int value_type;
            typedef ptrdiff_t difference_type;
            typedef int* pointer;
            typedef int& reference;

            // constructor
            iterator(chainNode* theNode = NULL)
               {node = theNode;}

            // dereferencing operators
            int& operator*() const {return node->element;}
            int* operator->() const {return &node->element;}

            // increment
            iterator& operator++()   // preincrement
                      {node = node->next; return *this;}
            iterator operator++(int) // postincrement
                        {iterator old = *this;
                         node = node->next;
                         return old;
                        }

            // equality testing
            bool operator!=(const iterator right) const
                  {return node != right.node;}
            bool operator==(const iterator right) const
                  {return node == right.node;}
         protected:
            chainNode* node;
      };  // end of iterator class
  
protected:
      // throw illegalIndex if theIndex invalid
      void checkIndex(int theIndex) const;

      chainNode* firstNode;     // 1D array to hold list elements
      int listSize;             // number of elements in list
};

#endif