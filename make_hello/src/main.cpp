#include <iostream>
#include "../include/make_hello/stuff/myclass.h"
#include "../include/make_hello/otherStuff/myotherclass.h"
#include "stuff/myclass_test.cpp"

#if !UNIT_TEST_MODE
int main()
{
	std::cout << "Hello, world." << std::endl;

	MyClass mc;
	mc.PrintTest();

	MyOtherClass oc;
	oc.OtherPrintTest();

	TestMyClass tmc;
	tmc.Test1();

	return 0;
}
#endif