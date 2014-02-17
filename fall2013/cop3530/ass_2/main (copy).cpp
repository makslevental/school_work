/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include <iostream> // necessary for cout, string, isdigit
#include <ostream>
#include <sstream>  // necessary for stringstream
#include <cstdlib>  // necessary for exit()
#include <locale>   // locale, tolower
#include "ArrayLinearList.h"

using namespace std;


// data validation method. prevents arguments that aren't a choice or 'q' from being passed to switch in main
char alpha_sanitize(){
	
	char entry = '\0';
	while(1){
	
		cout << "\nPick a task to perform please by entering the letter in brackets\n\n";
		cout << "[I]nsert an element\n";
		cout << "[D]elete an element\n";
		cout << "[P]rint out the entire List\n";
		cout << "Print the Current [S]ize List\n";
		cout << "Print Particular [E]lement\n";
		cout << "Print the [M]aximum and the [M]inimum elements in the list\n";
		cout << "[Q]uit\n\n";
		
		cin >> entry;
		entry = tolower(entry);
		system("clear");	
		if(entry != 'c' && entry != 'e' && entry != 'i' && entry != 'd' && entry != 'p' && entry != 's' && entry != 'q' && entry != 'm') { cout << "\nError, Invalid entry\n"; continue; }

		if(entry == 'q') exit(0);
		
		break;
		
		
	}
	
	
	return(entry);

}
int num_sanitize(){

	string entry;

	loop:
	while(1){
	
		cout << "\nEnter the capacity you would like to initialize the list (or enter ‘q’ to quit): ";
	
		// static declaration so that later *sanitized can point to it after method returns
		
		cin >> entry;
	
		if(entry == "q") exit(0);
	
		for(int i = 0; i < entry.length(); i++){
		
			// walk through array entry and search for element that !isdigit. if !isdigit then set *sanitized to NULL pointer
			// and return from method. if every element isdigit then conditional is not activated and for loop exits normally
			if(!isdigit(entry[i])){ cout << "\nInvalid entry, please try again\n\n"; goto loop;} 
	
		}
		break;
	}
	// if for loop finishes normally then set *sanitized to point to string entry and return 
	stringstream actual_entry;
	long long int n;
	actual_entry << entry;
	actual_entry >> n;
	
	return(n);

}

int main()
{

	arrayList<int> bobs(num_sanitize()); 

	int element = 0, index = 0;
	
	for(int i = 0; i < bobs.capacity(); i++){
	
		bobs.insert(i,i);
	
	}
		
	while(1){
		
		switch(alpha_sanitize()){
		
			case 'i':
			
			       system("clear");	
			       
			       while(1) {
				
				    cout << "\nPlease enter element to insert: ";
				    if(cin >> element) break;
				    else{
				    
					cout << "\nError: Please enter a valid integer\n" ;
					cin.clear();
					cin.ignore(10000,'\n');
						
				    }
				}
				
				while(1){
				
				    cout << "\nPlease enter index to insert at: ";
				    if(cin >> index) break;
				    
				    else{
				    
					cout << "\nError: Please enter a valid integer\n" << endl; 
					cin.clear();
					cin.ignore(10000,'\n');
				    
				    }
				    				    
				}
				
				try{ bobs.insert(index, element); }
				catch(...){ cout << ARRAY_ERROR; }
				
				break;
				
			case 'd':
			
				system("clear");	
				while(1) {
				    cout << "\nPlease enter index to delete at: ";
				    if (cin >> index) break;
				    else{
				    
					cout << "\nError: Please enter a valid integer\n" << endl; //array bounds!!!!!!!!!!!!!!!!!
					cin.clear();
					cin.ignore(10000,'\n');
					
				    }
				}
				try{ bobs.erase(index); }
				catch(...){ cout << ARRAY_ERROR; }
				break;
				
			case 'p':
			
				system("clear");	
				cout << bobs << endl;
				break;
				
			case 's':
			
				system("clear");	
				bobs.print_current_size();
				break;
				
			case 'm':
			
				system("clear");	
				bobs.print_min_max();	
				break;
					
			case 'e':
			
				system("clear");
				while(1){
				
				    cout << "\nPlease enter index: ";
				    if(cin >> index) break;
				    
				    else{
				    
					cout << "\nError: Please enter a valid integer\n" << endl; 
					cin.clear();
					cin.ignore(10000,'\n');
				    
				    }
				    				    
				}
				try{ cout << endl << bobs[index] << endl; }
				catch(...){ cout << ARRAY_ERROR; }	
				break;
				
			case 'c': // super secret debugging case
			
				cout << bobs.capacity();
				cout << endl << endl;
				bobs.print_array();
				
		
			}
			
	}	
		
}
