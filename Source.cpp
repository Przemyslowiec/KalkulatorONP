#include "ONP.h"
#include <string>
#include <iostream>

int main()
{
	std::string rownanie;
	std::clog << "Podaj rowanie do obliczenia: \n";
	std::getline(std::cin, rownanie);
	sprawdzanie(rownanie);
	std::clog << "Postac w ONP: ";
	wyswietl(konw(dzielenie(rownanie)));
	std::clog << "\nWynik: ";
	std::clog << "\n" << obliczanie(konw(dzielenie(rownanie)));
	return 0;
}

