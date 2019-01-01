#include <iostream>
#include "../include/make_hello/stuff/myclass.h"
#include "../../project3/src/stuff/project3Class.h"

namespace project2
{
	void MyClass::PrintTest()
	{
		std::cout << "Project2: PrintTest() from MyClass, call Project3:" << std::endl;

		project3::Project3Class p3c;
		p3c.PrintTest();
	}
}
