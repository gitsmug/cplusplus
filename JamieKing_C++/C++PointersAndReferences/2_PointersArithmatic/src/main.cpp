#include <iostream>

using std::cout;
using namespace std;

int main()
{
	cout << endl;
	cout << "Jamie King" << endl;
	cout << "https://www.youtube.com/user/1kingja" << endl;
	cout << endl;

	//int myInt = 9;
	const int length = 5;
	int* myIntPtr = new int[length];

	cout << "sizeof=" << sizeof(myIntPtr) << endl;
	cout << myIntPtr << endl;
	cout << *myIntPtr << endl;
	cout << endl;

	for (int i = 0; i < length; i++)
	{
		cout << myIntPtr[i] << endl;
	}

	cout << endl;

	for (int i = 0; i < length; i++)
	{
		myIntPtr[i] = i * 2;
	}

	cout << endl;

	for (int i = 0; i < length; i++)
	{
		cout << myIntPtr[i] << endl;
	}

	cout << endl;

	int* ptr = myIntPtr;
	cout << *ptr << endl;
	cout << ptr << endl;
	ptr += 1;
	cout << ptr << endl;

	cout << endl;

	for (int* ptr = myIntPtr; ptr < myIntPtr + length; ptr++)
	{
		cout << *ptr << endl;
	}

	delete[] myIntPtr;

	return 0;
}