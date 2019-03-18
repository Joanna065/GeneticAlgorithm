#include "CManager.h"
#include <iostream>
#include "ConstansAlgorithm.h"
#include <string>

using namespace std;

CManager::CManager()
{
	v_init_default_problems();
}

CManager::~CManager()
{
	delete pc_bool_AG;
	delete pc_double_AG;
	delete pc_int_AG;
}

void CManager::vRunDefaultBool() const
{
	pc_bool_AG->vRun();
	cout << pc_bool_AG->sBestSolution() << endl;
}

void CManager::vRunDefaultInteger() const
{
	pc_int_AG->vRun();
	cout << pc_int_AG->sBestSolution() << endl;
}

void CManager::vRunDefaultDouble() const
{
	pc_double_AG->vRun();
	cout << pc_double_AG->sBestSolution() << endl;
}

void CManager::vAddItemToBoolKnapsack(double dWeight, double dValue, int& iError) const
{
	pc_bool_problem->bAddItem(dWeight, dValue, iError);
}

void CManager::vAddItemToIntegerKnapsack(double dWeight, double dValue, int& iError) const
{
	pc_int_problem->bAddItem(dWeight, dValue, iError);
}

void CManager::vAddItemToDoubleKnapsack(double dWeight, double dValue, int& iError) const
{
	pc_double_problem->bAddItem(dWeight, dValue, iError);
}

void CManager::v_init_default_problems()
{
	vector<double> vd_weights DEFAULT_WEIGHTS;
	vector<double> vd_values DEFAULT_VALUES;

	pc_bool_problem = new CKnapsackProblem<bool>(DEFAULT_MAX_WEIGHT, DEFAULT_ITEM_AMOUNT, vd_weights, vd_values);
	pc_bool_AG = new CGeneticAlgorithm<bool>(DEFAULT_POP_SIZE, DEFAULT_CROSS_PROB, DEFAULT_MUT_PROB, DEFAULT_TIME_ITER, pc_bool_problem);

	pc_int_problem = new CKnapsackProblem<int>(DEFAULT_MAX_WEIGHT, DEFAULT_ITEM_AMOUNT, vd_weights, vd_values);
	pc_int_AG = new CGeneticAlgorithm<int>(DEFAULT_POP_SIZE, DEFAULT_CROSS_PROB, DEFAULT_MUT_PROB, DEFAULT_TIME_ITER, pc_int_problem);

	pc_double_problem = new CKnapsackProblem<double>(DEFAULT_MAX_WEIGHT, DEFAULT_ITEM_AMOUNT, vd_weights, vd_values);
	pc_double_AG = new CGeneticAlgorithm<double>(DEFAULT_POP_SIZE, DEFAULT_CROSS_PROB, DEFAULT_MUT_PROB, DEFAULT_TIME_ITER, pc_double_problem);
}

