#pragma once
#include "Organizm.h"

class Swiat;

class Roslina :
	public Organizm
{
public:
	Roslina();
	virtual ~Roslina();
	virtual void akcja();
	virtual OdbicieAtaku obrona(Organizm*);
};

