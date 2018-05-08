#include "Barszcz.h"
#include "Swiat.h"



Barszcz::Barszcz(Swiat* swiat1, int x1, int y1)
{
	this->gatunek = BARSZCZ;
	this->znak = 'B';
	this->sila = 10;
	this->nazwa = "Barszcz Sosnowskiego";
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}

Barszcz::Barszcz(Swiat* swiat1, int x1, int y1, int sila)
{
	this->gatunek = BARSZCZ;
	this->znak = 'B';
	this->sila = sila;
	this->nazwa = "Barszcz Sosnowskiego";
	this->x = x1;
	this->y = y1;
	this->swiat = swiat1;
}



OdbicieAtaku Barszcz::obrona(Organizm* atakujacy)
{
	this->Zabij(); // bo zje barszcz
	if (atakujacy->getGatunek() == CYBEROWCA) // cyberowca na póŸniej
	{
		swiat->dopiszDoKonsoli(atakujacy->getNazwa() + " zjada " + this->nazwa + '\n');
		return WYGRANA; // cyberowca jest odporna
	}
	else
	{
		swiat->dopiszDoKonsoli(atakujacy->getNazwa() + " zjada " + this->nazwa + " i przegrywa\n");
		return PRZEGRANA; // a inne nie
	}
}

void Barszcz::akcja()
{
	if (this->y - 1 >= 0) // od góry
	{
		Organizm* test = swiat->sprawdzKolizje(this->x, this->y - 1);
		if (test != nullptr && swiat->czyZwierze(test->getGatunek()) && test->getGatunek() != CYBEROWCA)
		{
			swiat->dopiszDoKonsoli(this->nazwa + " zabija " + test->getNazwa() + '\n');
			test->Zabij();
		}
	}
	if (this->y + 1 < swiat->getY()) // od do³u
	{
		Organizm* test = swiat->sprawdzKolizje(this->x, this->y + 1);
		if (test != nullptr && swiat->czyZwierze(test->getGatunek()) && test->getGatunek() != CYBEROWCA)
		{
			swiat->dopiszDoKonsoli(this->nazwa + " zabija " + test->getNazwa() + '\n');
			test->Zabij();
		}
	}
	if (this->x - 1 >= 0) // z lewej
	{
		Organizm* test = swiat->sprawdzKolizje(this->x - 1, this->y);
		if (test != nullptr && swiat->czyZwierze(test->getGatunek()) && test->getGatunek() != CYBEROWCA)
		{
			swiat->dopiszDoKonsoli(this->nazwa + " zabija " + test->getNazwa() + '\n');
			test->Zabij();
		}
	}
	if (this->x + 1 < swiat->getX()) // z prawej
	{
		Organizm* test = swiat->sprawdzKolizje(this->x + 1, this->y);
		if (test != nullptr && swiat->czyZwierze(test->getGatunek()) && test->getGatunek() != CYBEROWCA)
		{
			swiat->dopiszDoKonsoli(this->nazwa + " zabija " + test->getNazwa() + '\n');
			test->Zabij();
		}
	}
	// po sprz¹tniêciu wszystkich s¹siednich zwierz¹t barszcz normalnie siê rozmno¿y
	Roslina::akcja();
}


