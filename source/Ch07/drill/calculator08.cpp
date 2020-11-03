/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

/* GRAMMAR
  =======
  Calculation:
       Statement
       Print
       Quit
       Calculation Statement
 
  Statement:
       Declaration
       Expression
  
  Declaration:
       "let" Name "=" Expression
 
  Expression:
       Term
       Expression + Term
       Expression - Term
 
  Term:
       Primary
       Term * Primary
       Term / Primary
       Term % Primary
 
  Primary:
       Number
       ( Expression )
       - Primary
       ? Primary
       Primary ^ Primary
 
  Number:
       floating-point-literal
 */

#include "std_lib_facilities.h"

struct Token {
	char kind;		//what kind of token 
	double value;	//for numbers:a value 
	string name;
	Token(char ch) :kind(ch), value(0) { }		//make a token from a char
	Token(char ch, double val) :kind(ch), value(val) { }		//make a token from a char and a double
	Token(char ch, string n) :kind(ch), name(n) { }				//make a token from a char and a string 
};

class Token_stream {
	bool full;	// is there a Token in the buffer?
	Token buffer;	// here is where we keep a Token put back using putback()
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();		//get a token 
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char c);	// discard characters up to and including a c
};

const char let = 'L';
const char quit = 'Q';		//Q for quitting the program
const char print = '=';		//= for printing the result 
const char number = '8';	//8 to represent the numbers
const char name = 'a';
const char square_root = '?';

Token Token_stream::get()	// read characters from cin and compose a Token
{
	if (full) { full = false; return buffer; }	// check if we already have a Token ready
	char ch;
	cin >> ch;		// note that >> skips whitespace (space, newline, tab, etc.)
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case print:
	case quit:
	case square_root:
		return Token(ch);	// let each character represent itself
	case '.':	// a floating-point-literal can start with a dot
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.putback(ch);	// put digit back into the input stream
	double val;
	cin >> val;		// read a floating-point number
	return Token(number, val);
	}
	default:
		if (isalpha(ch))
		{
			string s;
			s += ch;
			while (cin.get(ch) && isalpha(ch) || isdigit(ch)) s += ch;
			cin.unget();
			if (s == "L") return Token(let);
			if (s == "Q") return Token(name);
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {		//look in buffer 
		full = false;
		return;
	}
	full = false;

	char ch = 0;		//look for input 
	while (cin >> ch)		
		if (ch == c) return;
}

struct Variable {		//introducing variables 
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)	//return the value of string s 
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

void set_value(string s, double d)	//set variable named s to d
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool is_declared(string s)		
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
	t = ts.get();
	if (t.kind != ')') error("')' expected");
	return d;
	}
	case '-':
		return primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	case square_root:
	{
		double d = primary();
		if(d < 0) error("Can't sqrt() negative numbers");	
		return sqrt(d); 
	}
	default:
		error("primary expected");
	}
}


double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}
double define_name(string n, double v)
{
	if (is_declared(n)) error(n, " declared twice");	//see if name is already declared 
	names.push_back(Variable(n, v));
	return v;

}
double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);
	double d = expression();
	names.push_back(Variable(name, d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()	//resets program after an error 
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();	//discard all "prints"
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;		//Write error message
		clean_up_mess();
	}
}

int main()

try {
	 define_name("pi",3.1415926535);		//defining variables 
	 define_name("e",2.7182818284);
	 define_name("k", 1000);


	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != '=');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != '=');
	return 2;
}