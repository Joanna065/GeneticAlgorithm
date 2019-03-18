#pragma once
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#include <iostream>
#include <string>

#define BOOL_PROBLEM 0
#define INT_PROBLEM 1
#define DOUBLE_PROBLEM 2

class CManager
{
public:
	CManager();
	~CManager();
	void vRunDefaultBool() const;
	void vRunDefaultInteger() const;
	void vRunDefaultDouble() const;
	void vAddItemToBoolKnapsack(double dWeight, double dValue, int& iError) const;
	void vAddItemToIntegerKnapsack(double dWeight, double dValue, int& iError) const;
	void vAddItemToDoubleKnapsack(double dWeight, double dValue, int& iError) const;

	template<class T> void vRunParam(double dMaxWeight, int iItemAmount, std::vector<double>& vdWeights, std::vector<double>& vdValues, int iPopulationSize, double dCrossProb, double dMutationProb, int iTimeInSec) const
	{
		std::string s_error = "";
		CKnapsackProblem<T>* pc_knapsack_problem = nullptr;
		if(CKnapsackProblem<T>::bLoadData(dMaxWeight,iItemAmount, vdWeights, vdValues,s_error))
		{
			pc_knapsack_problem = new CKnapsackProblem<T>(dMaxWeight, iItemAmount, vdWeights, vdValues);
		}
		else
		{
			std::cout << s_error << std::endl;
		}

		CGeneticAlgorithm<T>* pc_AG = nullptr;
		if(CGeneticAlgorithm<T>::bLoadData(iPopulationSize, dCrossProb, dMutationProb, iTimeInSec, pc_knapsack_problem, s_error))
		{
			pc_AG = new CGeneticAlgorithm<T>(iPopulationSize, dCrossProb, dMutationProb, iTimeInSec, pc_knapsack_problem);
		}
		else
		{
			std::cout << s_error << std::endl;
		}
		
		pc_AG->vRun();
		std::cout << pc_AG->sBestSolution() << std::endl;

		delete pc_AG;
	};

private:
	void v_init_default_problems();

	CKnapsackProblem<bool>* pc_bool_problem;
	CKnapsackProblem<int>* pc_int_problem;
	CKnapsackProblem<double>* pc_double_problem;

	CGeneticAlgorithm<bool>* pc_bool_AG;
	CGeneticAlgorithm<int>* pc_int_AG;
	CGeneticAlgorithm<double>* pc_double_AG;
	
};

