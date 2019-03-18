#pragma once
#include <string>


class CManager;

class CCommand
{
public:
	CCommand() = default;
	virtual ~CCommand()= default;
	virtual void vRunCommand();
};


class CCommandAG :
	public CCommand
{
public:
	CCommandAG(CManager* pcManager);
	virtual ~CCommandAG();
	virtual void vRunCommand();

protected:
	static bool b_parse_string_to_long(std::string& sUserInput, long& lParsedString);
	static bool b_parse_string_to_double(std::string& sUserInput, double& dParsedString);
	bool b_get_integer_user_input(std::string sMessage, int iLowBound, int iUpperBound, int& iIntegerValue) const;
	bool b_get_double_user_input(std::string sMessage, double dLowBound, double dUpperBound, double& dDoubleValue) const;
	static void v_show_error_message(int iErrorCode);
	int i_error;
	CManager* pc_manager;
};