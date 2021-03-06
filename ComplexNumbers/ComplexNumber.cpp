#include "stdafx.h"
#include "ComplexNumber.h"


ComplexNumber::ComplexNumber()
{
	count++;
	dImaginary = 0;
	dReal = 0;
	//std::cout << "\t\t\t\tT Def count: " << count << std::endl;
}

ComplexNumber::ComplexNumber(double _real, double _imaginary)
{
	count++;
	dReal = _real;
	dImaginary = _imaginary;
	//std::cout << "\t\t\t\tT RI count: " << count << std::endl;
}

ComplexNumber::ComplexNumber(double _real)
{
	count++;
	dReal = _real;
	dImaginary = 0;
	//std::cout << "\t\t\t\tT R count: " << count << std::endl;
}


ComplexNumber::ComplexNumber(const ComplexNumber & COther)
{
	count++;
	dReal = COther.dReal;
	dImaginary = COther.dImaginary;
	//std::cout << "\t\t\t\tT CO count: " << count << std::endl;
}

ComplexNumber::~ComplexNumber()
{
	count--;
	//std::cout << "\t\t\t\tDcount: " << count << std::endl;
}

ComplexNumber ComplexNumber::operator + (ComplexNumber & COther)
{
	ComplexNumber iAdd;
	iAdd.dImaginary = dImaginary + COther.dImaginary;
	iAdd.dReal = dReal + COther.dReal;
	return iAdd;
}

ComplexNumber  ComplexNumber::operator-(ComplexNumber & COther)
{
	ComplexNumber iSub;
	iSub.dImaginary = dImaginary - COther.dImaginary;
	iSub.dReal = dReal - COther.dReal;
	return iSub;
}

ComplexNumber  ComplexNumber::operator*(ComplexNumber & COther)
{
	ComplexNumber iMul;
	iMul.dReal = (dReal * COther.dReal) - (dImaginary * COther.dImaginary);
	iMul.dImaginary = (dReal * COther.dImaginary) + (dImaginary * COther.dReal);
	return iMul;
}

ComplexNumber  ComplexNumber::operator/(ComplexNumber & COther)
{
	ComplexNumber iDiv;
	iDiv.dReal = ((dReal * COther.dReal) + (dImaginary * COther.dImaginary)) / (COther.dReal*COther.dReal + COther.dImaginary*COther.dImaginary);
	iDiv.dImaginary = ((dImaginary * COther.dReal) - (dReal * COther.dImaginary)) / (COther.dReal*COther.dReal + COther.dImaginary*COther.dImaginary);
	return iDiv;
}

ComplexNumber & ComplexNumber::operator = (ComplexNumber & COther)
{
	if (this == &COther) return *this;
	dImaginary = COther.dImaginary;
	dReal = COther.dReal;
	return *this;
}

bool ComplexNumber::isZero()
{
	return dReal == 0 && dImaginary == 0;
}


std::ostream & operator<<(std::ostream & out, ComplexNumber & COther)
{
	out << COther.dReal << ((COther.dImaginary > 0) ? "+" : "");
	if (COther.dImaginary != 0) out << COther.dImaginary << "i";
	return out;
}

std::istream &	 operator>>(std::istream & in, ComplexNumber & COther)
{
	std::string a;
	std::getline(in, a);
	int iBreak;
	iBreak = a.find_first_of("+-");
	if (iBreak != std::string::npos)
	{
		a.pop_back();
		COther.dReal = std::stod(a.substr(0, iBreak));
		COther.dImaginary = std::stod(a.substr(iBreak, a.length() - iBreak - 1));
	}
	else {
		COther.dReal = std::stod(a);
	}

	return in;
}
