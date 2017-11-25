#pragma once
#include "ComplexNumber.h"
#include <list>
#include <vector>
#include "Errors.h"
#include <Windows.h>
#include "ComplexNumber.h"
#include "commands.h"
#include "help.h"

class CInterface
{
public:

	CInterface();
	~CInterface();

	int iCommand();
private:

	int iAddNum();
	int iDelete();
	int iDeleteAll();
	int iPrintAll();
	int iPrintOne();
	int iHelp();

	std::list<std::string> tokenize(std::string _str, char sep = ' ', char pom = ' ');

	int iAdd();
	int iSub();
	int iMul();
	int iDiv();

	bool bCheckToken(std::string token);

	std::vector<ComplexNumber> vctrNumbers;
	std::list<std::string> listOfTokens;
};

