#pragma once
#include <string>

class CMenuItem;
class CManager;

class CMenuTree
{
public:
	CMenuTree();
	~CMenuTree();
	void vInitMenuItems(CManager* pcManager);
	bool bInitMenuItems(std::string& sReadStringMenu);
	void vRunMenu();
	bool bRunMenu(std::string& sReadStringMenu);
	CMenuItem* pcGetRootMenu() const { return pc_root; }

private:
	CMenuItem* pc_root;
};


