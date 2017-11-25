#pragma once
#include <iostream>
#include <string>

static int count;

class ComplexNumber
{
public:
	ComplexNumber();
	ComplexNumber(double _real, double _imaginary);
	ComplexNumber(double _real);
	//ComplexNumber(std::string _str);
	ComplexNumber(const ComplexNumber &COther);
	~ComplexNumber();

	ComplexNumber operator + (ComplexNumber &COther);
	ComplexNumber operator - (ComplexNumber &COther);
	ComplexNumber operator * (ComplexNumber &COther);
	ComplexNumber operator / (ComplexNumber &COther);
	ComplexNumber &operator = (ComplexNumber &COther);

	friend std::ostream &operator << (std::ostream &out, ComplexNumber &COther);
	friend std::istream &operator >> (std::istream &out, ComplexNumber &COther);

	bool isZero();

private:
	double dReal;
	double dImaginary;
};

