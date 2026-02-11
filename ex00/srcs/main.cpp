#include "BitcoinExchange.hpp"
#include <iostream>
#include <exception>
#include <map>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error in argv" << std::endl;
		return (1);
	}
	try
	{
		BitcoinExchange	btc;
		btc.handleBtc(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}

