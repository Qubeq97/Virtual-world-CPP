#pragma once

#include <vector>
#include <string>
using namespace std;

class Organizm;
enum Gatunek;
enum Kierunek;

class Swiat
{
private:
	int x, y; // wymiary œwiata
	vector <Organizm*> organizmy; // przechowuje organizmy
	vector <Organizm*> doDodania; // przechowuje te do dodania do g³ównego wektora, konieczne by³o rozdzielenie, bo jeszcze trwa iteracja po g³ównym
	Organizm*** mapaOrganizmow; // mapa wskaŸników na organizmy (INDEKSY OD 0)
	int liczbaZwierzat, maxZwierzat;
	string konsola = "";
	bool czyJestCzlowiek = false;
	int licznikTrupow = 0;
public:
	Swiat();
	Swiat(int, int);
	Swiat(string);
	~Swiat();
	void stworzOrganizm(Gatunek, int, int);
	void wykonajTure();
	void ustawKursor(int, int);
	void pokazSwiat();
	void sortujOrganizmy();
	void sprzatnijTrupy(); // kasuje martwe organizmy
	Organizm* sprawdzKolizje(int, int);
	int getX(), getY();
	void aktualizujPozycje(Organizm*, int, int);
	bool czyJestMiejsce();
	void dodajDoWektora();
	void usunZwierzeZMapy(int, int);
	void pokazGranice();
	bool czyZwierze(Gatunek);
	bool czyRoslina(Gatunek);
	void dopiszDoKonsoli(string);
	void pokazKonsole();
	void skasujKonsole();
	void zapiszDoPliku(string);
	void inicjujOrganizmy();
};

