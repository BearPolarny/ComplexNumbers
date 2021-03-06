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


	double dReal, dImaginary;

	
	int iMusiBycLepszySposob = iCheckToken(dReal, dImaginary);		// Zjebane. Musi by� jaki� 
	if (iMusiBycLepszySposob) return iMusiBycLepszySposob;			// szybszy i kr�tszy spos�b,
	// dalszy kod gdy nie bylo bledu								// kt�ry mi umyka
																	
	vctrNumbers.push_back(ComplexNumber(dReal, dImaginary));

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

	size_t i = std::stoi(listOfTokens.front());

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

	for (size_t i = 0; i < vctrNumbers.size(); i++)
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

	size_t i = std::stoi(listOfTokens.front());

	if (i > (vctrNumbers.size() - 1)) return I_ERR_OUT_OF_BOUNDS;

	std::cout << "[" << i << "]: " << vctrNumbers.at(i) << std::endl;

	return I_ERR_OK;
}

int CInterface::iHelp()
{
	if (listOfTokens.size() > 0) return I_ERR_TOO_MANY_ARGS;
	system("cls");
	std::cout << HELP;
	return I_ERR_OK;
}

int CInterface::iAdd()
{
	system("cls");

	size_t a, b;

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

	size_t a, b;

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

	size_t a, b;

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

	size_t a, b;

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

int CInterface::iCheckToken(double &dReal, double &dImaginary)
{
	std::string sNumber = listOfTokens.front();

	if (sNumber.find_first_not_of("1234567890.+-i") != std::string::npos) return I_ERR_INVALID_ARGS;						// Odrzucamy ca�kowicie b��dne zapisy
	if (sNumber.size() == 1 && sNumber[0] == 'i') {		// enter i
		dReal = 0;
		dImaginary = 1;
		return I_ERR_OK;			// XD
									// To trzeba zmienic jak najszybciej zeby nikt nie zobaczyl
	}
	if (sNumber.size() == 2 && sNumber[1] == 'i' && (sNumber[0] == '-' || sNumber[0] == '+')) { // enter -i 
		dReal = 0;
		sNumber[0] == '-' ? dImaginary = -1 : dImaginary = 1;
		return I_ERR_OK;			// Tu to samo, kek
	}
	if (sNumber.find_last_of("1234567890") == std::string::npos) return I_ERR_INVALID_ARGS;								// Odrzucamy zapisy samych znakow: ++i.
	if (sNumber.find('i') != std::string::npos && sNumber.find('i') != sNumber.size() - 1) return I_ERR_INVALID_ARGS;	// Odrzucamy zapisy z 'i' w �rodku:  3i+3
	if (sNumber.find_last_of("+-") == sNumber.size() - 1) return I_ERR_INVALID_ARGS;										// Odrzucamy zapisy z +- na koncu: 3+; 3+1i-

	if (sNumber.size() > 1)
	{
		for (size_t i = 1; i < sNumber.size(); i++)
		{
			if (sNumber[i] == '+' || sNumber[i] == '-')
			{
				if (sNumber[i - 1] == '+' || sNumber[i - 1] == '-') return I_ERR_INVALID_ARGS;
			}
		}
	}

	if (tokenize(sNumber, '+', '-').size() > 2) return I_ERR_INVALID_ARGS;

	if (tokenize(sNumber, '+', '-').size() >= 2 && sNumber[sNumber.size() - 1] != 'i') return I_ERR_INVALID_ARGS;

	for (size_t i = 1; i < sNumber.size(); i++)
	{
		if (sNumber[i] == 'i' && (sNumber[i - 1] == '+' || sNumber[i - 1] == '-')) {
			sNumber[i - 1] == '+' ? dImaginary = 1 : dImaginary = -1;
			dReal = std::stod(sNumber.substr(0, i));

			return I_ERR_OK;          // To to ju� jest kompletna patologia...
		}
	}

	if (sNumber.size() > 1)
	{
		for (size_t i = 1; i < sNumber.size(); i++)
		{
			if (sNumber[i] == '.')
			{
				if (sNumber[i - 1] == '.') return I_ERR_INVALID_ARGS;
			}
		}
	}

	if (sNumber.find('i') == std::string::npos) {
		dReal = std::stod(sNumber);
		dImaginary = 0;
		return I_ERR_OK;
	}
	if ((sNumber.find_last_of("+-") == 0 || sNumber.find_last_of("+-") == std::string::npos) && sNumber[sNumber.size() - 1] == 'i')
	{
		dReal = 0;
		sNumber.pop_back();
		dImaginary = std::stod(sNumber);
		return I_ERR_OK;
	}



	dReal = std::stod(sNumber.substr(0, sNumber.find_last_of("+-")));
	dImaginary = std::stod(sNumber.substr(sNumber.find_last_of("+-"), sNumber.size() - sNumber.find_last_of("+-")));



	return I_ERR_OK;
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