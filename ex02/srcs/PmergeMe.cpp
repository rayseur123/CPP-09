#include "PmergeMe.hpp"
#include <vector>
#include <utility>
#include <iostream>

std::vector<std::pair<int, int> > doPairs(std::vector<int>& container)
{
    std::vector<std::pair<int, int> > ret;
    
    for (size_t i = 0; i + 1 < container.size(); i += 2)
    {
        int first = container[i];
        int second = container[i + 1];
        
        if (first < second)
            ret.push_back(std::make_pair(second, first));
        else
            ret.push_back(std::make_pair(first, second));
    }
    return (ret);
}

std::vector<int>	buildBigTab(std::vector<std::pair<int, int> >& vPairs)
{
	std::vector<int>	ret;

	for (size_t i = 0; i < vPairs.size(); i++)
	{
		ret.push_back(vPairs[i].first);
	}
	return (ret);
}

void	sortPairs(std::vector<std::pair<int, int> >& vPairs,
				  std::vector<int>& largerElements)
{
	std::vector<std::pair<int, int> > sortedPairs;

    for (size_t i = 0; i < largerElements.size(); i++)
    {
        for (size_t j = 0; j < vPairs.size(); j++)
        {
            if (vPairs[j].first == largerElements[i])
            {
                sortedPairs.push_back(vPairs[j]);
                break;
            }
        }
    }
	vPairs = sortedPairs;
}

void	insertSmalestElements(std::vector<int>& container, 
							  std::vector<int>& largerElements,
							  std::vector<std::pair<int, int> >& vPairs,
							  int odd)
{
	std::vector<int> buff = largerElements;
	buff.insert(buff.begin(), vPairs[0].second);

	for (size_t i = 1; i < vPairs.size(); i++)
	{
		int smallerToInsert = vPairs[i].second;
		std::vector<int>::iterator	position = std::lower_bound(buff.begin(), buff.end(), smallerToInsert);
		buff.insert(position, smallerToInsert);
	}
	if (odd != -1)
	{
		std::vector<int>::iterator	position = std::lower_bound(buff.begin(), buff.end(), odd);
		buff.insert(position, odd);
	}
	container = buff;
}

void	mergeInsertSort(std::vector<int>& container)
{
	if (container.size() <= 1)
        return;

	std::vector<std::pair<int, int> >	vPairs = doPairs(container);
	std::vector<int>					largerElements = buildBigTab(vPairs);
	int									odd = -1;

    if (container.size() % 2 == 1)
	{
        odd = container[container.size() - 1];
	}

	mergeInsertSort(largerElements);
	sortPairs(vPairs, largerElements);
	insertSmalestElements(container, largerElements, vPairs, odd);
}