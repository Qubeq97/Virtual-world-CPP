#pragma once
#include <string>
using namespace std;
class Swiat;
enum Gatunek
{
	WILK,
	OWCA,
	LIS,
	ZOLW,
	ANTYLOPA,
	TRAWA,
	MLECZ,
	GUARANA,
	JAGODY,
	BARSZCZ,
	CZLOWIEK,
	CYBEROWCA
};

enum OdbicieAtaku
{
	WYGRANA,
	WYCOFANIE,
	PRZEGRANA,
	WOLNEPOLE // w razie gdy np. antylopa w czasie obrony zwieje przed atakuj¹cym i zwolni mu pole
};

enum Kierunek
{
	GORA,
	DOL,
	LEWO,
	PRAWO
};

class Organizm
{

protected:
	int x, y; // po³o¿enie
	int celX, celY;
	int wiek=0;
	bool zywy = true; // czy zwierzê ¿yje, je¿eli nie, zostanie usuniête
	int inicjatywa, sila;
	Swiat* swiat;
	char znak;
	Gatunek gatunek;
	string nazwa;
	Kierunek kierunek;
public:
	virtual ~Organizm();
	virtual void akcja() = 0;
	virtual OdbicieAtaku obrona(Organizm*)=0;
	int getSila(), getInicjatywa(), getWiek();
	int getX(), getY();
	Gatunek getGatunek();
	string getNazwa();
	bool czyZyje();
	void Zabij();
	void wypiszZnak();
	void postarz();
	void dodajSile(int);
};

