#pragma once
#include <string>
#include <vector>
#include "CCommand.h"

class CManager;

class CMenuItem
{
	friend class CMenu;
	friend class CMenuCommand;

public:
	CMenuItem() {};
	CMenuItem(std::string sName, std::string sCommand) : s_name(sName), s_command(sCommand), pc_parent(nullptr) {};
	virtual ~CMenuItem() {};
	virtual void vRun() = 0;
	virtual void vToString(std::stringstream& sToString) = 0;
	virtual int iReadAndInitSelf(const std::string& sStringToRead, std::string& sErrorInfo, size_t sPosition = 0) = 0;
	std::string sGetName() const { return s_name; }
	void vSetName(std::string sName) { this->s_name = sName; }
	std::string sGetCommand() const { return s_command; }
	void vSetCommand(std::string sCommand) { this->s_command = sCommand; }

protected:
	CMenuItem* pc_search_root();
	std::string sGetPath() const;
	std::string s_name;
	std::string s_command;
	CMenuItem* pc_parent;
};

class CMenu
	: public CMenuItem
{
	//friend class CMenuTree;
public:
	CMenu();
	CMenu(std::string sName, std::string sCommand);
	~CMenu();
	void vRun() override;
	void vToString(std::stringstream& sToString) override;
	int iReadAndInitSelf(const std::string& sStringToRead, std::string& sErrorExpectedCharInfo, size_t sPosition = 0) override;
	void vAddMenuItem(CMenuItem* cpMenuItem);
	void vDeleteMenuItem(int iMenuItemIndex);
	void vEditMenuItem(std::string sNewName, std::string sNewCommand);
	int iGetChildAmount() const { return v_menu_items.size(); }

private:
	static void v_DFS_search(std::string& sCommandKey, CMenuItem* cMenuItem, std::vector<std::string>& vSearchedMenuItems);
	void v_show_menu_items();
	void v_search_command(std::string sUserInput);
	void v_help_command(std::string sUserInput);
	static std::string s_left_strip(std::string sInput);
	bool b_process_input(int& iVectorIndex);
	bool b_correct_command(std::string &sUserInput, int &iVectorIndex);
	bool b_menuitem_already_exist(std::string sName, std::string sCommand);
	bool b_check_index(int iVectorIndex) const;
	std::vector<CMenuItem*> v_menu_items;
};

class CMenuCommand
	: public CMenuItem
{
public:
	CMenuCommand();
	CMenuCommand(std::string sName, std::string sCommand, CCommand* cCommand, std::string sHelp);
	~CMenuCommand();
	void vRun() override;
	void vToString(std::stringstream& sToString) override;
	int iReadAndInitSelf(const std::string& sStringToRead, std::string& sErrorInfo, size_t sPosition = 0) override;
	std::string sHelpGetter() const { return s_help; }
private:
	CCommand* pc_command;
	std::string s_help;
};

