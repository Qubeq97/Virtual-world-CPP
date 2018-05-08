#pragma once
#include "Zwierze.h"
class Lis :
	public Zwierze
{


public:

	Lis(Swiat*, int, int);
	Lis(Swiat*, int, int, int);
	void poruszSie() override;
};

