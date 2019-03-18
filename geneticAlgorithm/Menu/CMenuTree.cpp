#include "CMenuTree.h"
#include <iostream>
#include "ConstansMenu.h"
#include "CMenuItems.h"
#include "CCommandDerived.h"
#include "CManager.h"

using namespace std;

CMenuTree::CMenuTree()
{
	pc_root = nullptr;
}

CMenuTree::~CMenuTree()
{
	delete pc_root;
}

void CMenuTree::vInitMenuItems(CManager* pcManager)
{
	CMenu* pc_main_menu = new CMenu(MAIN_MENU, MAIN_CMD);
	CMenu* pc_bool_knapsack_menu = new CMenu(BOOL_KNAPSACK, BOOL_KNAPSACK_CMD);
	CMenu* pc_int_knapsack_menu = new CMenu(INTEGER_KNAPSACK, INTEGER_KNAPSACK_CMD);
	CMenu* pc_double_knapsack_menu = new CMenu(DOUBLE_KNAPSACK, DOUBLE_KNAPSACK_CMD);

	CMenuCommand* pc_default_int_knapsack  = new CMenuCommand(DEFAULT_RUN, DEFAULT_RUN_CMD, new CRunDefault<int>(pcManager) , DEFAULT_RUN_INT_HELP_MSG);
	CMenuCommand* pc_default_bool_knapsack = new CMenuCommand(DEFAULT_RUN, DEFAULT_RUN_CMD, new CRunDefault<bool>(pcManager), DEFAULT_RUN_BOOL_HELP_MSG);
	CMenuCommand* pc_default_double_knapsack = new CMenuCommand(DEFAULT_RUN, DEFAULT_RUN_CMD, new CRunDefault<double>(pcManager), DEFAULT_RUN_DOUBLE_HELP_MSG);
	CMenuCommand* pc_add_item_to_int_knapsack = new CMenuCommand(ADD_ITEM, ADD_ITEM_CMD, new CAddItemToProblem<int>(pcManager), ADD_ITEM_HELP_MSG);
	CMenuCommand* pc_add_item_to_bool_knapsack = new CMenuCommand(ADD_ITEM, ADD_ITEM_CMD, new CAddItemToProblem<bool>(pcManager), ADD_ITEM_HELP_MSG);
	CMenuCommand* pc_add_item_to_double_knapsack = new CMenuCommand(ADD_ITEM, ADD_ITEM_CMD, new CAddItemToProblem<double>(pcManager), ADD_ITEM_HELP_MSG);
	CMenuCommand* pc_param_int_knapsack = new CMenuCommand(PARAM_RUN, PARAM_RUN_CMD, new CRunParam<int>(pcManager), PARAM_RUN_HELP_MSG);
	CMenuCommand* pc_param_bool_knapsack = new CMenuCommand(PARAM_RUN, PARAM_RUN_CMD, new CRunParam<bool>(pcManager), PARAM_RUN_HELP_MSG);
	CMenuCommand* pc_param_double_knapsack = new CMenuCommand(PARAM_RUN, PARAM_RUN_CMD, new CRunParam<double>(pcManager), PARAM_RUN_HELP_MSG);

	// MAIN MENU
	pc_main_menu->vAddMenuItem(pc_bool_knapsack_menu);
	pc_main_menu->vAddMenuItem(pc_int_knapsack_menu);
	pc_main_menu->vAddMenuItem(pc_double_knapsack_menu);

	// BOOL KNAPSACK MENU
	pc_bool_knapsack_menu->vAddMenuItem(pc_default_bool_knapsack);
	pc_bool_knapsack_menu->vAddMenuItem(pc_add_item_to_bool_knapsack);
	pc_bool_knapsack_menu->vAddMenuItem(pc_param_bool_knapsack);

	// INT KNAPSACK MENU
	pc_int_knapsack_menu->vAddMenuItem(pc_default_int_knapsack);
	pc_int_knapsack_menu->vAddMenuItem(pc_add_item_to_int_knapsack);
	pc_int_knapsack_menu->vAddMenuItem(pc_param_int_knapsack);


	// DOUBLE KNAPSACK MENU
	pc_double_knapsack_menu->vAddMenuItem(pc_default_double_knapsack);
	pc_double_knapsack_menu->vAddMenuItem(pc_add_item_to_double_knapsack);
	pc_double_knapsack_menu->vAddMenuItem(pc_param_double_knapsack);
	

	this->pc_root = pc_main_menu;
}

bool CMenuTree::bInitMenuItems(std::string& sReadStringMenu)
{
	pc_root = new CMenu();
	string s_error_char_info;
	const int i_position = pc_root->iReadAndInitSelf(sReadStringMenu, s_error_char_info);

	if (!s_error_char_info.empty())
	{
		cout << ERROR_STRING_MSG << i_position << CHARS_EXPECTED_INFO << s_error_char_info << endl;
		//delete pc_root;
		return false;
	}

	if (int(sReadStringMenu.length() - 1) > i_position)
	{
		cout << ERROR_STRING_MSG << i_position - 1 << CHARS_EXPECTED_INFO << COMMA << endl;
		return false;
	}
	cout << READ_FROM_FILE_SUCCESS << endl;
	cout << endl;
	return true;
}

void CMenuTree::vRunMenu()
{
	pc_root->vRun();
}

bool CMenuTree::bRunMenu(std::string& sReadStringMenu)
{
	if (this->bInitMenuItems(sReadStringMenu))
	{
		pc_root->vRun();
		return true;
	}
	return false;
}
