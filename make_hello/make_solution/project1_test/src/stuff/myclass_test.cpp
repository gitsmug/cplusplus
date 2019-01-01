#include <iostream>
#include "../../../project1/include/make_hello/stuff/myclass.h"

using project1::MyClass;

namespace project1_test
{
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
}