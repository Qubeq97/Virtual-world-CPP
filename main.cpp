#include <iostream>

// do randa
#include <cstdlib>
#include <ctime>

#include <conio.h>

#include "Swiat.h"

enum Gatunek
{
	WILK,
	OWCA,
	LIS,
	ZOLW,
	ANTYLOPA,
	TRAWA,
	MLECZ,
	GUARANA,
	JAGODY,
	BARSZCZ,
	CZLOWIEK,
	CYBEROWCA
};

enum Kierunek
{
	GORA,
	DOL,
	LEWO,
	PRAWO
};

using namespace std;

int main()
{
	srand(time(NULL));
	cout << "Wirtualny swiat - projekt PO, C++" << endl;
	cout << "1 - wymiary domyslne 20x20, 2 - wlasne wymiary, 3 - wczytaj z pliku"<<endl;
	cout << "ESC - wyjscie" << endl;
	int kod, wynik, x, y;
	Swiat* swiat = nullptr;
	while (kod = _getch())
	{
		if (kod == 49)
		{
			wynik = 1;
			break;
		}
		else if (kod == 50)
		{
			wynik = 2;
			break;
		}
		else if (kod == 51)
		{
			wynik = 3;
			break;
		}
		else if (kod == 27)
			exit(EXIT_SUCCESS);
		else
			cout << "Nie ten klawisz!" << endl;
	}
	switch (wynik)
	{
	case 1:
		try
		{
			swiat = new Swiat();
		}
		catch (...)
		{
			cout << "Blad losowej inicjalizacji swiata, program konczy dzialanie." << endl;
			exit(EXIT_FAILURE);
		}
		break;
	case 2:
		cout << "Podaj szerokosc" << endl;
		cin >> x;
		cout << "Podaj wysokosc" << endl;
		cin >> y;
		try
		{
			swiat = new Swiat(x, y);
		}
		catch (int ex)
		{
			if (ex == 0)
			{
				cout << "Za male wymiary! Program rozpocznie dzialanie z wymiarami domyslnymi." << endl;
				system("pause");
				try
				{
					swiat = new Swiat();
				}
				catch (...)
				{
					cout << "Blad inicjalizacji swiata, program konczy dzialanie." << endl;
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				cout << "Blad losowej inicjalizacji swiata, program konczy dzialanie." << endl;
				exit(EXIT_FAILURE);
			}
		}
		catch (...)
		{
			cout << "Blad inicjalizacji swiata, program konczy dzialanie." << endl;
			exit(EXIT_FAILURE);
		}
		break;
	case 3:
		try
		{
			swiat = new Swiat("stan.txt");
		}
		catch (int ex)
		{
			if (ex == -1)
			{
				cout << "Blad odczytu z pliku!" << endl;
				exit(EXIT_FAILURE);
			}
			else if (ex == -2)
			{
				cout << "Plik zawiera bledne dane!" << endl;
				exit(EXIT_FAILURE);
			}
		}
		break;
	}
	bool koniec = false;
	swiat->pokazSwiat();
	swiat->pokazKonsole();
	cout << "n - nowa tura, s - zapis, ESC - koniec" << endl;
	while (!koniec)
	{
		
		kod = _getch();
		switch (kod)
		{
		case 110:
			swiat->wykonajTure();
			cout << "n - nowa tura, s - zapis, ESC - koniec" << endl;
			break;
		case 115:
			try
			{
				swiat->zapiszDoPliku("stan.txt");
				cout << "Zapisano pomyslnie" << endl;
			}
			catch (...)
			{
				cout << "Blad zapisu!" << endl;
			}
			break;
		case 27:
			koniec = true;
			break;
		}
	}
	delete swiat;
	return 0;
}