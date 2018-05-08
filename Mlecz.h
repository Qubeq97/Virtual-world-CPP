#pragma once
#include "Roslina.h"
class Mlecz :
	public Roslina
{

public:
	Mlecz(Swiat*, int, int);
	Mlecz(Swiat*, int, int, int);
	void akcja() override;
};

