#include <iostream>
#include "../include/make_hello/stuff/myclass.h"
#include "../../project2/include/make_hello/stuff/myclass.h"

namespace project1
{
	void MyClass::PrintTest()
	{
		std::cout << "Project1: PrintTest() from MyClass" << std::endl;

		project2::MyClass mcFromProject2;
		mcFromProject2.PrintTest();
	}
}