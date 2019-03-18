#include "CMenuItems.h"
#include  <iostream>
#include <sstream>
#include <string>
#include <queue>
#include "ConstansMenu.h"
#include "Util.h"

using namespace std;

std::string CMenuItem::sGetPath() const
{
	if (this->pc_parent == nullptr)
	{
		return this->s_command;
	}
	else
	{
		return pc_parent->sGetPath() + " -> " + s_command;
	}
}

CMenuItem* CMenuItem::pc_search_root()
{
	if (this->pc_parent == nullptr) return  this;
	return pc_parent->pc_search_root();
}

//CMENU 
CMenu::CMenu()
	: CMenuItem("", "")
{
	pc_parent = nullptr;
}

CMenu::CMenu(std::string sName, const std::string sCommand)
	: CMenuItem(sName, sCommand)
{
	pc_parent = nullptr;
}

CMenu::~CMenu()
{
	for (size_t i = 0; i < v_menu_items.size(); i++)
	{
		delete v_menu_items[i];			// usuniecie obiektow z pamieci
	}
	v_menu_items.clear();				//usuniecie wskaznikow z wektora
}

void CMenu::vRun()
{
	cout << this->sGetPath() << endl;
	v_show_menu_items();
	cout << endl;

	int i_vector_index;

	while (b_process_input(i_vector_index))
	{
		v_menu_items[i_vector_index]->vRun();
		cout << endl;
		cout << this->sGetPath() << endl;
		v_show_menu_items();
	}
}

void CMenu::vToString(stringstream& sToString)
{
	sToString << "('" + s_name + "','" + s_command + "';";
	if (!v_menu_items.empty())
	{
		v_menu_items[0]->vToString(sToString);

		for (int i = 1; i < int(v_menu_items.size()); i++)
		{
			sToString << ",";
			v_menu_items[i]->vToString(sToString);
			// if( i != v_menu_items.size() - 1)
			// {
				// sToString << ",";
			// }
		}
	}
	sToString << ")";
}

int CMenu::iReadAndInitSelf(const std::string& sStringToRead, std::string& sErrorExpectedCharInfo, size_t sPosition)
{
	if (iExpectChars(sStringToRead, LEFT_BRACKET, sErrorExpectedCharInfo, sPosition) == -1)
		return sPosition;

	s_name = sParseName(sStringToRead, sErrorExpectedCharInfo, sPosition);
	if (!sErrorExpectedCharInfo.empty())
		return sPosition;

	if (iExpectChars(sStringToRead, COMMA, sErrorExpectedCharInfo, sPosition) == -1)
		return sPosition;

	s_command = sParseName(sStringToRead, sErrorExpectedCharInfo, sPosition);

	if (!sErrorExpectedCharInfo.empty())
		return sPosition;

	if (iExpectChars(sStringToRead, SEMICOLON, sErrorExpectedCharInfo, sPosition) == -1)
		return sPosition;

	// here we expect either ( or [ if the menu has children
	// or ) if the menu doesn't have any children.	
	while (sErrorExpectedCharInfo.empty())
	{
		int i_index = iExpectChars(sStringToRead, LEFT_SQUARE_OR_RIGHT_BRACKET, sErrorExpectedCharInfo, sPosition);

		if (i_index == -1)
			return sPosition;

		if (i_index == 2)
			return  sPosition;

		if (i_index == 0)
		{
			CMenu* pc_menu = new CMenu();
			vAddMenuItem(pc_menu);
			sPosition = pc_menu->iReadAndInitSelf(sStringToRead, sErrorExpectedCharInfo, --sPosition);
		}
		else if (i_index == 1)
		{
			CMenuCommand* pc_command_menu = new CMenuCommand();
			vAddMenuItem(pc_command_menu);
			sPosition = pc_command_menu->iReadAndInitSelf(sStringToRead, sErrorExpectedCharInfo, --sPosition);
		}
		if (sErrorExpectedCharInfo.empty())
		{
			i_index = iExpectChars(sStringToRead, COMMA_OR_RIGHT_BRACKET, sErrorExpectedCharInfo, sPosition);
			if (i_index == 1)
				return sPosition;
		}
	}
	return sPosition;
}

void CMenu::vAddMenuItem(CMenuItem* cpMenuItem)
{
	if (!b_menuitem_already_exist(cpMenuItem->sGetName(), cpMenuItem->sGetCommand()))
	{
		cpMenuItem->pc_parent = this;
		v_menu_items.push_back(cpMenuItem);
	}
	else
	{
		cout << MENUITEM_ALREADY_EXIST << endl;
	}
}

void CMenu::vDeleteMenuItem(int iMenuItemIndex)
{
	if (b_check_index(iMenuItemIndex))
	{
		delete v_menu_items[iMenuItemIndex];
		v_menu_items.erase(v_menu_items.begin() + iMenuItemIndex);
	}
	else
	{
		cout << NONEXISTENT_MENUITEM << endl;
	}
}

void CMenu::vEditMenuItem(std::string sNewName, std::string sNewCommand)
{
	if (!b_menuitem_already_exist(sNewName, sNewCommand))
	{
		s_name = sNewName;
		s_command = sNewCommand;
	}
	else
	{
		cout << MENUITEM_ALREADY_EXIST << endl;
	}
}

void CMenu::v_DFS_search(string& sCommandKey, CMenuItem* cMenuItem, vector<string>& vSearchedMenuItems)
{
	if (cMenuItem->sGetCommand() == sCommandKey)
	{
		vSearchedMenuItems.push_back(cMenuItem->sGetPath());
	}
	CMenu* c_menu = dynamic_cast<CMenu*>(cMenuItem);
	if (c_menu != nullptr)
	{
		for (int i = 0; i < int(c_menu->v_menu_items.size()); i++)
		{
			v_DFS_search(sCommandKey, c_menu->v_menu_items[i], vSearchedMenuItems);
		}
	}
}

void CMenu::v_show_menu_items() {

	for (int i = 0; i < int(v_menu_items.size()); i++)
	{
		cout << to_string(i + 1) + ". " + v_menu_items[i]->sGetName() + " (" + v_menu_items[i]->sGetCommand() + ") " << endl;
	}
}

void CMenu::v_search_command(string sUserInput)
{
	if (sUserInput.length() == 0)
	{
		cout << NO_COMMAND_NAME << endl;
	}
	else if (sUserInput[0] != ' ')
	{
		cout << WRONG_COMMAND << endl;
	}
	else
	{
		vector<string> v_searched_menu_paths;
		sUserInput = s_left_strip(sUserInput);
		if (sUserInput.empty())
		{
			cout << NO_COMMAND_NAME << endl;
		}
		else
		{
			v_DFS_search(sUserInput, this->pc_search_root(), v_searched_menu_paths);
			if (v_searched_menu_paths.empty())
			{
				cout << COMMAND_NOT_EXIST << endl;
			}
			else
			{
				for (int i = 0; i < int(v_searched_menu_paths.size()); i++)
				{
					cout << v_searched_menu_paths[i] << endl;
				}
			}
		}
	}

}

void CMenu::v_help_command(string sUserInput)
{
	int i_command_index;

	if (sUserInput.length() == 0)
	{
		cout << NO_COMMAND_NAME << endl;
	}
	else if (sUserInput[0] != ' ')
	{
		cout << WRONG_COMMAND << endl;
	}
	else
	{
		sUserInput = s_left_strip(sUserInput);
		if (sUserInput.empty())
		{
			cout << NO_COMMAND_NAME << endl;
		}
		else if (b_correct_command(sUserInput, i_command_index))
		{
			if (CMenuCommand* c_menu_cmd = dynamic_cast<CMenuCommand*>(v_menu_items[i_command_index]))
				//instanceof CMenuCommand
			{
				cout << c_menu_cmd->sHelpGetter() << endl;
			}
			else
			{
				cout << MENU_COMMAND << endl;
			}
		}
		else
		{
			cout << WRONG_COMMAND << endl;
		}
	}
}

string CMenu::s_left_strip(std::string sInput)
{
	const size_t s_pos = sInput.find_first_not_of(' ');
	if (s_pos == string::npos) return "";
	return sInput.substr(s_pos);
}

bool CMenu::b_process_input(int& iVectorIndex)
{
	bool b_ask_input = true;
	string s_user_input;

	string filteredInput;

	while (b_ask_input)
	{
		getline(cin, s_user_input);

		if (s_user_input == "back")
		{
			return false;
		}

		if (s_user_input.substr(0, 4) == "help")
		{
			v_help_command(s_user_input.substr(4));
		}

		else if (s_user_input.substr(0, 6) == "search")
		{
			v_search_command(s_user_input.substr(6));
		}

		else if (b_correct_command(s_user_input, iVectorIndex))
		{
			b_ask_input = false;
		}
		else
		{
			cout << WRONG_COMMAND << endl;
		}
	}
	return true;
}

bool CMenu::b_correct_command(string &sUserInput, int &iVectorIndex)
{
	for (int i = 0; i < int(v_menu_items.size()); i++)
	{
		if (sUserInput == v_menu_items[i]->sGetCommand()) {
			iVectorIndex = i;
			return true;
		}
	}
	return false;
}

bool CMenu::b_menuitem_already_exist(string sName, string sCommand)
{
	for (int i = 0; i < int(v_menu_items.size()); i++)
	{
		if (sName == v_menu_items[i]->sGetName() && sCommand == v_menu_items[i]->sGetCommand())
		{
			return true;
		}
	}
	return false;
}

bool CMenu::b_check_index(int iVectorIndex) const
{
	return iVectorIndex >= 0 && iVectorIndex < int(v_menu_items.size());
}

// CMENUCOMMAND
CMenuCommand::CMenuCommand()
	: CMenuItem("", ""), pc_command(nullptr), s_help("")
{
}

CMenuCommand::CMenuCommand(string sName, string sCommand, CCommand* cCommand, string sHelp)
	: CMenuItem(sName, sCommand), pc_command(cCommand), s_help(sHelp)
{
	pc_parent = nullptr;
}

CMenuCommand::~CMenuCommand()
{
	delete pc_command;
}

void CMenuCommand::vRun()
{
	if (pc_command != nullptr)
	{
		pc_command->vRunCommand();
	}
	else
	{
		cout << EMPTY_COMMAND << endl;
	}
}

void CMenuCommand::vToString(stringstream& sToString)
{
	sToString << "['" + s_name + "','" + s_command + "','" + s_help + "']";
}

int CMenuCommand::iReadAndInitSelf(const std::string& sStringToRead, std::string& sErrorInfo, size_t sPosition)
{
	if (iExpectChars(sStringToRead, "[", sErrorInfo, sPosition) != 0)
		return sPosition;

	s_name = sParseName(sStringToRead, sErrorInfo, sPosition);
	if (!sErrorInfo.empty())
		return sPosition;

	if (iExpectChars(sStringToRead, ",", sErrorInfo, sPosition) != 0)
		return sPosition;

	s_command = sParseName(sStringToRead, sErrorInfo, sPosition);
	if (!sErrorInfo.empty())
		return sPosition;

	if (iExpectChars(sStringToRead, ",", sErrorInfo, sPosition) != 0)
		return sPosition;

	s_help = sParseName(sStringToRead, sErrorInfo, sPosition);
	if (!sErrorInfo.empty())
		return sPosition;

	iExpectChars(sStringToRead, "]", sErrorInfo, sPosition);

	return sPosition;
}
