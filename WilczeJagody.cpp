#include "WilczeJagody.h"
#include "Swiat.h"



WilczeJagody::WilczeJagody(Swiat* swiat1, int x1, int y1)
{
	this->gatunek = JAGODY;
	this->nazwa = "Wilcze Jagody";
	this->znak = 'J';
	this->sila = 99;
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}

WilczeJagody::WilczeJagody(Swiat* swiat1, int x1, int y1, int sila)
{
	this->gatunek = JAGODY;
	this->nazwa = "Wilcze Jagody";
	this->znak = 'J';
	this->sila = sila;
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}


OdbicieAtaku WilczeJagody::obrona(Organizm * atakujacy)
{
	swiat->dopiszDoKonsoli(atakujacy->getNazwa() + " zjada " + this->nazwa + " i przegrywa\n");
	this->Zabij(); // bo atakuj¹cy zje jagody
	return PRZEGRANA; // a przy okazji jagody teleportuj¹ ka¿dego atakuj¹cego prosto w tamten œwiat (R.I.P.)
}


