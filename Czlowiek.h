#pragma once
#include "Zwierze.h"
class Swiat;
class Czlowiek :
	public Zwierze
{
private:
	bool spec_aktywna = false;
	int tura = 0;
	bool czy_wolno = true;
public:
	Czlowiek(Swiat*, int, int);
	Czlowiek(Swiat*, int, int, int, bool, int, bool);
	void akcja() override;
	void aktywujEliksir(); // aktywuje eliksir
	bool czyAktywna();
	int getTura();
	bool czyWolno();
};

