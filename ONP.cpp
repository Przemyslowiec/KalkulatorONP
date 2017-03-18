#include "ONP.h"
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <map>
#include <math.h>

void sprawdzanie(std::string &w) {
	bool poprawnosc = true;
	for (int i = 0; i < w.size(); i++) {
		if ((w[i] == '.' || w[i] == ',') && (static_cast<int>(w[i - 1]) >= 48 && static_cast<int>(w[i] - 1) <= 57) && (static_cast<int>(w[i + 1]) >= 48 && static_cast<int>(w[i + 1]) <= 57)) {
			if (w[i] == ',') {
				w.erase(i, 1);
				w.insert(i, ".");
			}
		}
	}
}

std::vector<std::string> dzielenie(std::string w) {
	std::string czesc; //zmienna pomocnicza(najpotrzebniejsza w while) ma przede wszystkim przechowywaæ liczbê
	std::vector<std::string> gotowe; //przechowywanie podzielonych danych wejsciowych
	int k; //zmienna pomicnicza (osobny licznik do while, po wyjsciu z while i=k)
	for (int i = 0; i < w.size(); i++) { //przejrzenie wszystkich elementow string
		if (static_cast<int>(w[i]) >= 48 && static_cast<int>(w[i]) <= 57 || static_cast<int>(w[i] == 46)) {
			k = i;
			czesc.clear(); //czyszczenie
			while ((static_cast<int>(w[k]) >= 48 && static_cast<int>(w[k]) <= 57) || (static_cast<int>(w[k]) == 46)) {
				//	std::clog << w[k] << " ";
				czesc += w[k];
				k++;
			}
			k--;
			gotowe.push_back(czesc);
			i = k;
			czesc.clear();
		}
		else {
			czesc.clear();
			czesc += w[i];
			gotowe.push_back(czesc);
			czesc.clear();
		}
	}
	return gotowe;
}

std::vector<std::string> konw(std::vector<std::string> wek) {
	//priorytety
	std::map<std::string, int> priorytety;
	priorytety["("] = 0;
	priorytety["+"] = 1;
	priorytety["-"] = 1;
	priorytety["*"] = 2;
	priorytety["/"] = 2;
	priorytety["^"] = 3;
	std::vector<std::string> wyjscie;
	std::stack<std::string> stos;
	std::string tek;
	for (unsigned int i = 0; i < wek.size(); i++) {
		tek.clear();
		tek += wek[i];
		//jest liczb¹
		if (atoi(tek.c_str()) != 0 || tek == "0") {
			wyjscie.push_back(tek);
		}
		else {//nie jest liczb¹
			if (tek == "(") {
				stos.push(tek);
			}
			if (tek == ")") {//jeœli jest prawym nawiasem wszstko do ( wyœlij na wyjœcie a ( zrzuæ
				while (stos.top() != "(") {
					wyjscie.push_back(stos.top());
					stos.pop();
				}
				stos.pop();
			}
			//jest operatorem
			if (tek == "+" || tek == "-" || tek == "*" || tek == "*" || tek == "/" || tek == "^") {
				if (stos.empty() == true) {
					stos.push(tek);
				}//stos nie jest pusty
				else {
					if (priorytety[tek] > priorytety[stos.top()]) {
						stos.push(tek);
					}
					//if (priorytety[tek] <= priorytety[stos.top()]) 
					else {
						while (stos.empty() == false && priorytety[tek] <= priorytety[stos.top()])
						{
							wyjscie.push_back(stos.top());
							stos.pop();
						}
						stos.push(tek);
					}
				}
			}
		}
	}
	while (!stos.empty())
	{
		wyjscie.push_back(stos.top());
		stos.pop();
	}
	return wyjscie;
}

double obliczanie(std::vector<std::string> w) {
	std::map<std::string, int> priorytety; //potrzebne do wybrania odpowiedniej opcji póŸniej 
	priorytety["+"] = 1;
	priorytety["-"] = 2;
	priorytety["*"] = 3;
	priorytety["/"] = 4;
	priorytety["^"] = 5;
	std::stack<double> stos; //wykonywane operacje na nim
	double a, b; //zmienne pomocnicze do zapamiêtywania wartosci ze stosu
	for (unsigned int i = 0; i < w.size(); i++) {
		//jest liczb¹

		if (w[i] != "+" && w[i] != "-" && w[i] != "*" && w[i] != "*" && w[i] != "/" & w[i] != "^") {
			stos.push(std::stod(w[i]));
		}
		else { //nie jest liczb¹
			a = stos.top(); //zapamiêtywanie i œci¹ganie ze stosu liczb
			stos.pop();
			b = stos.top();
			stos.pop();
			switch (priorytety[w[i]]) //wykonywanie odpowiedniej akcji w zale¿noœci od operatora
			{
			case 1:

				stos.push(b + a);

				break;
			case 2:
				stos.push(b - a);
				break;
			case 3:
				stos.push(b*a);
				break;
			case 4:
				stos.push(b / a);
				break;
			case 5:
				stos.push(pow(b, a));
				break;
			}
		}
	}
	return stos.top();
}

void wyswietl(std::vector<std::string>we) {
	for (auto i = 0; i <we.size(); i++)
	{
		std::clog << we[i] << " ";
	}
}
