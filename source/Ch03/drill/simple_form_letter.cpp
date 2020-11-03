#include "std_lib_facilities.h"

int main()
{
	cout << "Enter the name of the person you want to write to: \n";
	string first_name;
	cin >> first_name;
	cout << "Dear " << first_name << "," "\n";
	cout << "How are you?\n";
	cout << "I am fine. \n";
	cout << "I miss you \n";
	cout << "I'm writing to tell you that I'm coming to Debrecen next week and I'd like to meet up with you. \n";

	cout << "Enter the name of another friend! \n";
	string friend_name;
	cin >> friend_name;

	cout << "Have you seen " << friend_name << " lately?\n";

	char friend_sex ='0';
	cout << "If the friend is male enter 'm' if not enter 'f' \n";
	cin >> friend_sex;

	if(friend_sex=='m')
		cout << "If you see " << friend_name << " please ask him to call me. \n";
	
	else
		cout << "If you see " << friend_name << " please ask her to call me. \n";

	cout << "Enter the age of the recipient, \n";
	int age;
	cin >> age;

	cout << "I hear you just had a birthday and you are " << age << " years old.\n";
	if(age >= 110)
		simple_error("you're kidding!");
	if(age <= 0)
		simple_error("you're kidding!");
	if(age < 12 )
		cout << "Next year you will be " << age+1 << "\n";
	if(age == 17)
		cout << "Next year you will be able to vote.\n";
	if(age > 70)
		cout << "I hope you are enjoying retirement.\n";

	cout << "Yours sincerely	Tamási Ádám.\n";

	return 0;
}