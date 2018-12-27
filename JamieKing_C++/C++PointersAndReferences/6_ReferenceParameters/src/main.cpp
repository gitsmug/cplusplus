#include <iostream>

using std::cout;
using std::endl;

struct Cow
{
	int mooCount = 0;
};

void makeCowMoo_byCopy(Cow cow)
{
	cow.mooCount++;
}

void makeCowMoo_byRef(Cow& cow)
{
	cow.mooCount++;
}

void printNumMoos(const Cow& cow)
{
	cout << cow.mooCount << endl;
}

int main()
{
	cout << endl;
	cout << "Jamie King" << endl;
	cout << "https://www.youtube.com/user/1kingja" << endl;
	cout << endl;

	Cow betsy;
	betsy.mooCount = 9;

	makeCowMoo_byCopy(betsy);
	cout << betsy.mooCount << endl;

	makeCowMoo_byRef(betsy);
	cout << betsy.mooCount << endl;

	printNumMoos(betsy);

	return 0;
}