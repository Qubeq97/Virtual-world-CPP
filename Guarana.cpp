#include "Guarana.h"
#include "Swiat.h"



Guarana::Guarana(Swiat* swiat1, int x1, int y1)
{
	this->gatunek = GUARANA;
	this->nazwa = "Guarana";
	this->znak = 'G';
	this->sila = 0;
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}

Guarana::Guarana(Swiat* swiat1, int x1, int y1, int sila)
{
	this->gatunek = GUARANA;
	this->nazwa = "Guarana";
	this->znak = 'G';
	this->sila = sila;
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}


OdbicieAtaku Guarana::obrona(Organizm* atakujacy)
{
	swiat->dopiszDoKonsoli(atakujacy->getNazwa() + " zjada " + this->nazwa + " i dostaje +3 do sily\n");
	this->Zabij();
	atakujacy->dodajSile(3); // organizm który zje guaranê dostaje +3 do si³y
	return WYGRANA;
}
