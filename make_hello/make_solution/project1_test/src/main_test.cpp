#include <iostream>
#include "../src/stuff/myclass_test.cpp"

int main()
{
	std::cout << "Hello, test world." << std::endl;

	project1_test::TestMyClass tmc;
	tmc.Test1();

	return 0;
}
