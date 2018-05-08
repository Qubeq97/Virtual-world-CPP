#include "Owca.h"



Owca::Owca(Swiat* swiat1, int x1, int y1)
{
	this->gatunek = OWCA;
	this->sila = 4;
	this->inicjatywa = 4;
	this->znak = 'O';
	this->x = x1;
	this->y = y1;
	this->nazwa = "Owca";
	this->swiat = swiat1;

}

Owca::Owca(Swiat* swiat1, int x1, int y1, int sila)
{
	this->gatunek = OWCA;
	this->sila = sila;
	this->inicjatywa = 4;
	this->znak = 'O';
	this->x = x1;
	this->y = y1;
	this->nazwa = "Owca";
	this->swiat = swiat1;

}

