/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include <iostream> // necessary for cout, string, isdigit
#include <sstream>  // necessary for stringstream
#include <cstdlib>  // necessary for exit()
#include "header.h"
using namespace std;


// data validation method. prevents arguments that aren't a number or 'q' from being passed to print_factorial() in header
string sanitize(){
	
	loop:
	while(1){
	
		cout << "Enter a number less than or equal to 20 (or enter ‘q’ to quit): ";
	
		// static declaration so that later *sanitized can point to it after method returns
		string entry;
		cin >> entry;
	
		if(entry == "q") exit(0);
	
		for(int i = 0; i < entry.length(); i++){
		
			// walk through array entry and search for element that !isdigit. if !isdigit then set *sanitized to NULL pointer
			// and return from method. if every element isdigit then conditional is not activated and for loop exits normally
			if(!isdigit(entry[i])){ cout << "\nInvalid entry, please try again\n\n"; goto loop;} 
	
		}
	
	}
	// if for loop finishes normally then set *sanitized to point to string entry and return 
	stringstream actual_entry;
	long long int n;
	actual_entry << entry;
	actual_entry >> n;
	
	return(n);

}


void choice(string *sanitized){
	
	// choice takes pointer. if sanitize() returns pointer to NULL then conditional isn't activated and choice return and while 
	// loop in main() reruns. if sanitized!=NULL then stringstream actual_entry converts string which was input in sanitize() to
	// long long int and then passes it to print_factorial(), stored in header.h
	if(sanitized!=NULL){
		
		
		stringstream actual_entry;
		long long int n;
		actual_entry << *sanitized;
		actual_entry >> n;

		print_factorial(n);
		
	}

}

int main()
{
	
	while(1){
	
		choice(sanitize());
		
	}
	
	
}
