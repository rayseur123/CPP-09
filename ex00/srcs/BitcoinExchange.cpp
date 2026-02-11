#include "BitcoinExchange.hpp"
#include <iostream>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define DATA_PATH "data/data.csv"

void	BitcoinExchange::display_map() const
{
	std::cout << "display map" << std::endl;
	for (std::map<std::time_t, float>::const_iterator it = btcMap_.begin(); it != btcMap_.end(); it++)
	{
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
	}
}

void	BitcoinExchange::addData(std::string& date, std::string& value)
{
	struct tm	tm = {};
	float		tempf;

	if (!strptime(date.c_str(), "%Y-%m-%d", &tm) || !sscanf(value.c_str(), "%f", &tempf))
		throw(std::logic_error("Error in the data file"));
	btcMap_.insert(std::make_pair(mktime(&tm), tempf));
}

void	BitcoinExchange::fillingDataMap(std::ifstream& dataFile)
{
	std::string	value;
	std::string	date;

	std::getline(dataFile, value);
	while (!dataFile.eof())
	{
		std::getline(dataFile, date, ',');
		std::getline(dataFile, value);
		if (!dataFile.eof())
			this->addData(date, value);
	}
}

static bool	handleError(std::string sDate, std::string value, float& fValue, struct tm& tm)
{
	if (!strptime(sDate.c_str(), "%Y-%m-%d", &tm))
	{
		std::cout << "Error: Invalid date format." << std::endl;
		return (0);
	}
	else if (!sscanf(value.c_str(), "%f", &fValue))
	{
		std::cout << "Error: Invalid float value." << std::endl;
		return (0);
	}
	else if (fValue < 0.0f)
	{
		std::cout << "Error: Not a positive number." << std::endl;
		return (0);
	}
	else if (fValue > 1000.0f)
	{
		std::cout << "Error: too large a number." << std::endl;
		return (0);
	}
	return (1);
}

void	BitcoinExchange::getAmountBtc(std::ifstream& inputFile)
{
	std::string								line;
	std::string								sDate;
	std::string								value;
	std::string::size_type					index;
	struct tm								tm = {};
	float									fValue;
	std::map<std::time_t, float>::iterator	it;

	std::getline(inputFile, line);
	while (!inputFile.eof())
	{
		std::getline(inputFile, line);
		index = line.find(" | ");
		sDate = line.substr(0, index);
		if (line.length() >= index + 3)
			value = line.substr(index + 3);
		else
		{
			std::cout << "Error: Invalid date format." << std::endl;
			continue;
		}
		if (!handleError(sDate, value, fValue, tm))
			continue;
		it = btcMap_.upper_bound(mktime(&tm));
		if (it-- != btcMap_.end())
			std::cout << sDate << " => " << value << " = " << it->second * fValue << std::endl;
	}
}

void	BitcoinExchange::handleBtc(std::string inputName)
{
	std::ifstream					inputFile(inputName.c_str());
	std::ifstream					dataFile(DATA_PATH);
	
	if (!inputFile.is_open())
	 	throw (std::logic_error("File open fail"));
	if (!dataFile.is_open())
		throw (std::logic_error("File open fail"));
	this->fillingDataMap(dataFile);
	this->getAmountBtc(inputFile);
}

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& toCopy)
: btcMap_(toCopy.btcMap_)
{}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange const& BitcoinExchange::operator=(BitcoinExchange const& toCopy)
{
	if (this == &toCopy)
		return (*this);
	btcMap_ = toCopy.btcMap_;
	return (*this);
}