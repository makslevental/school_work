
#include <iostream>
#include "Linearlist.h"

using namespace std;

void userInputOutput (linearList* l, string dataStructure){
	
	for (int i = 0; i < 13; i++)
     		l->insert(i, i+1);
	cout<<"The initial "<<dataStructure<<" is: ";
	l->traverse();
	cout<<"welcome to the assignmet 3!"<<endl;
	while(true){

	char command;
	cout<<"Please enter  your command(I, D, P, E, S, M, Q):";
	cin>>command;
	int index;
	int value;
	switch(command){

		case 'I':
			cout<<"Enter the index:";
			cin>>index;
			cout<<"Enter the value:";
			cin>>value;
			l->insert(index, value);
			cout<<"After inserting the element "<<value<<" at the index of "<<index<<", The updated "<<dataStructure<<" is: ";
			l->traverse();
			break;
		case 'D':
			cout<<"Enter the index:";
			cin>>index;
			l->erase(index);
			cout<<"After erasing the element with index of "<<index<<", The updated "<<dataStructure<<" is: ";
			l->traverse();
			break;
		case 'P':
			cout<<"The linear list is: ";
			l->traverse();
			break;
		case 'E':
			cout<<"Enter the index:";
			cin>>index;
			if(l->get(index))cout<<"The element at the index of "<<index<<" is "<<*(l->get(index))<<endl;
			break;
 		case 'S':
			cout<<"The current size of the "<<dataStructure<<" is "<<l->size()<<endl;
			break;
		case 'M':
			l->MaxMin();
			break;
		case 'Q':
			cout<<"The program is going to quit!"<<endl;
			return ;
	 	default:
            		cout<<"You have entered the incorrect command!"<<endl;
			break;
	
		}
	}
}
