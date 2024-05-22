#include "RPN.hpp"

#include <cctype>

std::stack<int> RPN::_stack;

// Initialize the operations map manually
RPN::OperationsMap RPN::_operations;

// Static function to populate the operations map
void RPN::populateOperationsMap()
{
    _operations.insert(std::make_pair('+', &add));
    _operations.insert(std::make_pair('-', &subtract));
    _operations.insert(std::make_pair('*', &multiply));
    _operations.insert(std::make_pair('/', &divide));
}

// Call populateOperationsMap() once to populate the operations map
static const bool operationsMapPopulated = (RPN::populateOperationsMap(), true);

int RPN::resolveExpression(const std::string &line)
{
	if (line.empty())
	{
		return 0;
	}
	for (std::string::const_iterator it = line.begin(); it != line.end(); ++it)
	{
		if (std::isspace(*it))
			continue;
		else if (std::isdigit(*it))
			pushToken(static_cast<int>(*it - '0'));
		else
			operate(static_cast<unsigned char>(*it));
	}
	if (_stack.size() > 1)
		throw::std::runtime_error("Operations ended and stack has more than 1 item");
	int ret = _stack.top();
	_stack = std::stack<int>();
	return ret;
}

void RPN::popOperandsTokens(int &lhs, int &rhs)
{
	if (_stack.size() < 2)
		throw std::runtime_error("RPN stack must have at less 2 items to do operations");
	rhs = _stack.top();
	_stack.pop();
	lhs = _stack.top();
	_stack.pop();
}

void RPN::pushToken(int token)
{
	_stack.push(token);
}

void RPN::operate(unsigned char symbol)
{
	OperationsMap::const_iterator it = _operations.find(symbol);
	if (it != _operations.end())
	{
		int lhs = 0, rhs = 0;
		popOperandsTokens(lhs, rhs);
		int res = it->second(lhs, rhs);
		pushToken(res);
		return;
	}
	throw std::runtime_error("Encoutered an undefined operator");
}

int RPN::add(const int &lhs, const int &rhs)
{
	return lhs + rhs;
}
int RPN::subtract(const int &lhs, const int &rhs)
{
	return lhs - rhs;
}
int RPN::multiply(const int &lhs, const int &rhs)
{
	return lhs * rhs;
}
int RPN::divide(const int &lhs, const int &rhs)
{
	if (rhs == 0)
		throw std::runtime_error("Tried to divide by 0");
	return lhs / rhs;
}
