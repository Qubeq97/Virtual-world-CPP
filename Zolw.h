#pragma once
#include "Zwierze.h"
class Zolw :
	public Zwierze
{

public:
	Zolw(Swiat*, int, int);
	Zolw(Swiat*, int, int, int);
	void poruszSie() override;
	OdbicieAtaku obrona(Organizm*) override;
};

