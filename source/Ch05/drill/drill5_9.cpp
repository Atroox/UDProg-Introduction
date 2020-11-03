#include "std_lib_facilities.h"

int main()
try {

	string s = " ape " ; bool c = true ; if (c) cout << " Success!\n " ;

	return 0;
	
} 
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	return 1;
} 
catch (...) {
	cerr << "Oops: unknown exception!\n";
	return 2;
}