#include "Swiat.h"
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "Barszcz.h"
#include "Czlowiek.h"
#define DOMYSLNA_SZER 20
#define DOMYSLNA_WYS 20

#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;


Swiat::Swiat()
{
	this->x = DOMYSLNA_SZER;
	this->y = DOMYSLNA_WYS;
	mapaOrganizmow = new Organizm**[DOMYSLNA_WYS];
	for (int i = 0; i < DOMYSLNA_WYS; i++)
		mapaOrganizmow[i] = new Organizm*[DOMYSLNA_SZER];
	for (int i = 0; i < DOMYSLNA_WYS; i++)
		for (int j = 0; j < DOMYSLNA_SZER; j++)
			mapaOrganizmow[i][j] = nullptr; // inicjujemy mapê organizmów pustymi wskaŸnikami
	liczbaZwierzat = 0;
	maxZwierzat = DOMYSLNA_SZER*DOMYSLNA_WYS;
	try
	{
		inicjujOrganizmy();
	}
	catch (int ex)
	{
		throw ex;
	}
}

Swiat::Swiat(int x, int y)
{
	this->x = x;
	this->y = y;
	if (x*y < 22) // bêdzie potrzebne miejsce na przynajmniej 22 organizmy (po 1 z ka¿dego ale czlowiek jeden), tyle jest ich rodzajów (jeszcze bez cyberowcy)
		throw 0;
	mapaOrganizmow = new Organizm**[y];
	for (int i = 0; i < y; i++)
		mapaOrganizmow[i] = new Organizm*[x];
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			mapaOrganizmow[i][j] = nullptr; // inicjujemy mapê organizmów pustymi wskaŸnikami
	liczbaZwierzat = 0;
	maxZwierzat = x*y;
	try
	{
		inicjujOrganizmy();
	}
	catch (int ex)
	{
		throw ex;
	}
}

/*
Konstruktor ³aduj¹cy dane z pliku

FORMAT ZAPISU:
- wymiary œwiata x y
- liczba zwierz¹t na planszy w momencie zapisu
- gatunek x y wiek sila (spec_aktywna tura czy_wolno - tylko dla CZ£OWIEKA)

(brak inicjatywy w zapisie - pozostaje ona sta³a dla danego gatunku)
(sila natomiast zmienia siê, w zale¿noœci od tego czy np. zwierze zjad³o guaranê czy cz³owiek ma spec-skilla)

wyj¹tki:
-1 - b³¹d odczytu
-2 - b³êdne dane
*/
Swiat::Swiat(string plik)
{
	ifstream wejscie(plik);
	if (!wejscie.good())
		throw - 1;
	wejscie >> this->x;
	wejscie >> this->y;
	wejscie >> this->liczbaZwierzat;
	if (wejscie.eof())
		throw - 1;
	if (this->x*this->y < 11 || this->x*this->y < liczbaZwierzat)
		throw - 2;
	mapaOrganizmow = new Organizm**[this->y];
	for (int i = 0; i < this->y; i++)
		mapaOrganizmow[i] = new Organizm*[this->x];
	for (int i = 0; i < this->y; i++)
		for (int j = 0; j < this->x; j++)
			mapaOrganizmow[i][j] = nullptr; // inicjujemy mapê organizmów pustymi wskaŸnikami
	int kontrol = 0;
	while (!wejscie.eof())
	{
		int int_gatunek; // póŸniej siê zrzutuje na enum Gatunek
		wejscie >> int_gatunek;
		if (wejscie.eof())
			break;
		if (int_gatunek > 10) // na razie brak cyberowcy
			throw - 2;
		Gatunek gatunek = (Gatunek)int_gatunek;
		int plikX, plikY, plikWiek, plikSila;
		wejscie >> plikX >> plikY >> plikWiek >> plikSila;
		if (gatunek == CZLOWIEK)
		{
			bool plikWolno, plikAktywna;
			int plikTura;
			wejscie >> plikAktywna >> plikTura >> plikWolno;
			try
			{
				mapaOrganizmow[plikY][plikX] = new Czlowiek(this, plikX, plikY, plikSila, plikAktywna, plikTura, plikWolno);
				czyJestCzlowiek = true;
				organizmy.push_back(mapaOrganizmow[plikY][plikX]);
				kontrol++;
			}
			catch (...)
			{
				throw - 2;
			}
		}
		else
		{
			try
			{
				switch (gatunek)
				{
				case WILK:
					mapaOrganizmow[plikY][plikX] = new Wilk(this, plikX, plikY, plikSila);
					break;
				case OWCA:
					mapaOrganizmow[plikY][plikX] = new Owca(this, plikX, plikY, plikSila);
					break;
				case LIS:
					mapaOrganizmow[plikY][plikX] = new Lis(this, plikX, plikY, plikSila);
					break;
				case ZOLW:
					mapaOrganizmow[plikY][plikX] = new Zolw(this, plikX, plikY, plikSila);
					break;
				case ANTYLOPA:
					mapaOrganizmow[plikY][plikX] = new Antylopa(this, plikX, plikY, plikSila);
					break;
				case TRAWA:
					mapaOrganizmow[plikY][plikX] = new Trawa(this, plikX, plikY, plikSila);
					break;
				case MLECZ:
					mapaOrganizmow[plikY][plikX] = new Mlecz(this, plikX, plikY, plikSila);
					break;
				case GUARANA:
					mapaOrganizmow[plikY][plikX] = new Guarana(this, plikX, plikY, plikSila);
					break;
				case JAGODY:
					mapaOrganizmow[plikY][plikX] = new WilczeJagody(this, plikX, plikY, plikSila);
					break;
				case BARSZCZ:
					mapaOrganizmow[plikY][plikX] = new Barszcz(this, plikX, plikY, plikSila);
					break;
				default:
					throw - 2;
					break;
				}
				organizmy.push_back(mapaOrganizmow[plikY][plikX]);
				kontrol++;
			}
			catch (...)
			{
				throw - 2;
			}
		}
	}
	wejscie.close();
	if (kontrol != liczbaZwierzat)
		throw - 2;
}


Swiat::~Swiat()
{
	for (int i = 0; i < this->y; i++)
		mapaOrganizmow[i] = nullptr;
	mapaOrganizmow = nullptr;
	for (Organizm* i : organizmy)
		if (i != nullptr)
			delete i;
	organizmy.clear();
	for (Organizm* i : doDodania)
		if (i != nullptr)
			delete i;
	doDodania.clear();
}


void Swiat::wykonajTure()
{
	skasujKonsole();
	sortujOrganizmy();
	for (Organizm* org : organizmy)
	{
		if (org->czyZyje())
		{
			org->akcja();
			org->postarz();
		}
	}
	dodajDoWektora();
	sprzatnijTrupy();
	pokazSwiat();
	pokazKonsole();
}

/*
w pierwszej kolejnoœci sprawdza inicjatywê i je¿eli siê ró¿ni, sortuje wg niej
je¿eli jest ta sama dla danych organizmów, sortuje je po wieku
*/
void Swiat::sortujOrganizmy()
{
	bool zmiana = false;
	for (int i = 0; i < organizmy.size(); i++)
	{
		zmiana = false;
		for (int j = 0; j < organizmy.size() - 1; j++)
		{
			if ((organizmy[j])->getInicjatywa() < (organizmy[j + 1])->getInicjatywa()) // sort po inicjatywie
			{
				swap(organizmy[j], organizmy[j + 1]);
				zmiana = true;
			}
			else if ((organizmy[j])->getInicjatywa() == (organizmy[j + 1])->getInicjatywa()) // je¿eli inicjatywa ta sama...
			{
				if ((organizmy[j])->getWiek() < (organizmy[j + 1])->getWiek()) // ... to sortuj po wieku
				{
					swap(organizmy[j], organizmy[j + 1]);
					zmiana = true;
				}
			}
		}
		if (!zmiana)
			break;
	}
}

// umieszcza trupy na koñcu wektora i je usuwa z niego
void Swiat::sprzatnijTrupy()
{
	int rozmiar = organizmy.size();
	for (int i = 0; i < rozmiar; i++)
	{
		if (!(organizmy[i]->czyZyje()))
		{
			if (organizmy[i]->getGatunek() == CZLOWIEK)
				czyJestCzlowiek = false;
			swap(organizmy[i], organizmy[rozmiar - 1]);
		}
	}
	while (licznikTrupow > 0)
	{
		delete organizmy[organizmy.size() - 1];
		organizmy[organizmy.size() - 1] = nullptr;
		organizmy.pop_back();
		licznikTrupow--;
	}
}

int Swiat::getX()
{
	return x;
}

int Swiat::getY()
{
	return y;
}

// po polsku:
// SprawdŸ, czy organizm ruszaj¹cy siê nie skoliduje z innym
// po wejœciu na pole (x,y)
// po technicznemu:
// nullptr - tam nic nie ma lub jest tam trup
Organizm* Swiat::sprawdzKolizje(int x, int y)
{
	return mapaOrganizmow[y][x];
	
}

// Wywo³ywana w celu aktualizacji mapy organizmów (i ich tablicy znaków, je¿eli nie bêdzie conio.h)
// nullptr zamiast delete, poniewa¿ wskaŸnik dalej siedzi w wektorze
// i potem odwo³anie z wektora do pustego obszaru wysypa³oby program
void Swiat::aktualizujPozycje(Organizm* org, int celX, int celY)
{
	// te linie maj¹ sens, bo wewnêtrzne zmienne pozycji zmieni¹ siê potem
	int stareX = org->getX();
	int stareY = org->getY();
	mapaOrganizmow[celY][celX] = org;
	mapaOrganizmow[stareY][stareX] = nullptr;
}

void Swiat::stworzOrganizm(Gatunek gat, int x, int y)
{
	if (x < 0 || x >= this->x || y < 0 || y >= this->y) // próba stworzenia poza map¹
		throw 3;
	Organizm* check = sprawdzKolizje(x, y);
	if (check != nullptr) // tam jest organizm
		throw 1;
	else if (!czyJestMiejsce()) // mapa jest pe³na
		throw 2;
	switch (gat)
	{
	case WILK:
		mapaOrganizmow[y][x] = new Wilk(this, x, y);
		break;
	case OWCA:
		mapaOrganizmow[y][x] = new Owca(this, x, y);
		break;
	case LIS:
		mapaOrganizmow[y][x] = new Lis(this, x, y);
		break;
	case ZOLW:
		mapaOrganizmow[y][x] = new Zolw(this, x, y);
		break;
	case ANTYLOPA:
		mapaOrganizmow[y][x] = new Antylopa(this, x, y);
		break;
	case TRAWA:
		mapaOrganizmow[y][x] = new Trawa(this, x, y);
		break;
	case MLECZ:
		mapaOrganizmow[y][x] = new Mlecz(this, x, y);
		break;
	case GUARANA:
		mapaOrganizmow[y][x] = new Guarana(this, x, y);
		break;
	case JAGODY:
		mapaOrganizmow[y][x] = new WilczeJagody(this, x, y);
		break;
	case BARSZCZ:
		mapaOrganizmow[y][x] = new Barszcz(this, x, y);
		break;
	case CZLOWIEK:
		if (!czyJestCzlowiek)
		{
			mapaOrganizmow[y][x] = new Czlowiek(this, x, y);
			czyJestCzlowiek = true;
		}
		else
			return;
		break;
	}
	doDodania.push_back(mapaOrganizmow[y][x]);
	liczbaZwierzat++;
	dopiszDoKonsoli("Nowy organizm: " + mapaOrganizmow[y][x]->getNazwa() + ", " + to_string(mapaOrganizmow[y][x]->getX()) + ", " + to_string(mapaOrganizmow[y][x]->getY()) + "\n");
}


// usuwa konkretnego trupa z mapy tu¿ po zgonie, aby nie przeszkadza³ w umieszczaniu na mapie nowych
// w wektorze dalej bêdzie on obecny z uwagi na to, ¿e ci¹gle siê po wektorze iteruje
// i te¿ przez to nie u¿ywam delete, tylko ustawiam wskaŸnik w mapie na nullptr
void Swiat::usunZwierzeZMapy(int x, int y)
{
	mapaOrganizmow[y][x] = nullptr;
	liczbaZwierzat--;
	licznikTrupow++;
}

bool Swiat::czyJestMiejsce()
{
	if (liczbaZwierzat == maxZwierzat)
		return false;
	else
		return true;
}

void Swiat::dodajDoWektora()
{
	while (!doDodania.empty())
	{
		organizmy.push_back(doDodania.back());
		doDodania.pop_back();
	}
}

void Swiat::ustawKursor(int x, int y)
{
	COORD wspolrzedne = { x,y };
	HANDLE wyjscie = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(wyjscie, wspolrzedne);
}

void Swiat::pokazGranice()
{
	for (int i = 0; i < (x + 2); i++)
	{
		for (int j = 0; j < (y + 2); j++)
		{
			ustawKursor(i, j);
			if (i == 0 || i == x + 1 || j == 0 || j == y + 1)
			{
				cout << '*';
			}
		}
	}
}

bool Swiat::czyZwierze(Gatunek gat)
{
	switch (gat)
	{
	case ANTYLOPA:
	case LIS:
	case OWCA:
	case WILK:
	case ZOLW:
	case CZLOWIEK:
		return true;
		break;
	default:
		return false;
	}
}

bool Swiat::czyRoslina(Gatunek gat)
{
	switch (gat)
	{
	case BARSZCZ:
	case GUARANA:
	case MLECZ:
	case TRAWA:
	case JAGODY:
		return true;
	default:
		return false;
	}
}


void Swiat::pokazSwiat()
{
	system("cls");
	pokazGranice();
	for (Organizm* org : organizmy)
	{
		if (org->czyZyje())
		{
			ustawKursor(org->getX() + 1, org->getY() + 1);
			org->wypiszZnak();
		}
	}
}

void Swiat::dopiszDoKonsoli(string napis)
{
	konsola += napis;
}

void Swiat::pokazKonsole()
{
	ustawKursor(0, this->y + 2);
	cout << konsola << endl;
}

void Swiat::skasujKonsole()
{
	konsola = "";
}

/*
FORMAT ZAPISU:
	- wymiary œwiata x y
	- liczba zwierz¹t na planszy w momencie zapisu
	- gatunek x y wiek sila (spec_aktywna tura czy_wolno - tylko dla CZ£OWIEKA)

	(brak inicjatywy w zapisie - pozostaje ona sta³a dla danego gatunku)
	(sila natomiast zmienia siê, w zale¿noœci od tego czy np. zwierze zjad³o guaranê czy cz³owiek ma spec-skilla)
*/
void Swiat::zapiszDoPliku(string plik)
{
	ofstream wyjscie(plik);
	if (!wyjscie.good())
		throw 1;
	wyjscie << x << ' ' << y << endl;
	wyjscie << liczbaZwierzat << endl;
	for (Organizm* org : organizmy)
	{
		if (org != nullptr && org->czyZyje())
		{
			wyjscie << org->getGatunek() << ' ';
			wyjscie << org->getX() << ' ' << org->getY() << ' ';
			wyjscie << org->getWiek() << ' ' << org->getSila();
			if (org->getGatunek() == CZLOWIEK)
			{
				Czlowiek* ptr = dynamic_cast<Czlowiek*>(org);
				wyjscie << ' ' << ptr->czyAktywna() << ' ';
				wyjscie << ptr->getTura() << ' ';
				wyjscie << ptr->czyWolno();
				ptr = nullptr;
			}
		}
		wyjscie << endl;
	}
	wyjscie.close();
}



// losowo dodaje organizmy do œwiata na starcie
// ta funkcja NIE DOTYCZY wczytywania stanu z pliku
void Swiat::inicjujOrganizmy()
{
	int noweX, noweY;
	for (int i = 0; i < 22; i++) // jest 11 gatunków, po 2 na gatunek, oprócz cz³owieka
	{
		do
		{
			noweX = rand() % this->x;
			noweY = rand() % this->y;
		} while (sprawdzKolizje(noweX, noweY) != nullptr);
		try
		{
			stworzOrganizm((Gatunek)(i % 11), noweX, noweY);
		}
		catch (int ex)
		{
			throw ex;
		}
	}
	dodajDoWektora();
	sortujOrganizmy();
	skasujKonsole();
}