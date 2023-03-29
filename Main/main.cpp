#include "Polynom.h"
#include <iostream>




int main()
{
	Polynomial pol1;
	Polynomial pol2;
	Polynomial pol3;
	Monom m(0, 0);
	ifstream file("C:/Users/stm_0/source/repos/PolinomLab/PolinomLab/cmake/test.txt");
	file >> pol1;
	file >> pol2;

	try
	{
		cout << pol1 << endl << pol2 << endl;
		pol3 = pol1 + pol2;
		cout << pol3 << endl;;
	}
	catch(exception)
	{
		cout << "exception!";
	}
	//cout << pol1.Calculate(Triple<float>(1, 1, 1));
}



