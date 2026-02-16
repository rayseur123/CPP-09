#include <iostream>
#include "PmergeMe.hpp"
#include <vector>
#include <cstdlib>

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "Please enter an input." << std::endl;
		return (1);
	}
	std::vector<int> vec;
	for (int i = 1; i < ac; i++)
	{
		vec.push_back(std::atoi(av[i]));
	}
	mergeInsertSort(vec);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it << ",";
	}
	return (0);
}

