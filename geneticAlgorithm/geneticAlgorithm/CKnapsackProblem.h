#pragma once
#include "CProblem.h"

template<class T>
class CKnapsackProblem
	:  public CProblem<T>
{
public:
	CKnapsackProblem();
	CKnapsackProblem(double dMaxWeight, int iItemAmount, std::vector<double>& vdWeights, std::vector<double>& vdValues);
	~CKnapsackProblem();

	static bool bLoadData(double dMaxWeight, int iItemAmount, std::vector<double>& vdWeights, std::vector<double>& vdValues, std::string& sError);	
	double dCalculateSolution(std::vector<T>& iSolution) override;
	int iGetSolutionLength() override { return i_item_amount; };
	bool bSetData(double dMaxWeight, int iItemAmount, std::vector<double>& vdWeights, std::vector<double>& vdValues, std::string& sError);
	bool bAddItem(double dWeight, double dValue, int& iError);

private:
	double d_max_weight;
	int i_item_amount;
	std::vector<double> vd_weights;
	std::vector<double> vd_values;
};


