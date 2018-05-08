#include "Lis.h"
#include "Swiat.h"


Lis::Lis(Swiat* swiat1, int x1, int y1)
{
	this->gatunek = LIS;
	this->sila = 3;
	this->inicjatywa = 7;
	this->znak = 'L';
	this->nazwa = "Lis";
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}


Lis::Lis(Swiat* swiat1, int x1, int y1, int sila)
{
	this->gatunek = LIS;
	this->sila = sila;
	this->inicjatywa = 7;
	this->znak = 'L';
	this->nazwa = "Lis";
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}

void Lis::poruszSie()
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
	if (celX < 0 || celX >= swiat->getX() || celY < 0 || celY >= swiat->getY())
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
			else if (oponent->getSila() <= this->sila) // je¿eli oponent mia³by wiêcej si³y, lis w ogóle nie spróbuje iœæ na tamto pole
			{
				if (kolizja(oponent))
				{
					// zmieni pozycjê
					swiat->aktualizujPozycje(this, celX, celY);
					this->x = celX;
					this->y = celY;
				}
			}
		}
	}
}