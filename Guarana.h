#pragma once
#include "Roslina.h"
class Guarana :
	public Roslina
{

public:
	Guarana(Swiat*, int, int);
	Guarana(Swiat*, int, int, int);
	OdbicieAtaku obrona(Organizm*) override;
};

