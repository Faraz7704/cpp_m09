#pragma once

#include <string>
#include <stack>
#include <map>
#include <stdexcept>

class RPN
{
	public:
		static int resolveExpression(const std::string &line);

		static void populateOperationsMap();
	
	private:
		RPN();
		RPN(const RPN &rhs);
		
		~RPN();
		
		RPN& operator=(const RPN &rhs);

		typedef int (*OperationFunc)(const int&, const int&);
		typedef std::map<unsigned char, OperationFunc> OperationsMap;

		static OperationsMap _operations;
		static std::stack<int> _stack;

		static void popOperandsTokens(int &lhs, int &rhs);
		static void pushToken(int token);

		static void operate(unsigned char symbol);

	    static int add(const int &lhs, const int &rhs);
		static int subtract(const int &lhs, const int &rhs);
		static int multiply(const int &lhs, const int &rhs);
		static int divide(const int &lhs, const int &rhs);
};
