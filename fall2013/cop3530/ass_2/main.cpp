/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include <iostream> // necessary for cout, string, isdigit
#include <istream>
#include <sstream>  // necessary for stringstream
#include <cstdlib>  // necessary for exit()
#include <algorithm> //str to lower
#include <string>	// str transform
#include "ArrayLinearList.h"

using namespace std;


// data validation method. prevents arguments that aren't a choice or 'q' from being passed to switch in main
char alpha_sanitize(){
	//entry1 is returned but string methods are used entry
	char entry1;
	loop:
	while(1){

		string entry;
		cout << "\n\nPick a task to perform please by entering the letter in brackets\n\n";
		cout << "[I]nsert an element\n";
		cout << "[D]elete an element\n";
		cout << "[P]rint out the entire List\n";
		cout << "Print the Current [S]ize List\n";
		cout << "Print Particular [E]lement\n";
		cout << "Print the [M]aximum and the [M]inimum elements in the list\n";
		cout << "[Q]uit\n\n";
		
		getline(cin, entry, '\n');

		std::transform(entry.begin(), entry.end(), entry.begin(), ::tolower);
		system("clear");
		//scans to see if multiple words were entered
		for(int i = 0; i < entry.length(); i++){

			if(isspace(entry[i])){


			cout << "\nInvalid entry, hit enter please try again\n\n"; 
			cin.clear();
			cin.ignore(10000, '\n');
			//used because conditional is already inside a for loop
			goto loop;

			}

		}	
		if(entry != "c" && entry != "e" && entry != "i" && entry != "d" && entry != "p" && entry != "s" && entry != "q" && entry != "m"){ 

			cout << "\nInvalid entry, hit enter please try again\n\n"; 
			cin.clear();
			cin.ignore(10000, '\n');
			continue; 

		}

		if(entry == "q") exit(0);
		
		entry1 = entry.at(0);

		break;
				
	}
	
	
	return(entry1);

}
//data validation. prevents entries that aren't numbers. takes string to display instructions on what kind of number to enter
int num_sanitize(const string& str){

	string entry;

	loop:
	while(1){
	
		cout << endl << str;
	
		
		getline(cin, entry, '\n');

		for(int i = 0; i < entry.length(); i++){
		
			// walk through array entry and search for element that !isdigit or isspace. 
			// if every element isdigit then conditional is not activated and for loop exits normally
			if(!isdigit(entry[i]) || isspace(entry[i])){


			cout << "\nInvalid entry, hit enter please try again\n\n"; 
			cin.clear();
			cin.ignore(10000, '\n');
			//used because conditional is already inside a for loop
			goto loop;

			}
	
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

	arrayList<int> bobs(num_sanitize("Please enter capacity to initialize list to: ")); 

	int element = 0, index = 0;
	
	for(int i = 0; i < bobs.capacity(); i++){
	
		bobs.insert(i,i);
	
	}
		
	while(1){
		
		switch(alpha_sanitize()){
		
			case 'i':
			
		        system("clear");	
		    
			    element = num_sanitize("Please enter element to insert: ");
			    index = num_sanitize("Please enter index to insert at: ");
			
				try{ bobs.insert(index, element); }
				catch(...){ cout << ARRAY_ERROR; }
				
				break;
				
			case 'd':
			
				system("clear");

				index = num_sanitize("Please enter index to delete at: ");

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

				index = num_sanitize("Please enter index to view: ");

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
