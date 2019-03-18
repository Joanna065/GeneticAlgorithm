#pragma once
#include <vector>

template<class T>
class CProblem
{
public:
	CProblem(){};
	virtual ~CProblem(){};

	virtual double dCalculateSolution(std::vector<T>& iSolution) = 0;
	virtual int iGetSolutionLength() = 0;
};

