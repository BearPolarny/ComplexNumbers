#include "stdafx.h"
#include "ComplexNumber.h"
#include "Interface.h"
#include "help.h"


int main()
{
	{
		CInterface a;
		std::cout << COMMENT_HELP;
		while (a.iCommand() != -1);
	}
	//system("pause");
	return 0;
}

