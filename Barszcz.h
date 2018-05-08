#pragma once
#include "Roslina.h"
class Barszcz :
	public Roslina
{

public:
	Barszcz(Swiat*, int, int);
	Barszcz(Swiat*, int, int, int);
	OdbicieAtaku obrona(Organizm*) override;
	void akcja() override;
};

