#pragma once
#include "Roslina.h"
class WilczeJagody :
	public Roslina
{

public:
	WilczeJagody(Swiat*, int, int);
	WilczeJagody(Swiat*, int, int, int);
	OdbicieAtaku obrona(Organizm*) override;
};

