#include <iostream>

using std::cout;
using namespace std;

int main()
{
	cout << endl;
	cout << "Jamie King" << endl;
	cout << "https://www.youtube.com/user/1kingja" << endl;
	cout << endl;

	int myVar = 23;

	/* Defing pointer that points to address of int value.
	 * "Type*" means define pointer that points to address of thing of type Type.
	 * "&var" means address of value of var.
	 */
	int *myPointer = &myVar;

	/* Example of why it might be better to say "int *var" instead of "int* var":
	 * "int myVal, *ptr" is valid and makes more sense as "*myPtr" instead of "* ptr"
	 */

	cout << "value of pointer: " << myPointer << endl;
	cout << "dereference pointer to whatever it points at: " << *myPointer << endl;

	// At address pointed to by *var, assign value 15;
	*myPointer = 15;

	cout << "value of pointer: " << myPointer << endl;
	cout << "dereference pointer to whatever it points at: " << *myPointer << endl;


	int variable1 = 5;
	int variable2 = 10;
	int *pointer1 = &variable1;
	int *pointer2 = &variable1;

	cout << *pointer1 << endl;
	cout << *pointer2 << endl;

	pointer2 = &variable2;
	cout << *pointer2 << endl;

	*pointer2 = 25;
	cout << *pointer2 << endl;
	cout << variable2 << endl;

	pointer1 = pointer2;
	cout << *pointer1 << endl;

	return 0;
}