#include <iostream>
#include "../include/make_hello/stuff/myclass.h"
#include "../include/make_hello/otherStuff/myotherclass.h"

#include "stuff/project3Class.h"

using namespace project3;

int main()
{
	std::cout << "Project3: Hello, world." << std::endl;

	MyClass mc;
	mc.PrintTest();

	MyOtherClass oc;
	oc.OtherPrintTest();

	Project3Class pc;
	pc.PrintTest();

	return 0;
}