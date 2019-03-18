#include "CKnapsackProblem.h"
#include "ConstansAlgorithm.h"
#include "ConstansMenu.h"
using namespace std;

template <class T>
CKnapsackProblem<T>::CKnapsackProblem()
{
}

template<class T>
CKnapsackProblem<T>::CKnapsackProblem(double dMaxWeight, int iItemAmount, vector<double>& vdWeights, vector<double>& vdValues)
	: d_max_weight(dMaxWeight), i_item_amount(iItemAmount), vd_weights(vdWeights), vd_values(vdValues)
{
}

template<class T>
CKnapsackProblem<T>::~CKnapsackProblem() = default;

template<class T>
bool CKnapsackProblem<T>::bLoadData(double dMaxWeight, int iItemAmount, vector<double>& vdWeights, vector<double>& vdValues, string& sError)
{
	if (iItemAmount < 1) {
		sError = ERROR_ITEMS_AMOUNT;
		return false;
	}
	if (dMaxWeight <= 0) {
		sError = ERROR_MAX_WEIGHT;
		return false;
	}
	if (iItemAmount != int(vdWeights.size()) || iItemAmount != int(vdValues.size())) {
		sError = ERROR_WRONG_DATA_FOR_WEIGHTS_OR_VALUES;
		return false;
	}
	for (int i = 0; i < iItemAmount; i++) {
		if (vdWeights[i] <= 0 || vdValues[i] < 0) {
			sError = ERROR_NEGATIVE_WEIGHTS_OR_VALUES;
			return false;
		}
	}
	return true;
}

template<class T>
// return 0 if not fitted or value of items if fitted
double CKnapsackProblem<T>::dCalculateSolution(vector<T>& iSolution)
{
	if (int(iSolution.size()) == i_item_amount) {
		double i_value = 0;
		double i_weight = 0;

		for (int ii = 0; ii < i_item_amount; ii++)
		{
			i_value += vd_values[ii] * iSolution[ii];
			i_weight += vd_weights[ii] * iSolution[ii];
		}
		if (i_weight <= d_max_weight)
		{
			return i_value;
		}
	}
	return 0;
}

template<class T>
bool CKnapsackProblem<T>::bSetData(double dMaxWeight, int iItemAmount, vector<double>& vdWeights,
	vector<double>& vdValues, string& sError)
{
	if (bLoadData(dMaxWeight, iItemAmount, vdWeights, vdValues, sError)) {
		d_max_weight = dMaxWeight;
		i_item_amount = iItemAmount;
		vd_weights = vdWeights;
		vd_values = vdValues;
		return true;
	}
	return false;
}

template<class T>
bool CKnapsackProblem<T>::bAddItem(double dWeight, double dValue, int& iError)
{
	if(!(dWeight > 0 && dValue >= 0))
	{
		iError = WRONG_VALUE;
		return false;
	}
	vd_weights.push_back(dWeight);
	vd_values.push_back(dValue);
	i_item_amount++;
	return true;
}

template class CKnapsackProblem<bool>;
template class CKnapsackProblem<int>;
template class CKnapsackProblem<double>;


