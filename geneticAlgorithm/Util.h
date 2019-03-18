#pragma once
#include <string>

class CMenuItem;
void vWriteToFile(const std::string& sFileName, CMenuItem* pcObjectToWrite);

std::string pcReadFromFile(const std::string& sFileName);

int iExpectChars(const std::string& sString, const std::string& sCharsExpected, std::string& sErrorExpectedCharInfo, size_t& sPosition);

std::string sParseName(const std::string& sString, std::string& sErrorExpectedCharInfo, size_t& sPosition);

int iParseNumber(const std::string& sString, std::string& sErrorExpectedCharInfo, size_t& sPosition);

bool bReadInteger(std::string& sNumInString, int iLowBound, int iUpperBound, int& iIntegerValue, std::string& sErrorExpectedCharInfo);

bool bParseStringToLong(std::string& sUserInput, long& lParsedString, std::string& sErrorExpectedCharInfo);

bool bIsSpecialChar(const char c);
