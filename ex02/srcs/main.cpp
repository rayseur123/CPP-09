#include <iostream>
#include "PmergeMe.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

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
	std::cout << "Before: ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it;
		if (it + 1 != vec.begin())
			std::cout << " ";
	}
	clock_t	start = std::clock();
	PmergeMe::mergeInsertSort(vec);
	clock_t	end = std::clock();
	std::cout << std::endl << "After: ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it;
		if (it + 1 != vec.begin())
			std::cout << " ";
	}
	std::cout << std::endl << "Time to process a range of with std::vector: " << ac - 1 << " " << end - start << " us";
	std::cout << std::endl << "Time to process a range of " << ac - 1 << " " << end - start << " us";
	return (0);
}

