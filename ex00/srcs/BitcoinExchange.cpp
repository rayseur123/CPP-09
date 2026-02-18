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

static bool	checkIsFloat(std::string sFloat)
{
	bool	dot = false;
	size_t 	i = 0;
	
	if (sFloat[0] == '-')
		i++;
	for (size_t j = i; j < sFloat.length(); j++)
	{
		if (!isdigit(sFloat[i]))
		{
			if (sFloat[i] == '.' && !dot && i > 0 && i < sFloat.length() - 1)
				dot = true;
			else
				return (false);
		}
	}
	return (true);
}

static bool isLeapYear(int year)
{
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

static bool	checkDate(std::string sDate)
{
	for (size_t i = 0; i < sDate.length(); i++)
	{
		if (!isdigit(sDate[i]) && sDate[i] != '-')
			return false;
	}

	if (sDate.size() != 10 || sDate[4] != '-' || sDate[7] != '-')
		return false;

	int year = atoi(sDate.substr(0, 4).c_str());
	int month = atoi(sDate.substr(5, 2).c_str());
	int day = atoi(sDate.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return false;

	int daysInMonth;

	if (month == 2)
	{
		if (isLeapYear(year))
			daysInMonth = 29;
		else
			daysInMonth = 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		daysInMonth = 30;
	}
	else
	{
		daysInMonth = 31;
	}
	if (day < 1 || day > daysInMonth)
		return false;
	return (true);
}

static bool	handleError(std::string sDate, std::string value, float& fValue, struct tm& tm)
{
	if (!strptime(sDate.c_str(), "%Y-%m-%d", &tm) || !checkDate(sDate))
	{
		std::cout << "Error: Invalid date format." << std::endl;
		return (false);
	}
	else if (!sscanf(value.c_str(), "%f", &fValue) || !checkIsFloat(value))
	{
		std::cout << "Error: Invalid float value." << std::endl;
		return (false);
	}
	else if (fValue < 0.0f)
	{
		std::cout << "Error: Not a positive number." << std::endl;
		return (false);
	}
	else if (fValue > 1000.0f)
	{
		std::cout << "Error: too large a number." << std::endl;
		return (false);
	}
	return (true);
}

void	BitcoinExchange::getAmountBtc(std::ifstream& inputFile)
{
	std::string								line;
	std::string								sDate;
	std::string								sValue;
	std::string::size_type					index;
	struct tm								tm = {};
	float									fValue;
	std::map<std::time_t, float>::iterator	it;

	std::getline(inputFile, line);
	while (!inputFile.eof())
	{
		std::getline(inputFile, line);
		index = line.find(" | ");
		if (index == line.npos)
		{
			std::cout << "Error: Invalid line." << std::endl;
			continue;
		}
		sDate = line.substr(0, index);
		if (line.length() > index + 3)
			sValue = line.substr(index + 3);
		else
		{
			std::cout << "Error: Invalid line format." << std::endl;
			continue;
		}
		if (!handleError(sDate, sValue, fValue, tm))
			continue;
		it = btcMap_.upper_bound(mktime(&tm));
		if (it-- != btcMap_.end())
			std::cout << sDate << " => " << sValue << " = " << it->second * fValue << std::endl;
	}
}

void	BitcoinExchange::handleBtc(std::string inputName)
{
	std::ifstream	inputFile(inputName.c_str());
	std::ifstream	dataFile(DATA_PATH);
	
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