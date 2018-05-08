#include "Mlecz.h"
#include "Swiat.h"



Mlecz::Mlecz(Swiat* swiat1, int x1, int y1)
{
	this->gatunek = MLECZ;
	this->znak = 'M';
	this->nazwa = "Mlecz";
	this->sila = 0;
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}

Mlecz::Mlecz(Swiat* swiat1, int x1, int y1, int sila)
{
	this->gatunek = MLECZ;
	this->znak = 'M';
	this->nazwa = "Mlecz";
	this->sila = sila;
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}

void Mlecz::akcja()
{
	for (int i = 0; i < 3; i++)
	{
		try
		{
			this->Roslina::akcja(); // podejmuje 3 pr�by zwyk�ego rozmno�enia si�
			break; // i jak si� uda, to ju� nie podejmie pr�b
		}
		catch (int)
		{
			;
		}
	}
}
