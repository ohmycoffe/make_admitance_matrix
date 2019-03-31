#include <iostream>
#include <stdlib.h>
#include <fstream> //biblioteka do operacji na plikach
#include <cstdlib>
#include <string> //biblioteka dodaj¹ca operacje na "stringach"
#include <conio.h>
#include <complex>//biblioteka dodaj¹ca operacje na liczbach zespolonych
#include <math.h>  // biblioteka dodaj¹ca operacje matematyczne takie jak "pierwiastek", czy potêga

using namespace std;
typedef complex<double> liczba_zesp; //

typedef int(*wsk_proba)(int);


/*KLASA MACIERZ*/
class klasa_macierz
{
public:
	liczba_zesp **macierz; // deklaracja tablicy dwuwymiarowej (bo 2x*) która bêdzie przechowywyac mac. admitancyjn¹
	float rozmiarM; //rozmiar tej macierzy


public:
	klasa_macierz(int n);
	~klasa_macierz();

	void zapis_plik_macierz(int jaki_rozmiar);
	void odczyt_plik_macierz(int jaki_rozmiar);

};


/*Alokacja (rezerwowanie) pamiêci na nasz¹ macierz admitancyjn¹.
Jest ona wykonywana za ka¿dym razem, gdy tworzony jest obiekt tej klasy*/


klasa_macierz::klasa_macierz(int n) //
{
	macierz = new liczba_zesp*[n];
	int i;
	for (i = 0; i<n; i++)
	{
		macierz[i] = new liczba_zesp[n];
	}
}

//destruktor - zwalnia pamiêæ
klasa_macierz::~klasa_macierz()
{
	int i;
	for (i = 0; i<rozmiarM; i++)
	{
		delete[] macierz[i];
	}
	delete[] macierz;
}

//odczytanie z pliku "Macierz" macierzy admitancyjnej i wrzucenie jej do utworzonej tablicy "macierz" w programie
void klasa_macierz::odczyt_plik_macierz(int jaki_rozmiar)
{
	ifstream plik_we;
	plik_we.open("Macierz.txt");

	if (plik_we.is_open())
	{
		cout << "\nMacierz admitancyjna Y:\n\n";
		for (int w = 0; w < jaki_rozmiar; w++)
		{
			for (int k = 0; k < jaki_rozmiar; k++)
			{
				plik_we >> macierz[w][k];
				cout << " |" << real(macierz[w][k]) << " + " << imag(macierz[w][k]) << "j" << "|";
			}
			cout << "\n\n";
		}
	}
	else
	{
		cout << "\nNie mozna wczytac pliku!";
		system("Pause");
	}
	plik_we.close();
}

// zapis tablicy macierz do pliku o nazwie "Macierz.txt"


void klasa_macierz::zapis_plik_macierz(int jaki_rozmiar)
{
	ofstream plik_wy;
	plik_wy.open("Macierz.txt");
	for (int w = 0; w < jaki_rozmiar; w++)
	{
		for (int k = 0; k< jaki_rozmiar; k++)
		{
			plik_wy << macierz[w][k] << " ";
		}
		plik_wy << endl;
	}
	plik_wy << endl;
	plik_wy.close();

}
/*KONIEC KLASA MACIERZ*/

/*Struktura LINIA*/

struct struktura_linia
{
	int from, to;
	float length;
	float r, x, b; //jednostkowe
	string opis;
};

/*Struktura WEZLY*/
struct struktura_bus
{
	int bus;
	float v_nom;
	string opis;
};

//zapis do pliku danych ze struktury (br)
void zapis_plik_dane(struktura_linia *k, int ile_elementow)
{

	ofstream plik_wy;
	plik_wy.open("Dane.txt");
	for (int i = 0; i < ile_elementow; i++)
	{
		if (i != 0) plik_wy << '\n';
		plik_wy << k[i].from << '\t' << k[i].to << '\t' << k[i].r << '\t' << k[i].x << '\t' << k[i].b << '\t' << k[i].length << '\t' << k[i].opis; // \t to jest tabulacja
	}
	plik_wy << endl;
	plik_wy.close();
}
//zapis do pliku danych ze struktury (bus)
void zapis_plik_wezly(struktura_bus *k, int ile_elementow)
{

	ofstream plik_wy;
	plik_wy.open("Wezly.txt");
	for (int i = 0; i < ile_elementow; i++)
	{
		if (i != 0) plik_wy << '\n'; // gdyby tego nie bylo to by pierwsza linia by³a pusta
		plik_wy << k[i].bus << '\t' << k[i].v_nom << '\t' << k[i].opis;
	}
	plik_wy << endl;
	plik_wy.close();
}

//dodajemy now¹ liniê - rozszerzamy rozmiar struktury br
void dodaj_linie(struktura_linia *&k, int ile)
{
	struktura_linia * br2 = new struktura_linia[ile + 1]; //struktura tymczasowa o rozmiarze wiekszym o 1
	for (int i = 0; i < ile; i++) br2[i] = k[i]; //przepisanie elementow do tymczasowej struktury ze starej
	delete[] k; // zwolnienie pamieci struktury starej
	k = br2; //przypisanie calego bloku pamieci struktury tymczasowej do struktury ozn. jako k (u nas to br)
	cout << "\nDodaj linie\n";
	cout << "Podadj from: ";
	cin >> k[ile].from; //bo numeracja od 0
	cout << "Podadj to: ";
	cin >> k[ile].to;
	cout << "Podadj r [ohm/km] = ";
	cin >> k[ile].r;
	cout << "Podadj x [ohm/km] = ";
	cin >> k[ile].x;
	cout << "Podadj b [uS/km] = ";
	cin >> k[ile].b;
	cout << "Podadj dlugosc [km] = ";
	cin >> k[ile].length;
	cout << "Podadj opis ";
	cin >> k[ile].opis;

	cout << "\nDodano linie o parametrach: ";
	cout << "\nFrom = " << k[ile].from;
	cout << "\nTo = " << k[ile].to;
	cout << "\nr = " << k[ile].r << " [ohm/km]";
	cout << "\nx = " << k[ile].x << " [ohm/km]";
	cout << "\nb = " << k[ile].b << " [uS/km]";
	cout << "\ndDugosc = " << k[ile].length << " [km]";
	cout << "\nOpis: " << k[ile].opis;
}

//usuwa linie
void usun_linie(struktura_linia *k, int ile)
{
	cout << "\nPodaj nr linii do usuniecia: ";
	int del;
	cin >> del;
	for (int i = del; i < ile - 1; i++)
	{
		k[i] = k[i + 1];
		/*k[i].from = k[i + 1].from;
		k[i].to = k[i + 1].to;
		k[i].r = k[i + 1].r;
		k[i].x = k[i + 1].x;
		k[i].b = k[i + 1].b;
		k[i].length = k[i + 1].length;
		k[i].opis = k[i + 1].opis;
		*/
	}
}

// dodaje wezel analogicznie jak dodaj_linie
void dodaj_wezel(struktura_bus *&k, int ile)
{
	struktura_bus * b2 = new struktura_bus[ile + 1];
	for (int i = 0; i < ile; i++) b2[i] = k[i];
	delete[] k;
	k = b2;
	cout << "\nDodaj wezel\n";
	cout << "Podadj id wezla: ";
	cin >> k[ile].bus;
	cout << "Podadj v_nom [kv] = ";
	cin >> k[ile].v_nom;
	cout << "Podadj opis: ";
	cin >> k[ile].opis;

	cout << "\nDodano wezel o parametrach: ";
	cout << "\nBus: " << k[ile].bus;
	cout << "\nV_nom [kv] = " << k[ile].v_nom;
	cout << "\nOpis: " << k[ile].opis;

}


int ktory_wezel(klasa_macierz &obiekt, int ileM, int &f)
{
	f = 0;
	int zwroc = 0;
	for (int i = 0; i < ileM; i++)
	{
		if (obiekt.macierz[i][i] == liczba_zesp(0, 0))
		{
			zwroc = i;
			f = 1;
		}

	}
	return zwroc;
}

void usun_wezel(klasa_macierz &obiekt, int ileM, struktura_bus *k, int ileW)
{

	for (int del = 0; del < ileM; del++)
	{
		if (obiekt.macierz[del][del] == liczba_zesp(0, 0))
		{
			for (int i = del; i < ileW - 1; i++)
				k[i] = k[i + 1];
		}

	}

}


int usun_wezly(klasa_macierz &obiekt, int ileM, struktura_bus *k, int ileW, int &wywal)
{
	int zwroc = 0;
	for (int del = 0; del < ileM; del++)
	{
		int flaga = 0;
		if (obiekt.macierz[del][del]  == liczba_zesp(0, 0))
		{
			wywal = del;
			flaga = 1;
			zwroc = 1;
			for (int i = del; i < ileW - 1; i++)
				k[i] = k[i + 1];

		}
		if (flaga == 1)
		{
			ofstream plik_wy;
			plik_wy.open("Wezly.txt");
			for (int i = 0; i < ileW - flaga; i++)
			{
				if (i != 0) plik_wy << '\n';
				plik_wy << k[i].bus << '\t' << k[i].v_nom << '\t' << k[i].opis;
			}
			plik_wy << endl;
			plik_wy.close();
		}
	}
	return zwroc;
}


void modyfikacja_linii(struktura_linia *k) //k to br nasze
{
	int i;
	cout << "\nPodaj nr linii do modyfikacji (od zera): ";
	cin >> i;

	cout << "Podadj from: ";
	cin >> k[i].from;
	cout << "Podadj to: ";
	cin >> k[i].to;
	cout << "Podadj r [ohm/km] = ";
	cin >> k[i].r;
	cout << "Podadj x [ohm/km] = ";
	cin >> k[i].x;
	cout << "Podadj b [uS/km] = ";
	cin >> k[i].b;
	cout << "Podadj dlugosc [km] = ";
	cin >> k[i].length;
	cout << "Podadj opis: ";
	cin >> k[i].opis;
}


void modyfikacja_wezla(struktura_bus *k)
{
	int i;
	cout << "\nPodaj indeks od zera: ";
	cin >> i;

	cout << "Podadj wezel: ";
	cin >> k[i].bus;
	cout << "Podadj v_nom [kV] =";
	cin >> k[i].v_nom;
	cout << "Podadj opis: ";
	cin >> k[i].opis;
}

void wyswietlenie_linia(struktura_linia *k, int ile)
{
	int i;
	for (i = 0; i<ile; i++)
	{
		cout << "\nLinia nr " << i << ":";
		cout << "\nFrom = " << k[i].from;
		cout << "\nTo = " << k[i].to;
		cout << "\nr = " << k[i].r;
		cout << "\nx = " << k[i].x;
		cout << "\nb [uS] = " << k[i].b;
		cout << "\ndlugosc = " << k[i].length;
		cout << "\nOpis: " << k[i].opis;
		cout << endl;
	}
	cout << endl;
}

void wyswietlenie_wezel(struktura_bus *k, int ile)
{
	int i;
	for (i = 0; i<ile; i++)
	{
		cout << "\nWezel nr " << i << ":";
		cout << "\nBus: " << k[i].bus;
		cout << "\nV_nom = " << k[i].v_nom;
		cout << "\nOpis: " << k[i].opis;
		cout << endl;

	}
	cout << endl;
}

int odczyt_plik_dane(struktura_linia *k, int ile_linii)
{
	ifstream plik_we;
	plik_we.open("Dane.txt");
	int i = 0;


	if (plik_we.is_open())
	{
		for (int i = 0; i < ile_linii; i++)
		{
			plik_we >> k[i].from;
			plik_we >> k[i].to;
			plik_we >> k[i].r;
			plik_we >> k[i].x;
			plik_we >> k[i].b;
			plik_we >> k[i].length;
			plik_we >> k[i].opis;
			//cout << k[i].from << " " << k[i].to << " " << k[i].r << " " << k[i].x << " " << k[i].opis << endl;
		}
	}
	else
	{
		cout << "\nNie mozna wczytac pliku 'Dane.txt'!";
	}

	plik_we.close();
	return i;
}

int odczyt_plik_wezly(struktura_bus *k, int ile_wezlow)
{
	ifstream plik_we;
	plik_we.open("Wezly.txt");
	int i = 0;


	if (plik_we.is_open())
	{
		for (int i = 0; i < ile_wezlow; i++)
		{
			plik_we >> k[i].bus;
			plik_we >> k[i].v_nom;
			plik_we >> k[i].opis;
			//cout << k[i].bus << " " << k[i].v_nom << " " << k[i].opis << endl;
		}
	}
	else
		cout << "\nNie mozna wczytac pliku 'Wezly.txt'!";
	plik_we.close();
	return i;
}

/*FUNKCJE ZEWNETRZNE*/

void normalizacja(struktura_linia *k, int ileL, struktura_bus *b, int ileW, int nr)
{
	cout << "NUMER " << nr;
	for (int i = 0; i < ileL; i++)
	{
		if (k[i].from > nr) k[i].from = k[i].from - 1;
		if (k[i].to > nr) k[i].to = k[i].to - 1;

	}
	for (int i = 0; i < ileL; i++)
	{
		if (b[i].bus > nr) b[i].bus = b[i].bus - 1;
	}
}

//zlicza liczbe wierzy w pliku z liniami ("Dane")
int licz_linie()
{
	int liczba_linii = 0; //zeruje licznik
	string line;
	ifstream plik_we;
	plik_we.open("Dane.txt");
	if (plik_we.is_open())
	{
		while (getline(plik_we, line))
			++liczba_linii;
		cout << "Liczba linii wynosi:" << liczba_linii;
	}
	else cout << "\nNie mozna wczytac pliku 'Dane.txt' w celu zliczenia linii!";


	return liczba_linii;
}


int licz_wezly()
{
	int liczba_wezlow = 0;
	string line;
	ifstream plik_we;
	plik_we.open("Wezly.txt");

	if (plik_we.is_open())
	{
		while (getline(plik_we, line))
			++liczba_wezlow;
		cout << "\nLiczba wezlow wynosi: " << liczba_wezlow << endl;
	}
	else cout << "Nie mozna wczytac pliku 'Wezly.txt' w celu policzenia wezlow !\n";

	return liczba_wezlow;
}
//tworzy macierz admitancyjn¹
void makeMatrix(struktura_linia *k, klasa_macierz &obiekt, int ileD, int ileM)
{
	liczba_zesp Z(0, 0), y(0, 0);
	float X, R, B; //to juz nie beda jednostkowe

				   //Zerowanie macierzy Y:
	for (int i = 0; i < ileM; i++) //po wierszach
	{
		for (int j = 0; j < ileM; j++) //po kolumnach
			obiekt.macierz[i][j] = 0;
	}

	//Dodanie do macierzy elementow wzdluznych - elementy pozadiagonalne
	for (int i = 0; i < ileD; i++)
	{
		R = k[i].r*k[i].length;
		X = k[i].x*k[i].length;
		Z = liczba_zesp(R, X);
		y = liczba_zesp(1, 0) / (Z); //to jest po prostu 1/Z
		obiekt.macierz[k[i].from - 1][k[i].to - 1] = -y; //linie sa numerowane od 1 dlatego -1
		obiekt.macierz[k[i].to - 1][k[i].from - 1] = -y;
	}
	//uzupelnienie elementow diagonalnych elementami wzdluznymi
	for (int i = 0; i < ileM; i++)
	{
		for (int j = 0; j < ileM; j++)
			if (j != i) obiekt.macierz[i][i] += obiekt.macierz[i][j];  // to¿same: obiekt.macierz[i][i] = obiekt.macierz[i][i] + obiekt.macierz[i][j]
		obiekt.macierz[i][i] = -obiekt.macierz[i][i];
	}

	//Dodanie pojemnoœci do elementów diagonalnych:
	for (int i = 0; i < ileD; i++)
	{
		B = k[i].b*k[i].length*pow(10, -6); //10^-6
		y = liczba_zesp(0, B / 2);
		obiekt.macierz[k[i].from - 1][k[i].from - 1] += y;
		obiekt.macierz[k[i].to - 1][k[i].to - 1] += y;
	}
}



/*KONIEC FUNKCJE ZEWNETRZNE*/

/*PROGRAM GLOWNY*/

int main()
{
	int temp = 10000;
	int temp2;
	char c = 0;
	do
	{
		int dimD = licz_linie();
		struktura_linia *br;
		br = new struktura_linia[dimD];
		int dimM = licz_wezly();
		struktura_bus *bus;
		bus = new struktura_bus[dimM];
		klasa_macierz macAdm(dimM);

		odczyt_plik_dane(br, dimD);
		odczyt_plik_wezly(bus, dimM);

		cout << "\nMakeMatrix->'1' \nDodaj wezel->'2' \nDodaj linie  ->'3' \nModyfikuj linie->'4'\nWyswietl dane o wezlach i liniach->'5'\nUsun linie->'6' \nNormalizuj macierz Y->'7'\nWyjdz z programu -> 'z'\nCo chcesz zrobic? ";
		cin >> c;
		cout << "\n";
		switch (c)
		{

		case '1':
			makeMatrix(br, macAdm, dimD, dimM);
			macAdm.zapis_plik_macierz(dimM);
			macAdm.odczyt_plik_macierz(dimM);

			break;
		case '2':
			dodaj_wezel(bus, dimM);
			zapis_plik_wezly(bus, dimM + 1); //bo chcemy zapisac do pliku strukture o wiekszym rozmiarze niz plik poczatkowy
			dodaj_linie(br, dimD); //od razu dodaje linie zeby nie bylo izolowanych wezlow
			zapis_plik_dane(br, dimD + 1);

			break;
		case '3':
			dodaj_linie(br, dimD);
			zapis_plik_dane(br, dimD + 1);
			break;
		case '4':
			wyswietlenie_linia(br, dimD);
			modyfikacja_linii(br);
			zapis_plik_dane(br, dimD);
			break;
		case '5':
			wyswietlenie_wezel(bus, dimM);
			wyswietlenie_linia(br, dimD);
			break;
		case '6':
			wyswietlenie_linia(br, dimD);
			usun_linie(br, dimD);
			wyswietlenie_linia(br, dimD - 1);
			zapis_plik_dane(br, dimD - 1);
			break;
		case '7':
			makeMatrix(br, macAdm, dimD, dimM);
			macAdm.zapis_plik_macierz(dimM);
			macAdm.odczyt_plik_macierz(dimM);
			temp2 = usun_wezly(macAdm, dimM, bus, dimM, temp);
			if (temp2 == 1)
			{
				normalizacja(br, dimD, bus, dimM - 1, temp);
				zapis_plik_dane(br, dimD);
				zapis_plik_wezly(bus, dimM - 1);
			}
			break;
		case 'z':

			cout << "Do widzenia\n\nProgram stworzony przez:\nAgata Gawronska\nKrzysztof Krolikowski\n\n";
			break;
		default:
			cout << "Podaj poprawne polecenie\n";
			break;

			cout << "\n\n";
			delete[] br;
			delete[] bus;
		}
	} while (c != 'z');


	system("Pause");
}

