/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#ifndef ASSIGNMENT_1
#define ASSIGNMENT_1

#include <iostream> // necessary for cout, string, isdigit
#include <sstream>  // necessary for stringstream
#include <cstdlib>  // necessary for exit()
#include <locale>   // locale, tolower
#include <iterator> // ostream iterator

#define ARRAY_ERROR "\nArray index out of bounds\n"

using namespace std;

template<class T>
class linearList
{

	public:
		virtual ~linearList(){}
		virtual bool empty() const = 0;         					// return true iff list is empty, const out front means won't 
												// modify private fields, virtual means most derived version is used by compiler
		virtual int size() const = 0;           					// returns number of elements in the list
		virtual T &operator[](int theIndex) const = 0; 					// return elements whose index is theIndex
		virtual T &get(int theIndex) const = 0;
		virtual int indexOf(const T &theElement) const = 0; 				// return index of first occurrence of theElement
		virtual void erase(int theIndex) = 0; 						// removes element whose index is theIndex		
		virtual void insert(int theIndex, const T &theElement) = 0;			// inserts element at the index theIndex
		virtual void output(ostream &out) const = 0;					// inserts list into stream out
		virtual void print_min_max() const  = 0;			 		// prints the minimum and maximum entry in the list
		virtual void print_current_size() const = 0;		
		
};

template<class T>
class arrayList : public linearList<T>
{

	public:
	
		//constructor, copy constructor, destructor
		arrayList(int initialCapacity = 10);
		arrayList(const arrayList<T>& theList);
		~arrayList(){ delete [] elements;}
	
		//abstract data type methods
		bool empty() const{ return(listSize == 0); }
		int size() const{ return(listSize); }
		T &operator[](int theIndex) const;
		T &get(int theIndex) const;
		int indexOf(const T &theElement) const;
		void erase(int theIndex);
		void insert(int theIndex, const T &theElement);
		void output(ostream &out) const;	
		void print_min_max() const;
		void print_current_size() const;
		void print_array() const;				// prints elements array. just for debugging
		
		friend std::ostream &operator<<(ostream& out, const arrayList<T> &x){

			x.output(out);
			return(out);

		}
		
		//additional methods
		int capacity() const { return(arrayLength); }
	
	protected:
	
		void changeLength(T*& a, int oldLength, int newLength);
		void checkIndex(int theIndex) const;			// throw -1 if theIndex is invalid
		T *elements;						// 1D array to hold elements
		int arrayLength;					// length of array;
		int listSize;						// number of elements contained in the listSize
		
};

//constructor
template<class T>
arrayList<T>::arrayList(int initialCapacity){				

	if(initialCapacity < 1){
	
		cout << "\nInitial capacity is < 1" << endl;
		exit(0);
	
	}
		
	arrayLength = initialCapacity;
	elements = new T[arrayLength];
	listSize = 0;
	
}

// copy constructor
template<class T>							
arrayList<T>::arrayList(const arrayList<T>& theList){			

	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	elements = new T[arrayLength];
	copy(theList.elements, theList.elements, elements);

}

//prints current size of list
template<class T>
void arrayList<T>::print_current_size() const{

	cout << "\nThe current list size is " << listSize << endl;

}

//verifies that theIndex is between 0 and listSize
template<class T>
void arrayList<T>::checkIndex(int theIndex) const{

	if(theIndex < 0 || theIndex > listSize){
		
		throw -1;
		
	}
	
}

//returns element whose index is theIndex
template<class T>
T &arrayList<T>::operator[](int theIndex) const{

	checkIndex(theIndex+1); 			// this call, along with all others is "hacked" because checkIndex() is specifically tailored to the insert method.
							// because insert needs to be able to insert successfully at the index just outside of the list, checkIndex() doesnt
							// throw on that index. but every other method needs to not do things on the first index just outside of list. hence 
							// the +1. checkIndex does throw for 2 outside of listSize which is the listSizeth+1 index.
	return(elements[theIndex]);

}

template<class T>
//returns by reference. a reference return type is automatically "dereferenced"
T &arrayList<T>::get(int theIndex) const{
	
	checkIndex(theIndex+1);
	return(elements[theIndex]);	

}

//returns index of first occurrence of theElement, return -1 if absent from list (unknown complexity))
template<class T>
int arrayList<T>::indexOf(const T &theElement) const{

	for(int i = 0; i < this->listSize; i++){
	
		if(elements[theElement] == theElement) return(i);
	
	}
	
	return(-1);

}

//removes element at theIndex and shifts everything down 1
template<class T>
void arrayList<T>::erase(int theIndex){

	checkIndex(theIndex+1);
	
	copy(elements+ theIndex + 1, elements + listSize, elements + theIndex);
	elements[--listSize].~T();
	

}
//inserts element at theIndex and shifts everything. doubles array size of array is too smaller
template<class T>
void arrayList<T>::insert(int theIndex, const T &theElement){

	checkIndex(theIndex);
	
	if( arrayLength == listSize ){ changeLength(elements, arrayLength, 2*arrayLength); arrayLength *= 2; }
	
	//backwards copy, otherwise copying copies forwards
	copy_backward(elements + theIndex, elements + listSize, elements + listSize + 1);

	elements[theIndex] = theElement;
	listSize++;
	
}

//inserts arrayList into output stream
template<class T>
void arrayList<T>::output(ostream& out) const{

	copy(elements, elements + listSize, ostream_iterator<T>(cout, " "));

}

//changes length by x amount
template<class T>
void arrayList<T>::changeLength(T*& a, int oldLength, int newLength){

	T* temp = new T[newLength];
	int number = min(oldLength, newLength);
	copy(a, a + number, temp);
	delete [] a;
	a = temp;
	

}
//prints min and max in arrayList. comparison operator needs overloading, assignment operator needs overloading
template<class T>
void arrayList<T>::print_min_max() const{

	T min = this->elements[0];
	T max = this->elements[0];
	
	for(int i = 1; i < listSize; i++){
	
		if(this->elements[i] >= max) max = this->elements[i];
		if(this->elements[i] <= min) min = this->elements[i];
	
	}
	
	cout << "\nThe minimum is: " << min;
	cout << "\nThe maximum is: " << max;
 
}

//prints the entire array elements inside arrayList. for debugging only
template<class T>							
void arrayList<T>::print_array() const{			

	for(int i = 0; i < 100; i++){
	
		cout << elements[i] << " ";
	
	}

}
#endif
