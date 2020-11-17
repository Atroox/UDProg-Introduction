	#include "std_lib_facilities.h"

	//version 9.4.1:
	/*
	struct Date
	{
		int y;
		int m;
		int d;
	};

	void init_day(Date& dd, int y, int m, int d)
	{
		if(m<=0 || 12<m)
			error("invalid month");
		if(d<=0 || 31<d)
			error("Invalid day");

		dd.y=y;
		dd.m=m;
		dd.d=d;
	}

	void add_day(Date& dd, int n)
	{
		dd.d+=n;
		if(dd.d > 31) dd.d %= 31;
	}

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
	}


	int main()
	{
		Date today;
		init_day(today, 2020, 12, 16);
		Date tomorrow = today;
		add_day(tomorrow, 1);

		cout << today << '\n' << tomorrow << '\n';
		return 0;
	}
	*/
	//------------------------------------------------------------------

	//Version 9.4.2:
/*
struct Date{
	int y, m, d;
	Date(int y, int m, int d);
	void add_day(int n);
};

Date::Date(int yy, int mm, int dd)
:y{yy}, m{mm}, d{dd}
{
	if(mm<=0 || mm>12)
		error("Invalid month");
	if(dd<=0 || dd>31)
		error("Invalid day");
}

void Date::add_day(int n)
{
	d += n;
	if (d > 31) d %= 31;
}

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}

int main()
try{
	Date today(2020, 11, 16);
	cout << "today: " << today << '\n';
	Date tomorrow = today;
	tomorrow.add_day(1);
	cout << "tomorrow: " << tomorrow << '\n';


	return 0;
}
catch(exception& e)
{	
	cerr << e.what() << '\n';
	return 1;
}
catch(...) {
	cerr << "unknown error" << '\n';
	return 2;
}
*/
//---------------------------------------------------------------------------------------

//Version 9.4.3:
/*
class Date
{
	int y, m, d;

public:
	Date(int y, int m, int d);	//check for valid date and initialize
	void add_day(int n);		//increase the day by n days
	int month() const{ return m; }
	int day() const{ return d; }
	int year() const{ return y; }
};

Date::Date(int yy, int mm, int dd)
	:y{yy}, m{mm}, d{dd}
{
	if(d < 0 || d > 31) error("Invalid day");
	if(m <= 0 || m > 12) error("Invalid month");
}

void Date::add_day(int n)
{
	if(d > 31) d %= 31;
	d += n;
}

ostream& operator<<(ostream& os, const Date& d)
{
    return os << '(' << d.year()
              << ',' << d.month()
              << ',' << d.day() << ')';
}

int main()
try{
	Date today(2020, 11, 16);
	cout << "today: " << today << '\n';
	Date tomorrow = today;
	tomorrow.add_day(1);
	cout << "tomorrow: " << tomorrow << '\n';

	return 0;
}
catch(exception& e) {
    cerr << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "unknown error" << '\n';
    return 2;
}
*/

//-----------------------------------------------------------------------------------------------

//version 9.7.1:
/*
enum class Month
{
	jan,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec
};

vector<string> month_tbl = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

ostream& operator<<(ostream& os, Month m)
{
	return os << month_tbl[int(m)];
}

class Date
{
	int y;
	Month m;
	int d;
public: 
	Date(int y, Month m, int d);
	void add_day(int n);
	int year() const {return y;}
	Month month() const {return m;}
	int day() const {return d;}
};

Date::Date(int yy, Month mm, int dd)

:y{yy}, m{mm}, d{dd}
{
	if(d<=0 || d > 31) error("Invalid day");
}

void Date::add_day(int n)
{
	d += n;
	if (d <= 0 || d > 31) d %= 31;
}

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
}

int main()
try{
	Date today(2020, Month::oct,16);
	Date tomorrow = today;
    tomorrow.add_day(1);

	cout << "today: " << today << '\n' << "tomorrow: " << tomorrow << '\n';

	return 0;
}
catch(exception& e) {
	cerr << e.what() << '\n';
	return 1;
}
catch(...) {
	cerr << "unknown error" << '\n';
	return 2;
}
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

//version 9.7.4:

class Date
{
public:

	enum Month
	{
		jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec,
	};

	int day() const{ return d;}
	Month month() const{ return m;}
	int year() const { return y;}

	Date(int y, Month m, int d)
	:y{y}, m{m}, d{d}
	{}
	void add_day(int n);
	void add_month(int n);
	void add_year(int n);

private:
	int y;
	Month m;
	int d;
};

void Date::add_day(int n)
{
	d += n;
}

void Date::add_month(int n)
{
	m = Month(int(m)+1);
}

void Date::add_year(int n)
{
	y += n;
}

static ostream & operator<< (ostream & os, const Date::Month & m) {
	switch (m) {
		case Date::jan: os << "January"; break;
		case Date::feb: os << "February"; break;
		case Date::mar: os << "March"; break;
		case Date::apr: os << "April"; break;
		case Date::may: os << "May"; break;
		case Date::jun: os << "June"; break;
		case Date::jul: os << "July"; break;
		case Date::aug: os << "August"; break;
		case Date::sep: os << "September"; break;
		case Date::oct: os << "October"; break;
		case Date::nov: os << "November"; break;
		case Date::dec: os << "December"; break;
	}
	return os;
}

ostream & operator<< (ostream & os, const Date & dd) {
	os << "Year: " << dd.year() << " Month: " << dd.month() << " Day: " << dd.day() << endl;
	return os;
}

int main()
try{

	Date today(2020, Date::nov, 17);
	Date tomorrow = today;
	tomorrow.add_day(1);
	tomorrow.add_month(1);

	cout << "today: " << today << '\n' << "tomorrow: " << tomorrow << '\n';

	return 0;
}
catch(exception& e) {
	cerr << e.what() << '\n';
	return 1;
}
catch(...) {
	cerr << "unknown error" << '\n';
	return 2;
}