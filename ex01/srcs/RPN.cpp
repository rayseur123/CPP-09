#include "RPN.hpp"
#include <stdio.h>
#include <cstdlib>
#include <iostream>

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
	std::string::iterator	it = str.begin();
	std::string::iterator	end = str.end();
	int						buff;

	while (it != end)
	{
		if (isdigit(*it))
		{
			stack_.push(*it - '0');
		}
		else if (*it == '+' || *it == '-' || *it == '/' || *it == '*')
		{
			buff = stack_.top();
			stack_.pop();
			if (*it == '+')
			{
				stack_.push(stack_.top() + buff);
			}
			else if (*it == '-')
			{
				stack_.push(stack_.top() - buff);
			}
			else if (*it == '/')
			{
				stack_.push(stack_.top() / buff);
			}
			else if (*it == '*')
			{
				stack_.push(stack_.top() * buff);
			}
		}
		else if (*it != ' ')
		{
			std::cout << "Error" << std::endl;
			return ;
		}
		it++;
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
