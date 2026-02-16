#include "PmergeMe.hpp"
#include <vector>
#include <utility>
#include <algorithm>
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

std::vector<int> buildBigTab(std::vector<std::pair<int, int> >& pairs)
{
    std::vector<int> ret;
    for (size_t i = 0; i < pairs.size(); i++)
        ret.push_back(pairs[i].first);
    return (ret);
}

void reorderedPairs(std::vector<std::pair<int, int> >& pairs,
                    std::vector<int>& largerElements)
{
    std::vector<std::pair<int, int> > sortedPairs;
    std::vector<bool> used(pairs.size(), false);
    
    for (size_t i = 0; i < largerElements.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] && pairs[j].first == largerElements[i])
            {
                sortedPairs.push_back(pairs[j]);
                used[j] = true;
                break;
            }
        }
    }
    pairs = sortedPairs;
}

std::vector<size_t> generateJacobsthal(size_t maxSize)
{
    std::vector<size_t> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    
    while (true)
    {
        size_t next = jacobsthal[jacobsthal.size() - 1] + 
                      2 * jacobsthal[jacobsthal.size() - 2];
        if (next >= maxSize)
            break;
        jacobsthal.push_back(next);
    }
    return (jacobsthal);
}

std::vector<size_t> getInsertionOrder(size_t count)
{
    if (count == 0)
        return std::vector<size_t>();
    
    std::vector<size_t> order;
    std::vector<size_t> jacobsthal = generateJacobsthal(count + 1);
    std::vector<bool> inserted(count, false);
    
    for (size_t i = 1; i < jacobsthal.size(); i++)
    {
        size_t pos = jacobsthal[i];
        size_t prev = jacobsthal[i - 1];
        
        for (size_t j = std::min(pos - 1, count - 1); j > prev && j < count; j--)
        {
            if (!inserted[j])
            {
                order.push_back(j);
                inserted[j] = true;
            }
        }
    }
    
    for (size_t i = 0; i < count; i++)
    {
        if (!inserted[i])
            order.push_back(i);
    }
    
    return order;
}

void insertSmalestElements(std::vector<int>& container, 
                           std::vector<int>& largerElements,
                           std::vector<std::pair<int, int> >& pairs,
                           int odd)
{
    std::vector<int> buff = largerElements;
    
    if (!pairs.empty())
        buff.insert(buff.begin(), pairs[0].second);
    
    if (pairs.size() > 1)
    {
        std::vector<size_t> insertionOrder = getInsertionOrder(pairs.size() - 1);
        
        for (size_t i = 0; i < insertionOrder.size(); i++)
        {
            size_t index = insertionOrder[i] + 1;
            if (index < pairs.size())
            {
                int smallerToInsert = pairs[index].second;
                std::vector<int>::iterator position = 
                    std::lower_bound(buff.begin(), buff.end(), smallerToInsert);
                buff.insert(position, smallerToInsert);
            }
        }
    }
    
    if (odd != -1)
    {
        std::vector<int>::iterator position = 
            std::lower_bound(buff.begin(), buff.end(), odd);
        buff.insert(position, odd);
    }
    
    container = buff;
}

void mergeInsertSort(std::vector<int>& container)
{
    if (container.size() <= 1)
        return;
    
    std::vector<std::pair<int, int> > pairs = doPairs(container);
    std::vector<int> largerElements = buildBigTab(pairs);
    int odd = -1;
    
    if (container.size() % 2 == 1)
        odd = container[container.size() - 1];
    
    mergeInsertSort(largerElements);
    reorderedPairs(pairs, largerElements);
    insertSmalestElements(container, largerElements, pairs, odd);
}