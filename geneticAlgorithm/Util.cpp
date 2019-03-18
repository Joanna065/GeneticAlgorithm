#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Util.h"
#include <limits>
#include "ConstansMenu.h"
#include "CMenuItems.h"
using namespace  std;

void vWriteToFile(const string& sFileName, CMenuItem* pcObjectToWrite)
{
	ofstream out_file(sFileName);
	if (!out_file.is_open())
	{
		cout << "Unable to open file: " + sFileName << endl;
	}
	else
	{
		stringstream s_tree_string;
		if (pcObjectToWrite != nullptr)
		{
			pcObjectToWrite->vToString(s_tree_string);
			out_file << s_tree_string.str() << endl;
		}
	}
	out_file.close();
}

string pcReadFromFile(const string & sFileName)
{
	string s_tree_string;
	ifstream in_file(sFileName);
	if (!in_file.is_open())
	{
		cout << "Unable to find such a file: " + sFileName << endl;
	}
	else
	{
		s_tree_string.assign((std::istreambuf_iterator<char>(in_file)),
			(std::istreambuf_iterator<char>()));
	}
	in_file.close();

	return s_tree_string;
}

bool bIsSpecialChar(const char c)
{
	//std::string special_chars = "()',;[]";
	std::string special_chars = "'";
	for (size_t i = 0; i < special_chars.length(); ++i)
	{
		if (special_chars[i] == c) return true;
	}
	return false;
}

// Returns character index in *sCharsExpected* that is found at the sPosition in sString and increments sPosition by one.
// If the characters are not found, -1 is returned and sPosition is not incremented.
int iExpectChars(const string& sString, const string& sCharsExpected, string& sErrorExpectedCharInfo, size_t& sPosition)
{
	for (int i = 0; i < int(sCharsExpected.length()); ++i)
	{
		if (sString[sPosition] == sCharsExpected[i])
		{
			sPosition++;
			return i;
		}
	}
	sErrorExpectedCharInfo = sCharsExpected;
	return -1;
}

// sPosition is set to the last parsed position. If no error it corresponds to the closing '
string sParseName(const string& sString, string& sErrorExpectedCharInfo, size_t& sPosition)
{
	string s_ret;	//collect non special char 
	if (iExpectChars(sString, APOSTROPHE, sErrorExpectedCharInfo, sPosition) != 0)
		return s_ret;

	//using current sPosition in String to iterate on String
	for (; sPosition < sString.length() && sString[sPosition] != '\''; ++sPosition)
	{
		s_ret += sString[sPosition];
	}
	if (s_ret.empty())
	{
		sErrorExpectedCharInfo = "any non special character";
		return s_ret;
	}

	iExpectChars(sString, APOSTROPHE, sErrorExpectedCharInfo, sPosition);	// checking if sPosition is ' and set sErrorExpectedCharInfo otherwise
	return s_ret;
}

int iParseNumber(const std::string& sString, std::string& sErrorExpectedCharInfo, size_t& sPosition)
{
	int i_number;
	string s_ret;

	for (; sPosition < sString.length() && sString[sPosition] != ')'; ++sPosition)
	{
		s_ret += sString[sPosition];
	}
	if (s_ret.empty())
	{
		sErrorExpectedCharInfo = CHILD_NUMBER;
	}
	if (bReadInteger(s_ret, 0, numeric_limits<int>::max(), i_number, sErrorExpectedCharInfo))
	{
		return i_number;
	}

	return -1;
}

bool bReadInteger(string& sNumInString, int iLowBound, int iUpperBound, int& iIntegerValue, std::string& sErrorExpectedCharInfo)
{
	long l_parsed_string;
	if (bParseStringToLong(sNumInString, l_parsed_string, sErrorExpectedCharInfo))
	{
		if (l_parsed_string == int(l_parsed_string) && (l_parsed_string >= iLowBound && l_parsed_string <= iUpperBound))
		{
			iIntegerValue = int(l_parsed_string);
		}
		else
		{
			sErrorExpectedCharInfo = NUMERIC_CHAR_OVER_ZERO;
			return false;
		}
	}
	else
	{
		sErrorExpectedCharInfo = NUMERIC_CHARS;
		return false;
	}
	return true;
}

bool bParseStringToLong(std::string& sUserInput, long& lParsedString, std::string& sErrorExpectedCharInfo)
{
	char* pc_end; // has end of parsed string value to long (how many symbols was possible to be parsed as long)
	const int i_input_string_length = sUserInput.length();
	lParsedString = strtol(sUserInput.c_str(), &pc_end, 10);

	return (pc_end == sUserInput.c_str() + i_input_string_length);
	// if whole string is numeric
}
