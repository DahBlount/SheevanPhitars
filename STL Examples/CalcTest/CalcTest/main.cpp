#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdarg>
#include <cstring>
#include <limits.h>

#include "CalcTest.h"

inline
bool ch_is_sign(char ch)
{
	return ((ch == '-') || (ch == '+'));
}

inline
bool ch_is_numeral(char ch) {
	return ((ch >= '0') && (ch <= '9'));
}

inline
bool ch_is_decimal(char ch) {
	return (ch == '.');
}

std::map<int,ExpTerm> FuncExpDiff(std::map<int,ExpTerm> nthTerms)
{
	std::map<int,ExpTerm> diffTerms;
	for (auto it = nthTerms.begin(); it != nthTerms.end(); it++)
	{
		int Key = it->first;
		ExpTerm currTerm = it->second;
		currTerm.coefficient *= currTerm.exponent;
		currTerm.exponent -= 1.0f;
		if (currTerm.exponent < 0.0f) {
			currTerm.exponent = 0.0f;
		}
		diffTerms[Key] = currTerm;
	}
	return diffTerms;
}

void main()
{
	int nTerms;
	std::map<int, ExpTerm> inTerms;
	std::cout << "Note: If a term has no exponent, enter 1 if it has an 'x' or enter 0 if it is a constant." << std::endl;
	std::cout << "For example: x + 1 has two terms, the first term has a coefficient of 1 and an exponent of 1, the second term has a coefficient of 1 and exponent of 0." << std::endl;
	std::cout << "Please enter the number of terms your function contains: " << std::endl;
	std::cin >> nTerms;
	for (int i = 1; i <= nTerms; i++)
	{
		std::cout << "Please enter the coefficient of term " << i << " of your function: " << std::endl;
		std::cin >> inTerms[i].coefficient;
		std::cout << std::endl;
		std::cout << "Please enter the exponent of term " << i << " of your function: " << std::endl;
		std::cin >> inTerms[i].exponent;
		std::cout << std::endl;
	}
	std::map<int, ExpTerm> outTerms = FuncExpDiff(inTerms);

	std::cout << "The derivative of your function is: " << std::endl;
	for (int i = 1; i <= nTerms; i++)
	{
		if (outTerms[i].coefficient != 0.0f) {
			if (i != 1) {
				std::cout << " + ";
			}

			if (outTerms[i].exponent == 0.0f) {
				std::cout << outTerms[i].coefficient;
			} else if (outTerms[i].exponent == 1.0f) {
				std::cout << outTerms[i].coefficient << "x";
			} else {
				std::cout << outTerms[i].coefficient << "x^" << outTerms[i].exponent;
			}
		} else {
			std::cout << std::endl;
		}
	}
}