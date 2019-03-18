#include "CCommand.h"
#include  <iostream>
#include <string>
#include "ConstansMenu.h"

using namespace std;

void CCommand::vRunCommand()
{
	cout << DEFAULT_COMMAND << endl;
}

CCommandAG::CCommandAG(CManager* pcManager)
	: i_error(WITHOUT_ERROR)
	, pc_manager(pcManager)
{
}

CCommandAG::~CCommandAG()
{
}

void CCommandAG::vRunCommand()
{
	cout << DEFAULT_COMMAND << endl;
}

bool CCommandAG::b_parse_string_to_long(std::string& sUserInput, long& lParsedString)
{
	char* pc_end; // has end of parsed string value to long (how many symbols was possible to be parsed as long)
	const int i_input_string_length = sUserInput.length();
	lParsedString = strtol(sUserInput.c_str(), &pc_end, 10);

	return (pc_end == sUserInput.c_str() + i_input_string_length);
	// if whole string is numeric
}

bool CCommandAG::b_parse_string_to_double(std::string& sUserInput, double& dParsedString)
{
	char* pc_end; // has end of parsed string value to long (how many symbols was possible to be parsed as long)
	const int i_input_string_length = sUserInput.length();
	dParsedString = strtod(sUserInput.c_str(), &pc_end);

	return (pc_end == sUserInput.c_str() + i_input_string_length);
	// if whole string is numeric
}

bool CCommandAG::b_get_integer_user_input(const std::string sMessage, int iLowBound, int iUpperBound, int& iIntegerValue) const
{
	bool b_ask_input = true;
	string s_user_input;
	long l_parsed_string;

	while (b_ask_input)
	{
		cout << sMessage;
		getline(cin, s_user_input);

		if (s_user_input == "back")
		{
			return false;
		}

		if (b_parse_string_to_long(s_user_input, l_parsed_string) && !s_user_input.empty())
		{
			if (l_parsed_string == int(l_parsed_string) && (l_parsed_string >= iLowBound && l_parsed_string <= iUpperBound))
			{
				iIntegerValue = int(l_parsed_string);
				b_ask_input = false;
			}
			else
			{
				v_show_error_message(WRONG_VALUE);
			}
		}
		else
		{
			v_show_error_message(WRONG_TYPE);
		}
	}
	return true;
}

bool CCommandAG::b_get_double_user_input(const std::string sMessage, double dLowBound, double dUpperBound, double& dDoubleValue) const
{
	bool b_ask_input = true;
	string s_user_input;
	double d_parsed_string;

	while (b_ask_input)
	{
		cout << sMessage;
		getline(cin, s_user_input);

		if (s_user_input == "back")
		{
			return false;
		}

		if (b_parse_string_to_double(s_user_input, d_parsed_string) && !s_user_input.empty())
		{
			if (d_parsed_string == double(d_parsed_string) && (d_parsed_string > dLowBound && d_parsed_string <= dUpperBound))
			{
				dDoubleValue = double(d_parsed_string);
				b_ask_input = false;
			}
			else
			{
				v_show_error_message(WRONG_VALUE);
			}
		}
		else
		{
			v_show_error_message(WRONG_TYPE);
		}
	}
	return true;
}

void CCommandAG::v_show_error_message(int iErrorCode)
{
	if (iErrorCode == WITHOUT_ERROR)
	{
		return;
	}
	string message;

	switch (iErrorCode)
	{
	case WRONG_VALUE:
		message = WRONG_VALUE_MSG;
		break;

	case ALLOCATION_ERROR:
		message = ALLOCATION_ERROR_MSG;
		break;

	case WRONG_TYPE:
		message = WRONG_TYPE_MSG;
		break;
	default:
		cout << iErrorCode << endl;
		message = UNKNOWN_ERROR;
	}

	cout << message << endl;
}
