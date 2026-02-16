#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>

class PmergeMe
{
	private:
	public:
		static void	mergeInsertSort(std::vector<int>& container);
		static void	mergeInsertSort(std::deque<int>& container);

		PmergeMe();
		PmergeMe(PmergeMe const& toCopy);
		~PmergeMe();

		PmergeMe const&	operator=(PmergeMe const& toCopy);
};





#endif