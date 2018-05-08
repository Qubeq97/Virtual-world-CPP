#pragma once
#include "Zwierze.h"
class Antylopa :
	public Zwierze
{


public:

	Antylopa(Swiat*, int, int);
	Antylopa(Swiat*, int, int, int);
	void poruszSie() override;
	bool kolizja(Organizm*) override;
	OdbicieAtaku obrona(Organizm*) override;
};

