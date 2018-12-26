#include <iostream>

using std::cout;
using std::endl;

int main()
{
	cout << endl;
	cout << "Jamie King" << endl;
	cout << "https://www.youtube.com/user/1kingja" << endl;
	cout << endl;

	const int agesCount = 4;

	int ages[agesCount];
	ages[0] = 21;
	ages[1] = 32;
	ages[2] = 55;
	ages[3] = 1;

	for (int i = 0; i < agesCount; i++)
	{
		cout << ages[i] << endl;
	}

	return 0;
}