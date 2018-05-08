#pragma once
#include "Organizm.h"
class Swiat;




class Zwierze :
	public Organizm
{
public:
	virtual ~Zwierze();
	virtual void akcja();
	virtual void poruszSie();
	virtual bool kolizja(Organizm*);
	void rozmnozSie(Organizm*);
	OdbicieAtaku obrona(Organizm*);
};

