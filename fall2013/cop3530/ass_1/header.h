/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#ifndef ASSIGNMENT_1
#define ASSIGNMENT_1
using namespace std;

// standard iterative factorial. doesn't accept numbers over 21, which cause overflow.
void print_factorial(long long int n){

	if(n >= 21){ cout << "\n" << n << " is too high for this puny computer. please enter a smaller number\n\n"; return;}
	long long int factorial = 1LL;
	for(int i = n; i >=1; i--){
	
		factorial *= i;
	
	}
	cout << '\n' << n << "!= " << factorial << '\n' << '\n';

}

#endif
