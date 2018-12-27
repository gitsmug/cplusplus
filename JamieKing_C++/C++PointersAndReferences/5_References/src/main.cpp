#include <iostream>

using std::cout;
using std::endl;

struct Cow
{
	int mooCount;
};

int main()
{
	cout << endl;
	cout << "Jamie King" << endl;
	cout << "https://www.youtube.com/user/1kingja" << endl;
	cout << endl;

	int i = 51;

	// References cannot change like pointers can.
	// Rererences can be handy for aliasing shitty variable names.
	int& i_ref = i;

	cout << i << endl;
	i_ref = 71;
	cout << i << endl;

	Cow betsy;
	betsy.mooCount = 999;

	Cow& betsy_ref = betsy;
	Cow* betsy_ptr = &betsy;

	cout << betsy.mooCount << endl;

	betsy_ref.mooCount = 13;
	cout << betsy.mooCount << endl;
	betsy_ptr->mooCount = 14;
	cout << betsy.mooCount << endl;

	return 0;
}