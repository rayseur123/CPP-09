#include <iostream>
#include "PmergeMe.hpp"
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>

void	testVector(std::vector<int> vec, int ac)
{
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
}

void	testDeque(std::deque<int> deq, int ac)
{
	clock_t	start = std::clock();
	PmergeMe::mergeInsertSort(deq);
	clock_t	end = std::clock();
	std::cout << std::endl << "Time to process a range of with std::deque: " << ac - 1 << " " << end - start << " us";
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "Please enter an input." << std::endl;
		return (1);
	}

	std::vector<int>	vec;
	std::deque<int>		deque;

	for (int i = 1; i < ac; i++)
		vec.push_back(std::atoi(av[i]));
	for (int i = 1; i < ac; i++)
		deque.push_back(std::atoi(av[i]));

	std::cout << "Before: ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		std::cout << *it;
		if (it + 1 != vec.begin())
			std::cout << " ";
	}

	testVector(vec, ac);
	testDeque(deque, ac);
	return (0);
}
