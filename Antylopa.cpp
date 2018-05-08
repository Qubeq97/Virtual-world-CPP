#include "Antylopa.h"
#include "Swiat.h"


Antylopa::Antylopa(Swiat* swiat1, int x1, int y1)
{
	this->gatunek = ANTYLOPA;
	this->sila = 4;
	this->inicjatywa = 4;
	this->znak = 'A';
	this->x = x1;
	this->y = y1;
	this->nazwa = "Antylopa";
	this->swiat = swiat1;
}

Antylopa::Antylopa(Swiat* swiat1, int x1, int y1, int sila)
{
	this->gatunek = ANTYLOPA;
	this->sila = sila;
	this->inicjatywa = 4;
	this->znak = 'A';
	this->x = x1;
	this->y = y1;
	this->nazwa = "Antylopa";
	this->swiat = swiat1;
}



void Antylopa::poruszSie()
{
	switch (kierunek) // tu zmiany: zasiêg ruchu antylopy wynosi 2 pola!
	{
	case GORA:
		this->celX = this->x;
		this->celY = this->y - 2;
		break;
	case DOL:
		this->celX = this->x;
		this->celY = this->y + 2;
		break;
	case LEWO:
		this->celX = this->x - 2;
		this->celY = this->y;
		break;
	case PRAWO:
		this->celX = this->x + 2;
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

// true oznacza zgodê na ruch
bool Antylopa::kolizja(Organizm* oponent)
{
	int los = rand() % 2;
	if (los == 0 && swiat->czyZwierze(oponent->getGatunek())) // 50% szans na ucieczkê przed walk¹ przed innym zwierzêciem
	{
		bool koniec = false;
		int licznikProb = 0;
		while (!koniec)
		{
			los = rand() % 4;
			if (los == 0)
				this->kierunek = GORA;
			else if (los == 1)
				this->kierunek = DOL;
			else if (los == 2)
				this->kierunek = LEWO;
			else
				this->kierunek = PRAWO;
			switch (kierunek)
			{
			case GORA:
				this->celX = oponent->getX();
				this->celY = oponent->getY() - 1;
				break;
			case DOL:
				this->celX = oponent->getX();
				this->celY = oponent->getY() + 1;
				break;
			case LEWO:
				this->celX = oponent->getX() - 1;
				this->celY = oponent->getY();
				break;
			case PRAWO:
				this->celX = oponent->getX() + 1;
				this->celY = oponent->getY();
				break;
			}
			if (this->celX >= 0 && this->celX < swiat->getX() && this->celY >= 0 && this->celY < swiat->getY())
			{
   				if (swiat->sprawdzKolizje(this->celX, this->celY) == nullptr)
				{
					swiat->dopiszDoKonsoli(this->nazwa + " ucieka przed " + oponent->getNazwa() + '\n');
					return true;
					// jest zgoda na ruch, ale ju¿ w nowe pole niezajête obok oponenta
					// albowiem celX i celY s¹ zmienione
					// i wywo³a siê aktualizujPozycje dla nowych celX i celY
				}
			}
			licznikProb++;
			if (licznikProb == 4)
			{
				this->celX = oponent->getX();
				this->celY = oponent->getY();
				koniec = true;
				break;
			}
			if (kierunek == GORA)
				this->kierunek = DOL;
			else if (kierunek == DOL)
				this->kierunek = LEWO;
			else if (kierunek == LEWO)
				this->kierunek = PRAWO;
			else if (kierunek == PRAWO)
				this->kierunek = GORA;
		}
	}
	// je¿eli nie zwieje od walki, wywo³a siê standardowa metoda obs³ugi kolizji
	return Zwierze::kolizja(oponent);
}

OdbicieAtaku Antylopa::obrona(Organizm* atakujacy)
{
	int obecneX = this->x;
	int obecneY = this->y;
	int los = rand() % 2;
	if (los == 0 && swiat->czyZwierze(atakujacy->getGatunek())) // 50% szans na ucieczkê przed walk¹ przed innym zwierzeciem
	{
		bool koniec = false;
		int licznikProb = 0;
		while (!koniec)
		{
			los = rand() % 4;
			if (los == 0)
				this->kierunek = GORA;
			else if (los == 1)
				this->kierunek = DOL;
			else if (los == 2)
				this->kierunek = LEWO;
			else
				this->kierunek = PRAWO;
			switch (kierunek)
			{
			case GORA:
				this->celX = obecneX;
				this->celY = obecneY - 1;
				break;
			case DOL:
				this->celX = obecneX;
				this->celY = obecneY + 1;
				break;
			case LEWO:
				this->celX = obecneX - 1;
				this->celY = obecneY;
				break;
			case PRAWO:
				this->celX = obecneX + 1;
				this->celY = obecneY;
				break;
			}
			if (this->celX >= 0 && this->celX < swiat->getX() && this->celY >= 0 && this->celY < swiat->getY())
			{
				if (swiat->sprawdzKolizje(celX, celY) == nullptr)
				{
					// je¿eli jest obok wolne pole, antylopa zwieje
					// a to zwolni miejsce dla atakuj¹cego
					// i bêdzie móg³ tam wejœæ
					swiat->aktualizujPozycje(this, celX, celY);
					this->x = celX;
					this->y = celY;
   					swiat->dopiszDoKonsoli(this->nazwa + " ucieka przed " + atakujacy->getNazwa() + '\n');
					return WOLNEPOLE;
				}
			}

			licznikProb++;
			if (licznikProb == 4)
			{
				koniec = true;
				break;
			}
			if (kierunek == GORA)
				this->kierunek = DOL;
			else if (kierunek == DOL)
				this->kierunek = LEWO;
			else if (kierunek == LEWO)
				this->kierunek = PRAWO;
			else if (kierunek == PRAWO)
				this->kierunek = GORA;
		}
	}
	// je¿eli nie zwieje od walki, wywo³a siê standardowa metoda obs³ugi obrony
	return Zwierze::obrona(atakujacy);
}

