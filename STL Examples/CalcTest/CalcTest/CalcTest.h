#include <map>

struct ExpTerm
{
	float coefficient;
	float exponent;
};

std::map<int, ExpTerm> FuncExpDiff(std::map<int, ExpTerm> nthTerms);