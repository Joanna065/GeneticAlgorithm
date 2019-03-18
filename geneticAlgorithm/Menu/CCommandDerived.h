#pragma once
#include "CCommand.h"
#include <vector>

template <class T>
class CRunDefault
	: public CCommandAG
{
public:
	CRunDefault(CManager* pcManager)
		:CCommandAG(pcManager)
	{
	}

	void vRunCommand() override;
};

template <class T>
class CAddItemToProblem
	: public CCommandAG
{
public:
	CAddItemToProblem(CManager* pcManager)
		:CCommandAG(pcManager)
	{
	}

	void vRunCommand() override;
private:
	bool b_load_data();
	double d_weight;
	double d_value;
};

template <class T>
class CRunParam
	: public CCommandAG
{
public:
	CRunParam(CManager* pcManager)
		: CCommandAG(pcManager)
	{
	}

	void vRunCommand() override;
private:
	bool b_load_parameters();

	// KNAPSACK parameters
	std::vector<double> vd_weights;
	std::vector<double> vd_values;
	int i_items_amount;
	double d_max_weight;

	// genetic algorithm parameters
	int i_pop_size;
	double d_cross_prob;
	double d_mut_prob;
	int i_time_in_sec;

};



