#include <iostream>
#include "../include/make_hello/stuff/myclass.h"
#include "../include/make_hello/otherStuff/myotherclass.h"

#include "stuff/project2Class.h"

using namespace project2;

int main()
{
	std::cout << "Project2: Hello, world." << std::endl;

	MyClass mc;
	mc.PrintTest();

	MyOtherClass oc;
	oc.OtherPrintTest();

	Project2Class pc;
	pc.PrintTest();

	return 0;
}