#include <iostream>

using std::cout;
using std::endl;

#include <string>
using std::string;
using std::to_string;

/* Structs default to public accessability.
 * Classes default to private accessibility.
 * That's about it for the differences in C++
 */
class Heart
{
	uint numBeatsLeft;

public:
	Heart()
		: numBeatsLeft(0)
	{
		cout << "Heart()" << endl;
	}

	Heart(uint numBeatsLeft)
		: numBeatsLeft(numBeatsLeft)
	{ }

	~Heart()
	{
		cout << "~Heart()" << endl;
	}
};

class Person
{ 
private:
	static int myStaticInt;
	Heart stackHeart;
	Heart* heapHeart;

public:
	Person()
		: stackHeart(12345),
		firstName("[empty]"),
		lastName("[empty]"),
		max_age(100)
	{
		cout << "Person()" << endl;
		heapHeart = new Heart();
	}

	Person(bool /* b */)
		: heapHeart(nullptr),
		max_age(99)
	{ }

	Person(const Person& toCopy)
		: stackHeart(toCopy.stackHeart),
		firstName(toCopy.firstName),
		lastName(toCopy.lastName),
		max_age(toCopy.max_age)
	{
		heapHeart = new Heart(*toCopy.heapHeart);
	}

	~Person()
	{
		cout << "~Person()" << endl;

		delete heapHeart;
	}

	string firstName;
	string lastName;
	const uint max_age;

	string ToString()
	{
		return lastName + ", " + firstName + " max_age: " + to_string(max_age);
	}
};

int Person::myStaticInt = 50;

int main()
{
	cout << endl;
	cout << "Jamie King" << endl;
	cout << "https://www.youtube.com/user/1kingja" << endl;
	cout << endl;


	cout << "enter scope..." << endl;

	{
		Person personOnStack;
		cout << personOnStack.ToString() << endl;
	}

	cout << "... exit scope" << endl;

	Person p1;
	Person p2(true);

	cout << p1.ToString() << endl;
	cout << p2.ToString() << endl;

	Person copyMe;
	copyMe.firstName = "dumb";
	Person copidedYou(copyMe);

	cout << copyMe.ToString() << endl;
	cout << copidedYou.ToString() << endl;

	return 0;
}