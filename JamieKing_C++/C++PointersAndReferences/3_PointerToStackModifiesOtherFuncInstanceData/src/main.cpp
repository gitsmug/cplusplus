#include <iostream>

using std::cout;
using std::cout;
using std::endl;

const int valueToLookFor = 92;
const int valueToPlowOverWith = 667;

void function2()
{
	int f2Int;
	int* ptr = &f2Int;

	for (int i = 0; i < 20; i++)
	{
		int &valueRef = *(ptr + i);
		//cout << valueRef << endl;

		// Mess with data on stack that's out of our scope because we suck.
		if (valueRef == valueToLookFor)
		{
			valueRef = valueToPlowOverWith;
			break;
		}
	}
}

void function1()
{
	int f1Int = valueToLookFor;
	cout << f1Int << endl;
	function2();
	cout << f1Int << endl;
}

int main()
{
	cout << endl;
	cout << "Jamie King" << endl;
	cout << "https://www.youtube.com/user/1kingja" << endl;
	cout << endl;

	function1();

	return 0;
}