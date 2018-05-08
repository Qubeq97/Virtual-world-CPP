#include "Zolw.h"
#include "Swiat.h"


Zolw::Zolw(Swiat* swiat1, int x1, int y1)
{
	this->gatunek = ZOLW;
	this->znak = 'Z';
	this->nazwa = "Zolw";
	this->sila = 2;
	this->inicjatywa = 1;
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}

Zolw::Zolw(Swiat* swiat1, int x1, int y1, int sila)
{
	this->gatunek = ZOLW;
	this->znak = 'Z';
	this->nazwa = "Zolw";
	this->sila = sila;
	this->inicjatywa = 1;
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}


void Zolw::poruszSie()
{
	int los = rand() % 4;
	if (los == 0)  // albowiem w 75% przypadków ¿ó³w siê w ogóle nie poruszy
	{
		Zwierze::poruszSie();
	}
}

OdbicieAtaku Zolw::obrona(Organizm * atakujacy)
{
	if (atakujacy->getSila() < 5) // albowiem ¿ó³w odpiera ataki organizmów o sile <5, wtedy przeciwnik zostaje na swym polu
	{
		swiat->dopiszDoKonsoli(this->nazwa + " odpiera atak " + atakujacy->getNazwa() + '\n');
		return WYCOFANIE;
	}
	else
		return Zwierze::obrona(atakujacy); // w przeciwnym razie wykona siê standardowa metoda obrony
}

