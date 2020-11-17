#include "std_lib_facilities.h"

int main()
try {
    int birth_year = 2002;
    int a, b, c, d;
    double number = 1234567.89;

    cout << "decimal:\t" << birth_year << '\n' << hex
         << "hexadecimal:\t" << birth_year << '\n' << oct
         << "octal:\t\t" << birth_year << '\n';

    cout << dec << 18 << '\n';

    cout << '|' << setw(4) << "Ádám" << '|' << setw(6) << "Tamási" 
         << '|' << setw(21) << "adam.tmsi02@gmail.com"
         << '|' << setw(11) << "70 571 8172" << "|\n";
    
    cin >> a >>oct >> b >> hex >> c >> d;
	cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

	cout << defaultfloat << number << '\t' << fixed << number << '\t' << scientific << number << '\n';
}
catch(exception& e) {
    cerr << "Error: " << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "Something troubling occurred..\n";
    return 2;
}