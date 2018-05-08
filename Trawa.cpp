#include "Trawa.h"



Trawa::Trawa(Swiat* swiat1, int x1, int y1)
{
	this->gatunek = TRAWA;
	this->nazwa = "Trawa";
	this->sila = 0;
	this->znak = 'T';
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}

Trawa::Trawa(Swiat* swiat1, int x1, int y1, int sila)
{
	this->gatunek = TRAWA;
	this->nazwa = "Trawa";
	this->sila = sila;
	this->znak = 'T';
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}

