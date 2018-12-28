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

class IEdible
{
public:
	IEdible() {}
	virtual ~IEdible() {}

	virtual void eat() = 0;
};

class Mamal : public IEdible
{
private:
	uint mass;

public:
	Mamal(uint mass)
		: mass(mass)
	{ }

	virtual ~Mamal()
	{
		cout << "~Mamal()" << endl;
	}

	virtual void resparate()
	{
		cout << "huff, puff..." << endl;
	}

	virtual void makeSound() = 0;
};

class Person final : public Mamal
{ 
private:
	static int myStaticInt;
	Heart stackHeart;
	Heart* heapHeart;

public:
	Person()
		: Mamal(123),
		stackHeart(12345),
		firstName("[empty]"),
		lastName("[empty]"),
		max_age(100)
	{
		cout << typeid(Person).name() << "()" << endl;
		heapHeart = new Heart();
	}

	Person(bool /* b */)
		: Mamal(123),
		heapHeart(nullptr),
		max_age(99)
	{ }

	Person(const Person& toCopy)
		: Mamal(123),
		stackHeart(toCopy.stackHeart),
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

	void makeSound() override
	{
		cout << "derp!" << endl;
	}

	void eat() override
	{
		cout << "NOM, NOM..." << endl;
	}

	string firstName;
	string lastName;
	const uint max_age;

	string ToString() const
	{
		return lastName + ", " + firstName + " max_age: " + to_string(max_age);
	}

	friend std::ostream& operator<<(std::ostream& stream, const Person& person)
	{
		stream << "operator<<: " << person.ToString();

		return stream;
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

	copidedYou.resparate();
	copidedYou.makeSound();
	copidedYou.eat();

	cout << copidedYou << endl;

	return 0;
}