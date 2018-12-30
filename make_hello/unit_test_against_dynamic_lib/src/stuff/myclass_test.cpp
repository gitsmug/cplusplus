#include <iostream>
#include "../../include/make_hello/stuff/myclass.h"

class TestMyClass
{
public:
	void Test1()
	{
		std::cout << "Test1(): Testing MyClass::PrintTest()..." << std::endl;
	
		MyClass mc;
		mc.PrintTest();
	}
};