#include <iostream>

using std::cout;
using std::endl;

int main()
{
	cout << endl;
	cout << "Jamie King" << endl;
	cout << "https://www.youtube.com/user/1kingja" << endl;
	cout << endl;

	// This is really a pointer.
	int ages[4];
	ages[0] = 32;
	ages[1] = 6;

	int* ptr = ages;

	cout << ages << endl;
	cout << ptr << endl;

	cout << *ptr << endl;
	cout << *(ptr + 0) << endl;
	cout << ages[0] << endl;
	cout << *(ages + 0) << endl;
	
	cout << *(ptr + 1) << endl;
	cout << ages[1] << endl;

	return 0;
}