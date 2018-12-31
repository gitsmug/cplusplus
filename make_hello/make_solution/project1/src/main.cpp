#include <iostream>

#include "../include/make_hello/stuff/myclass.h"
#include "../include/make_hello/otherStuff/myotherclass.h"

#include "../../project2/src/stuff/project2Class.h"
#include "../../project2/include/make_hello/stuff/myclass.h"

int main()
{
	std::cout << "Project1: Hello, world." << std::endl;

	project1::MyClass mc;
	mc.PrintTest();

	/* lib from project2
	 * For this to work I had to ensure that Project 1 and 2's
	 * header guards are different.
	 */
	project2::MyClass mcFromProject2;
	mcFromProject2.PrintTest();

	project1::MyOtherClass oc;
	oc.OtherPrintTest();

	project2::Project2Class pc;
	pc.PrintTest();

	return 0;
}