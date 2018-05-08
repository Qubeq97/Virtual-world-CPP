#include "Roslina.h"
#include "Swiat.h"


Roslina::Roslina()
{
	inicjatywa = 0;
}

Roslina::~Roslina()
{

}


void Roslina::akcja()
{
	int los = rand() % 10;
	if (los < 3) // np. niech prawdopodobie�stwo wyniesie 30%
	{
		int noweX, noweY;
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
			noweX = this->x;
			noweY = this->y - 1;
			break;
		case DOL:
			noweX = this->x;
			noweY = this->y + 1;
			break;
		case LEWO:
			noweX = this->x - 1;
			noweY = this->y;
			break;
		case PRAWO:
			noweX = this->x + 1;
			noweY = this->y;
			break;
		}
		try
		{
			swiat->stworzOrganizm(this->gatunek, noweX, noweY);
		}
		catch (int ex)
		{
			if (this->gatunek == MLECZ)
				throw ex; // aby obs�u�y� 3 pr�by rozmna�ania si� mleczy
		}
	}
}

OdbicieAtaku Roslina::obrona(Organizm* atakujacy)
{
	swiat->dopiszDoKonsoli(atakujacy->getNazwa() + " zjada " + this->nazwa + '\n');
	this->Zabij(); // atakuj�cy zjada ro�lin�
	return WYGRANA; // i pozwalamy mu wej�� na swoje miejsce
}