#include "RPN.hpp"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <exception>

Rpn::Rpn()
{}

Rpn::Rpn(Rpn const& toCopy)
{
	stack_ = toCopy.stack_;
}

Rpn::~Rpn()
{}

Rpn const&	Rpn::operator=(Rpn const& toCopy)
{
	if (this == &toCopy)
		return (*this);
	stack_ = toCopy.stack_;
	return (*this);
}

void		Rpn::handleStack(std::string str)
{
	for (std::string::iterator it = str.begin(); it != str.end(); it++)
	{
		if (isdigit(*it))
		{
			stack_.push(*it - '0');
		}
		else if ((*it == '+' || *it == '-' || *it == '/' || *it == '*') && stack_.size() > 1)
		{
			int buff = stack_.top();
			stack_.pop();
			if (*it == '+')
			{
				stack_.top() += buff;
			}
			else if (*it == '-')
			{
				stack_.top() -= buff;
			}
			else if (*it == '/')
			{
				if (buff == 0)
				{
					throw (std::logic_error("Division by 0 is forbiden"));
				}
				stack_.top() /= buff;
			}
			else if (*it == '*')
			{
				stack_.top() *= buff;
			}
		}
		else if (*it != ' ')
		{
			std::cout << "Error" << std::endl;
			return ;
		}
	}
	if (stack_.size() == 1)
	{
		std::cout << stack_.top() << std::endl;
	}
	else
	{
		std::cout << "Error" << std::endl;
	}
}
