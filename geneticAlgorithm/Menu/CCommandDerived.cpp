#include "CCommandDerived.h"
#include "CManager.h"
#include <string>
#include "ConstansMenu.h"
using namespace  std;


void CRunDefault<bool>::vRunCommand()
{
	pc_manager->vRunDefaultBool();
}

void CRunDefault<int>::vRunCommand()
{
	pc_manager->vRunDefaultInteger();
}

void CRunDefault<double>::vRunCommand()
{
	pc_manager->vRunDefaultDouble();
}

void CAddItemToProblem<bool>::vRunCommand()
{
	if(b_load_data())
	{
		pc_manager->vAddItemToBoolKnapsack(d_weight, d_value, i_error);
	}
	v_show_error_message(i_error);	
}

template <class T>
bool CAddItemToProblem<T>::b_load_data()
{
	if (!b_get_double_user_input(ASK_WEIGHT_ITEM, 0, numeric_limits<double>::max(), d_weight)) return false;
	//if(d_weight < 0) cout << 
	if (!b_get_double_user_input(ASK_VALUE_ITEM, 0, numeric_limits<double>::max(), d_value)) return false;
	return true;
}

void CAddItemToProblem<int>::vRunCommand()
{
	if (b_load_data())
	{
		pc_manager->vAddItemToIntegerKnapsack(d_weight, d_value, i_error);
	}
	v_show_error_message(i_error);
}

void CAddItemToProblem<double>::vRunCommand()
{
	if (b_load_data())
	{
		pc_manager->vAddItemToDoubleKnapsack(d_weight, d_value, i_error);
	}
	v_show_error_message(i_error);
}

void CRunParam<bool>::vRunCommand()
{
	if(b_load_parameters())
	{
		pc_manager->vRunParam<bool>(d_max_weight, i_items_amount, vd_weights, vd_values, i_pop_size, d_cross_prob, d_mut_prob, i_time_in_sec);
	}
}

void CRunParam<int>::vRunCommand()
{
	if(b_load_parameters())
	{
		pc_manager->vRunParam<int>(d_max_weight, i_items_amount, vd_weights, vd_values, i_pop_size, d_cross_prob, d_mut_prob, i_time_in_sec);
	}
}

void CRunParam<double>::vRunCommand()
{
	if (b_load_parameters())
	{
		pc_manager->vRunParam<double>(d_max_weight, i_items_amount, vd_weights, vd_values, i_pop_size, d_cross_prob, d_mut_prob, i_time_in_sec);
	}
}

template <class T>
bool CRunParam<T>::b_load_parameters()
{
	cout << ASK_KNAPSACK_DATA << endl;
	if(!b_get_integer_user_input(ASK_ITEM_AMOUNT, 1, std::numeric_limits<int>::max(), i_items_amount)) return false;
	for (int ii = 0; ii < i_items_amount; ii++)
	{
		double d_weight;
		double d_value;

		if (!b_get_double_user_input(ASK_WEIGHT_ITEM, 0, numeric_limits<double>::max(), d_weight)) return false;
	
		if (!b_get_double_user_input(ASK_VALUE_ITEM, 0, numeric_limits<double>::max(), d_value)) return false;
		vd_weights.push_back(d_weight);
		vd_values.push_back(d_value);
	}
	if (int(vd_weights.size()) != i_items_amount || int(vd_values.size()) != i_items_amount) return false;
	if (!b_get_double_user_input(ASK_MAX_WEIGHT, 0, numeric_limits<double>::max(), d_max_weight)) return false;

	cout << endl;
	cout << ASK_AG_DATA << endl;
	if(!b_get_integer_user_input(ASK_POP_SIZE, 1, numeric_limits<int>::max(), i_pop_size)) return false;
	if(!b_get_double_user_input(ASK_CROSS_PROB, 0, 1, d_cross_prob)) return false;
	if (!b_get_double_user_input(ASK_MUT_PROB, 0, 1, d_mut_prob)) return false;
	if(!b_get_integer_user_input(ASK_TIME_ITER, 1, numeric_limits<int>::max(), i_time_in_sec)) return false;

	return true;
}

template class CRunDefault<bool>;
template class CRunDefault<int>;
template class CRunDefault<double>;
template class CAddItemToProblem<bool>;
template class CAddItemToProblem<int>;
template class CAddItemToProblem<double>;
template class CRunParam<bool>;
template class CRunParam<int>;
template class CRunParam<double>;

