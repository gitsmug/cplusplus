#include <iostream>

using std::cout;
using std::endl;

#include <string>
using std::string;

/* Structs default to public accessability.
 * Classes default to private accessibility.
 * That's about it for the differences in C++
 */

class Person
{
public:
	Person()
		:firstName("[empty]"),
		lastName("[empty]")
	{ }

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


	Person personOnStack;

	cout << personOnStack.ToString() << endl;

	personOnStack.firstName = "Jamie";
	personOnStack.lastName = "King";

	cout << personOnStack.ToString() << endl;

	return 0;
}