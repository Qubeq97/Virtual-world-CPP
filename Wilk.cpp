#include "Wilk.h"



Wilk::Wilk(Swiat* swiat1,int x1,int y1)
{
	this->gatunek = WILK;
	this->sila = 9;
	this->inicjatywa = 5;
	this->znak = 'W';
	this->x = x1;
	this->y = y1;
	this->nazwa = "Wilk";
	this->swiat = swiat1;
}

Wilk::Wilk(Swiat* swiat1, int x1, int y1, int sila)
{
	this->gatunek = WILK;
	this->sila = sila;
	this->inicjatywa = 5;
	this->znak = 'W';
	this->x = x1;
	this->y = y1;
	this->nazwa = "Wilk";
	this->swiat = swiat1;
}

