#include <iostream>
#include "../include/make_hello/stuff/myclass.h"
#include "../include/make_hello/otherStuff/myotherclass.h"

#include "stuff/project2Class.h"

#include "../../project3/src/stuff/project3Class.h"
#include "../../project3/include/make_hello/stuff/myclass.h"

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

	project3::Project3Class p3c;
	p3c.PrintTest();

	return 0;
}