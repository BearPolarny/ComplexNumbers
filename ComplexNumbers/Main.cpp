#include "stdafx.h"
#include "ComplexNumber.h"
#include "Interface.h"

int main()
{
	{
		CInterface a;
		std::cout << "Jesli nie znasz komend wpisz help lub ? aby otrzymac pomoc\n";
		while (a.iCommand() != -1);
	}
	//system("pause");
	return 0;
}

