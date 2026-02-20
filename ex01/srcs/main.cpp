#include "RPN.hpp"
#include <iostream>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error in argv" << std::endl;
		return (1);
	}
	try
	{
		Rpn	rpn;
		rpn.handleStack(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	
	return (0);
}

