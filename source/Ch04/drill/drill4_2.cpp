#include "std_lib_facilities.h"

int main()
{
	double a = 0;

	double min = numeric_limits<double>::max();
	double max = numeric_limits<double>::lowest();

	constexpr double cm_per_inch = 2.54;
	constexpr double cm_per_meter = 100;
	constexpr double in_per_feet = 12;

	double sum_of_values;

	double number_of_values =0;

	string unit_indicator;

	vector<double> v;

	while(cin >> a >> unit_indicator)
	{
		v.push_back(a);
		++number_of_values;

		if(a < min)
		{
			cout << a << " the smallest so far" << endl;
			min = a;
		}
		
		if(a > max)
		{
			cout << a << " the largest so far" << endl;
			max = a;
		}
		if(unit_indicator == "cm")
		{
			cout << a << unit_indicator << endl;
			sum_of_values += a/100;
		}

		if(unit_indicator == "m")
		{
			cout << a << unit_indicator << " = " << a*cm_per_meter << "cm" << endl;
			sum_of_values += a;
		}

		if(unit_indicator == "in")
		{
			cout << a << unit_indicator << " = " << a*cm_per_inch << "cm" << endl;
			sum_of_values += a*cm_per_inch/100;
		}

		if(unit_indicator == "ft")
		{
			cout << a << unit_indicator << " = " << a*in_per_feet << "in" << endl;
			sum_of_values += (a*in_per_feet*cm_per_inch)/100;
		}

	}

	cout << "The number of values: " << number_of_values << endl;

	cout << "The sum of values: " << sum_of_values << " m" << endl;

	sort(v.begin(), v.end());
	for(auto x : v)
		cout << x << " " << endl;

	if (a = '|')
		return 0;

	return 0;
}