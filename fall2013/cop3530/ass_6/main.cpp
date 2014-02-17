/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include "BinPacking.h"

using namespace std;

int main(){
	int choice, obs, cap, n;
	BinPacking* binpack;
	while(choice !=3){
		cout << "\nPlease choose the algorithm for test: 1. Firstfit 2. Bestfit; 3. Quit? ";
		cin >> choice;
		if(choice == 1){	
			cout << "\nEnter number of objects and bin capacity for First Fit" << endl;
			cin >> obs;
			cin >> cap;
			binpack = new BinPacking(true, obs, cap); 
			for(int i = 0; i < obs; i++){
				cout << "\nEnter space requirement of object " << i+1 << endl;
				cin >> n;
				binpack->firstFit(n);
			}
			delete binpack;
		}
		else if(choice == 2){		
			cout << "\nEnter number of objects and bin capacity for Best Fit" << endl;
			cin >> obs;
			cin >> cap;
			binpack = new BinPacking(false, obs, cap); 
			for(int i = 0; i < obs; i++){
				cout << "\nEnter space requirement of object " << i+1 << endl;
				cin >> n;
				binpack->bestFit(n);
			}
			delete binpack;
		}
		else if(choice == 3)
			return(0);
		else
			cout << "\nError invalid entry";
	}
}