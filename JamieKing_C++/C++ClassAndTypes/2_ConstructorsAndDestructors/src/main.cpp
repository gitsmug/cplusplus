#include <iostream>

using std::cout;
using std::endl;

#include <string>
using std::string;

class Person
{
public:
	Person()
		:firstName("[empty]"),
		lastName("[empty]")
	{
		cout << "Person()" << endl;
	}

	~Person()
	{
		cout << "~Person()" << endl;
	}

	string firstName;
	string lastName;

	string ToString()
	{
		return lastName + ", " + firstName;
	}
};

int main()
{
	cout << endl;
	cout << "Jamie King" << endl;
	cout << "https://www.youtube.com/user/1kingja" << endl;
	cout << endl;


	cout << "enter scope..." << endl;

	{
		Person personOnStack;
	}

	cout << "... exit scope" << endl;

	return 0;
}