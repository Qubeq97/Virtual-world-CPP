#include "Zwierze.h"
#include "Swiat.h"
#include <cstdlib>
#include <iostream>

Zwierze::~Zwierze()
{

}

void Zwierze::akcja()
{
	bool okay = false;
	while (!okay)
	{
		try
		{
			int los = rand() % 4;
			if (los == 0)
				this->kierunek = GORA;
			else if (los == 1)
				this->kierunek = DOL;
			else if (los == 2)
				this->kierunek = LEWO;
			else
				this->kierunek = PRAWO;
			poruszSie();
			okay = true;
		}
		catch (int)
		{
			okay = true;
			// jak natknie siê na œcianê, to tak jakby siê od niej odbije
		}
	}
}

void Zwierze::poruszSie()
{
	switch (kierunek)
	{
	case GORA:
		this->celX = this->x;
		this->celY = this->y - 1;
		break;
	case DOL:
		this->celX = this->x;
		this->celY = this->y + 1;
		break;
	case LEWO:
		this->celX = this->x - 1;
		this->celY = this->y;
		break;
	case PRAWO:
		this->celX = this->x + 1;
		this->celY = this->y;
		break;
	}
	if (this->celX < 0 || this->celX >= swiat->getX() || this->celY < 0 || this->celY >= swiat->getY())
		throw 1;
	else
	{
		Organizm* oponent = swiat->sprawdzKolizje(celX, celY);
		if (oponent == nullptr)
		{
			swiat->aktualizujPozycje(this, celX, celY);
			this->x = celX;
			this->y = celY;
		}
		else
		{
			if (oponent->getGatunek() == this->gatunek)
				rozmnozSie(oponent);
			else if (kolizja(oponent))
			{
				// zmieni pozycjê
				swiat->aktualizujPozycje(this, celX, celY);
				this->x = celX;
				this->y = celY;
			}
		}
	}
}

// je¿eli true, jest zgoda na ruch
bool Zwierze::kolizja(Organizm* oponent)
{
	OdbicieAtaku wynik = oponent->obrona(this);
	if (wynik == WYGRANA || wynik == WOLNEPOLE)
	{
		return true;
	}
	else if (wynik == PRZEGRANA)
	{
		this->Zabij();
	}
	return false;
	// je¿eli WYCOFANIE, nie ruszaæ siê - np. ¿ó³w jest w stanie tak odbiæ
}


void Zwierze::rozmnozSie(Organizm* partner)
{
	Kierunek kierunekRozmnazania;
	enum
	{
		TEN,
		PARTNER,
	}obok = TEN;

	bool koniec = false;
	int licznikProb = 0;
	while (!koniec)
	{
		try
		{
			int los = rand() % 4;
			if (licznikProb < 4)
			{
				if (los == 0)
					kierunekRozmnazania = GORA;
				else if (los == 1)
					kierunekRozmnazania = DOL;
				else if (los == 2)
					kierunekRozmnazania = LEWO;
				else
					kierunekRozmnazania = PRAWO;
				switch (kierunekRozmnazania)
				{
				case GORA:
					if (obok == TEN)
						swiat->stworzOrganizm(this->gatunek, this->getX(), this->getY() - 1);
					else
						swiat->stworzOrganizm(this->gatunek, partner->getX(), partner->getY() - 1);
					koniec = true;
					break;
				case DOL:
					if (obok == TEN)
						swiat->stworzOrganizm(this->gatunek, this->getX(), this->getY() + 1);
					else
						swiat->stworzOrganizm(this->gatunek, partner->getX(), partner->getY() + 1);
					koniec = true;
					break;
				case LEWO:
					if (obok == TEN)
						swiat->stworzOrganizm(this->gatunek, this->getX() - 1, this->getY());
					else
						swiat->stworzOrganizm(this->gatunek, partner->getX() - 1, partner->getY());
					koniec = true;
					break;
				case PRAWO:
					if (obok == TEN)
						swiat->stworzOrganizm(this->gatunek, this->getX() + 1, this->getY());
					else
						swiat->stworzOrganizm(this->gatunek, partner->getX() + 1, partner->getY());
					koniec = true;
					break;
				}
			}
			else
			{
				// je¿eli obok organizmów nie bêdzie miejsca, nie bêdzie nowego organizmu
				swiat->dopiszDoKonsoli("Brak miejsca do rozmnozenia dla " + this->nazwa + "\n");
				koniec = true;
				break;
			}

		}
		catch (int ex)
		{
			if (ex == 2) // je¿eli brak miejsca
				koniec = true; // bo i tak ju¿ nic nie dodam do pe³nego
			else if (ex == 1 || ex == 3) // je¿eli koliduje z ¿ywym lub próbuje wyjœæ poza planszê
			{
				if (obok == TEN)
					obok = PARTNER;
				else
				{
					obok = TEN;
					licznikProb++;
					switch (kierunekRozmnazania)
					{
					case GORA:
						kierunekRozmnazania = DOL;
						break;
					case DOL:
						kierunekRozmnazania = LEWO;
						break;
					case LEWO:
						kierunekRozmnazania = PRAWO;
						break;
					case PRAWO:
						kierunekRozmnazania = GORA;
						break;
					}
				}
			}
		}
		catch (...)
		{
			std::cout << "Nieznany blad rozmnazania." << endl;
			system("pause");
			exit(EXIT_FAILURE);
		}
	}
}

// zwraca, czy atakuj¹cy wygra³, czy ka¿e siê wycofaæ, czy przegra³
// je¿eli atakuj¹cy wygra³, ten ginie
OdbicieAtaku Zwierze::obrona(Organizm* atakujacy)
{
	if (this->sila <= atakujacy->getSila()) // przy równej sile wygrywa atakuj¹cy
	{
		swiat->dopiszDoKonsoli(atakujacy->getNazwa() + " wygrywa z " + this->nazwa + '\n');
		this->Zabij();
		return WYGRANA; // atakuj¹cy wygra³
	}
	else
	{
		swiat->dopiszDoKonsoli(this->nazwa + " wygrywa z " + atakujacy->getNazwa() + '\n');
		return PRZEGRANA; // atakuj¹cy przegra³
	}
}