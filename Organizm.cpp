#include "Organizm.h"
#include "Swiat.h"
#include <iostream>

Organizm::~Organizm()
{
	this->swiat = nullptr;
}

int Organizm::getInicjatywa()
{
	return this->inicjatywa;
}


int Organizm::getSila()
{
	return this->sila;
}

int Organizm::getWiek()
{
	return this->wiek;
}

int Organizm::getX()
{
	return this->x;
}

int Organizm::getY()
{
	return this->y;
}

Gatunek Organizm::getGatunek()
{
	return gatunek;
}

bool Organizm::czyZyje()
{
	return this->zywy;
}

string Organizm::getNazwa()
{
	return this->nazwa;
}

void Organizm::Zabij()
{
	this->zywy = false;
	swiat->usunZwierzeZMapy(this->x, this->y);
}



void Organizm::wypiszZnak()
{
	std::cout << znak;
}

void Organizm::postarz()
{
	this->wiek++;
}

void Organizm::dodajSile(int ile)
{
	this->sila += ile;
}
