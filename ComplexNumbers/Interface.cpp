#include "stdafx.h"
#include "Interface.h"

CInterface::CInterface() {}
CInterface::~CInterface() {}

int CInterface::iCommand()
{
	listOfTokens.clear();
	int _errlog;
	std::string _command;
	std::getline(std::cin, _command);
	listOfTokens = tokenize(_command);
	_command = listOfTokens.front();
	listOfTokens.pop_front();

	if (_command == COM_ADDNUM)				_errlog = iAddNum();
	else if (_command == COM_DELETE)		_errlog = iDelete();
	else if (_command == COM_DELETE_ALL)	_errlog = iDeleteAll();
	else if (_command == COM_PRINT_ONE)		_errlog = iPrintOne();
	else if (_command == COM_PRINT_ALL)		_errlog = iPrintAll();
	else if (_command == COM_HELP || _command == COM_HELP2)
		_errlog = iHelp();
	else if (_command == COM_ADD)			_errlog = iAdd();
	else if (_command == COM_SUB)			_errlog = iSub();
	else if (_command == COM_MUL)			_errlog = iMul();
	else if (_command == COM_DIV)			_errlog = iDiv();
	else if (_command == COM_ENTER)			_errlog = I_ERR_OK;
	else if (_command == COM_EXIT)			_errlog = I_EXIT;
	else
		_errlog = I_ERR_UNKNOWN_COMMAND;

	switch (_errlog)
	{
	case I_ERR_UNKNOWN_COMMAND:		std::cout << S_ERR_UNKNOWN_COMMAND;		break;
	case I_ERR_NOT_ENOUGH_ARGS:		std::cout << S_ERR_NOT_ENOUGH_ARGS;		break;
	case I_ERR_TOO_MANY_ARGS:		std::cout << S_ERR_TOO_MANY_ARGS;		break;
	case I_ERR_INVALID_ARGS:		std::cout << S_ERR_INVALID_ARGS;		break;
	case I_ERR_OUT_OF_BOUNDS:		std::cout << S_ERR_OUT_OF_BOUNDS;		break;
	case I_ERR_NOT_SUPPORTED:		std::cout << S_ERR_NOT_SUPPPORTED;		break;
	case I_ERR_DIVIDING_BY_ZERO:	std::cout << S_ERR_DIVIDING_BY_ZERO;	break;
	}

	return _errlog;
}

int CInterface::iAddNum()
{
	if (listOfTokens.size() > 1) return I_ERR_TOO_MANY_ARGS;
	if (listOfTokens.size() < 1) return I_ERR_NOT_ENOUGH_ARGS;

	std::string sNumber = listOfTokens.front();

	// TODO: Checking if token is legit number

	vctrNumbers.push_back(ComplexNumber(sNumber));

	std::cout << "Dodano: " << vctrNumbers.back();
	Sleep(1500);
	system("cls");

	return I_ERR_OK;
}

int CInterface::iDelete()
{
	if (listOfTokens.size() > 1) return I_ERR_TOO_MANY_ARGS;
	if (listOfTokens.size() < 1) return I_ERR_NOT_ENOUGH_ARGS;
	if (listOfTokens.front().find_first_not_of("1234567890") != std::string::npos) return I_ERR_INVALID_ARGS;

	int i = std::stoi(listOfTokens.front());

	if (i > (vctrNumbers.size() - 1)) return I_ERR_OUT_OF_BOUNDS;

	vctrNumbers.erase(vctrNumbers.begin() + i);

	system("cls");

	return I_ERR_OK;
}

int CInterface::iDeleteAll()
{
	if (listOfTokens.size() > 0) return I_ERR_TOO_MANY_ARGS;
	vctrNumbers.clear();

	system("cls");

	return I_ERR_OK;
}

int CInterface::iPrintAll()
{
	system("cls");

	if (listOfTokens.size() > 0) return I_ERR_TOO_MANY_ARGS;

	for (int i = 0; i < vctrNumbers.size(); i++)
	{
		std::cout << "[" << i << "] " << vctrNumbers.at(i) << "\t";
	}
	std::cout << std::endl;

	return I_ERR_OK;
}

int CInterface::iPrintOne()
{
	system("cls");

	if (listOfTokens.size() > 1) return I_ERR_TOO_MANY_ARGS;
	if (listOfTokens.size() < 1) return I_ERR_NOT_ENOUGH_ARGS;
	if (listOfTokens.front().find_first_not_of("1234567890") != std::string::npos) return I_ERR_INVALID_ARGS;

	int i = std::stoi(listOfTokens.front());

	if (i > (vctrNumbers.size() - 1)) return I_ERR_OUT_OF_BOUNDS;

	std::cout << "[" << i << "]: " << vctrNumbers.at(i) << std::endl;

	return I_ERR_OK;
}

int CInterface::iHelp()
{
	if (listOfTokens.size() > 0) return I_ERR_TOO_MANY_ARGS;
	system("cls");
	std::cout << "Witaj w pomocy! Jestes tu bo nikt nie dostarczyl Ci informacji jak korzystac z tego zalosnego programu\n"
		<< "\"Program\" oferuje nastepujace mozliwosci:\n"
		<< "\tenter - dodaj nowa liczbe (enter 12; enter 2+3i; enter -4i)\n"
		<< "\tdel x - usun liczbe na pozycji x (del 2)\n"
		<< "\tdelall - usun wszystkie liczby \n"
		<< "\tprint x - wydrukuj liczbe na x pozycji (print x) \n"
		<< "\tprintall - wydrukuj wszystkie liczby \n"
		<< "\tadd x y - dodaj liczby na pozycjach x y oraz dodaj wynik do tablicy (add 2 0) \n"
		<< "\tsub x y - odejmij liczby na pozycjach x y oraz dodaj wynik do tablicy (sub 2 0) \n"
		<< "\tmul x y - pomnoz liczby na pozycjach x y oraz dodaj wynik do tablicy (mul 2 0) \n"
		<< "\tdiv x y - podziel liczby na pozycjach x y oraz dodaj wynik do tablicy (div 2 0) \n"
		<< "\thelp lub ? - wyswietl pomoc\n"
		<< "\texit - zakoncz prace programu\n"
		<< "Powodzenia!\n";
	return I_ERR_OK;
}

int CInterface::iAdd()
{
	system("cls");

	int a, b;

	if (listOfTokens.size() > 2) return I_ERR_TOO_MANY_ARGS;
	if (listOfTokens.size() < 2) return I_ERR_NOT_ENOUGH_ARGS;
	if (listOfTokens.front().find_first_not_of("1234567890") != std::string::npos) return I_ERR_INVALID_ARGS;

	a = std::stoi(listOfTokens.front());
	if (a > (vctrNumbers.size() - 1)) return I_ERR_OUT_OF_BOUNDS;

	listOfTokens.pop_front();

	if (listOfTokens.front().find_first_not_of("1234567890") != std::string::npos) return I_ERR_INVALID_ARGS;
	b = std::stoi(listOfTokens.front());
	if (b > (vctrNumbers.size() - 1)) return I_ERR_OUT_OF_BOUNDS;

	ComplexNumber add = vctrNumbers.at(a) + vctrNumbers.at(b);
	std::cout << "Suma to: " << add << std::endl;
	vctrNumbers.push_back(add);

	return I_ERR_OK;
}

int CInterface::iSub()
{
	system("cls");

	int a, b;

	if (listOfTokens.size() > 2) return I_ERR_TOO_MANY_ARGS;
	if (listOfTokens.size() < 2) return I_ERR_NOT_ENOUGH_ARGS;
	if (listOfTokens.front().find_first_not_of("1234567890") != std::string::npos) return I_ERR_INVALID_ARGS;

	a = std::stoi(listOfTokens.front());
	if (a > (vctrNumbers.size() - 1)) return I_ERR_OUT_OF_BOUNDS;

	listOfTokens.pop_front();

	if (listOfTokens.front().find_first_not_of("1234567890") != std::string::npos) return I_ERR_INVALID_ARGS;
	b = std::stoi(listOfTokens.front());
	if (b > (vctrNumbers.size() - 1)) return I_ERR_OUT_OF_BOUNDS;

	ComplexNumber add = vctrNumbers.at(a) - vctrNumbers.at(b);
	std::cout << "Roznica to: " << add << std::endl;
	vctrNumbers.push_back(add);

	return I_ERR_OK;
}

int CInterface::iMul()
{
	system("cls");

	int a, b;

	if (listOfTokens.size() > 2) return I_ERR_TOO_MANY_ARGS;
	if (listOfTokens.size() < 2) return I_ERR_NOT_ENOUGH_ARGS;
	if (listOfTokens.front().find_first_not_of("1234567890") != std::string::npos) return I_ERR_INVALID_ARGS;

	a = std::stoi(listOfTokens.front());
	if (a > (vctrNumbers.size() - 1)) return I_ERR_OUT_OF_BOUNDS;

	listOfTokens.pop_front();

	if (listOfTokens.front().find_first_not_of("1234567890") != std::string::npos) return I_ERR_INVALID_ARGS;
	b = std::stoi(listOfTokens.front());
	if (b > (vctrNumbers.size() - 1)) return I_ERR_OUT_OF_BOUNDS;

	ComplexNumber add = vctrNumbers.at(a) * vctrNumbers.at(b);
	std::cout << "Iloczyn to: " << add << std::endl;
	vctrNumbers.push_back(add);

	return I_ERR_OK;
}

int CInterface::iDiv()
{
	system("cls");

	int a, b;

	if (listOfTokens.size() > 2) return I_ERR_TOO_MANY_ARGS;
	if (listOfTokens.size() < 2) return I_ERR_NOT_ENOUGH_ARGS;
	if (listOfTokens.front().find_first_not_of("1234567890") != std::string::npos) return I_ERR_INVALID_ARGS;

	a = std::stoi(listOfTokens.front());
	if (a > (vctrNumbers.size() - 1)) return I_ERR_OUT_OF_BOUNDS;

	listOfTokens.pop_front();

	if (listOfTokens.front().find_first_not_of("1234567890") != std::string::npos) return I_ERR_INVALID_ARGS;
	b = std::stoi(listOfTokens.front());
	if (a > (vctrNumbers.size() - 1)) return I_ERR_OUT_OF_BOUNDS;

	if (vctrNumbers.at(b).isZero()) return I_ERR_DIVIDING_BY_ZERO;

	ComplexNumber add = vctrNumbers.at(a) / vctrNumbers.at(b);
	std::cout << "Iloraz to: " << add << std::endl;
	vctrNumbers.push_back(add);

	return I_ERR_OK;
}

bool CInterface::bCheckToken(std::string token)
{
	std::list<std::string> tmp = tokenize(token, '+', '-');

	int i = token.find_last_of("-+");

	if (tmp.size() > 2) return false;
	if (tmp.size() > 1) {
		if (token[i - 1] == '+' || token[i - 1] == '-') return false;
		if (i == token.size() - 1) return false;
	}

	i = token.find('i');
	if (i != std::string::npos && i != token.size() - 1) return false;

	return true;
}


std::list<std::string> CInterface::tokenize(std::string _str, char sep, char pom)
{
	std::list<std::string> lista;
	std::string tmp = "";
	if (_str == "") lista.push_back("");
	else
	{
		for (std::string::iterator i = _str.begin(); i < _str.end(); ++i)
		{
			if (((const char)*i != sep && (const char)*i != pom) && i != _str.end())
			{
				tmp += *i;
			}
			else
			{
				if (tmp != "")
				{
					lista.push_back(tmp);
				}
				tmp = "";
			}
		}
		if (tmp != "")
		{
			lista.push_back(tmp);
		}
	}
	return lista;
}