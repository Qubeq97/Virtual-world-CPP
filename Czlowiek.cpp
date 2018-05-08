#include "Czlowiek.h"
#include "Swiat.h"
#include <iostream>
#include <conio.h>
using namespace std;
/*
	Przydzia³ spec. umiejêtnoœci:
	- mój numer indeksu to 165761
	- ostatnia cyfra to 1
	- 1 mod 5 wynosi 1
	- u¿yta umiejêtnoœæ: MAGICZNY ELIKSIR

	Opis spec. umiejêtnoœci:
	- si³a roœnie do 10 w pierwszej turze dzia³ania, potem maleje a¿ do pocz¹tkowej
*/

Czlowiek::Czlowiek(Swiat* swiat1, int x1, int y1)
{
	this->gatunek = CZLOWIEK;
	this->sila = 5;
	this->inicjatywa = 4;
	this->znak = '$';
	this->x = x1;
	this->y = y1;
	this->nazwa = "Czlowiek";
	this->swiat = swiat1;
}

Czlowiek::Czlowiek(Swiat* swiat1, int x1, int y1, int sila, bool aktywna, int tura, bool czy_wolno)
{
	this->gatunek = CZLOWIEK;
	this->sila = 5;
	this->inicjatywa = 4;
	this->znak = '$';
	this->x = x1;
	this->y = y1;
	this->nazwa = "Czlowiek";
	this->swiat = swiat1;
	this->spec_aktywna = aktywna;
	this->tura = tura;
	this->czy_wolno = czy_wolno;

}





void Czlowiek::akcja()
{
	bool koniec = false;
	swiat->pokazSwiat();
	swiat->ustawKursor(0, swiat->getY() + 2);
	cout << "Masz "<<sila<<" sily. Strzalki - ruch\n";
	if (!spec_aktywna)
	{
		if (czy_wolno)
			cout << "Spec-skill nieaktywny. Mozesz go wlaczyc klawiszem s\n";
		else
			cout << "Musisz poczekac " << 5-tura << " tur z nowa dawka eliksiru\n";
	}
	else
	{
		cout << "Eliksir dziala jeszcze przez " << 5 - tura << " nastepnych tur\n";
	}
	while (!koniec)
	{
		int kod = _getch();
		switch (kod)
		{
		case 224:
			kod = _getch();
			switch (kod)
			{
			case 72:
				this->kierunek = GORA;
				koniec = true;
				break;
			case 80:
				this->kierunek = DOL;
				koniec = true;
				break;
			case 75:
				this->kierunek = LEWO;
				koniec = true;
				break;
			case 77:
				this->kierunek = PRAWO;
				koniec = true;
				break;
			}
			break;
		case 115:
			aktywujEliksir();
			break;
		}
	}
	try
	{
		this->poruszSie();
	}
	catch (int)
	{
		;
	}
	if (spec_aktywna)
	{
		tura++;
		sila--;
		if (tura >= 5)
		{
			spec_aktywna = false;
			czy_wolno = false; // ban na eliksir
			tura = 0; // i teraz ju¿ liczymy 5 tur bana na eliksir
		}
	}
	else
	{
		if (!czy_wolno)
		{
			tura++;
			if (tura >= 5)
			{
				tura = 0;
				czy_wolno = true; // ban siê koñczy
			}
		}
	}
}

void Czlowiek::aktywujEliksir()
{
	if (!spec_aktywna && czy_wolno)
	{
		sila +=5;
		tura = 0;
		spec_aktywna = true;
		cout << "Aktywowano MAGICZNY ELIKSIR! Masz teraz "<<sila<<" sily\n";
	}
	else if (!czy_wolno)
		cout << "SORRY, ale musisz poczekac!\n";
	else if (spec_aktywna)
		cout << "Eliksir jeszcze dziala!\n";
}

bool Czlowiek::czyAktywna()
{
	return this->spec_aktywna;
}

int Czlowiek::getTura()
{
	return this->tura;
}

bool Czlowiek::czyWolno()
{
	return this->czy_wolno;
}




