#ifndef RPN_CPP
#define RPN_CPP

#include <stack>
#include <string>

class	Rpn
{
	private:
		std::stack<int>	stack_;
	public:
		Rpn();
		Rpn(Rpn const& toCopy);
		~Rpn();

		Rpn const&	operator=(Rpn const& toCopy);
		void		handleStack(std::string str);
};

#endif