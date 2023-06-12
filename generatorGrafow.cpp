// generowanie grafów
#include <iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <cstdlib>

using namespace std;

class List
{
public:
	List* next;
	int v,weight;
};

void listEdges(int wierzcho³ek, List** tabL)
{
	List* p;
	for (int i = 0;i < wierzcho³ek; i++)
	{
		
		cout << "Wierzcholek[" << i << "]= ";
		for (p = tabL[i];p;p = p->next)
		{
			cout<<p->v << " " << p->weight <<" | ";
		}
		cout << endl;
	}
}

void showMatrix(int wierzcho³ek, int** tabM)
{
	cout << "Macierz sasiedztwa" << endl;
	for (int k = 0;k < wierzcho³ek;k++)
	{
		if (k == 0) cout << "  ";
		cout << k << " ";
	}
	for (int i = 0; i < wierzcho³ek;i++)
	{
		cout << endl;
		for (int j = 0; j < wierzcho³ek;j++)
		{
			if (j == 0) cout << i << " ";
			cout << tabM[i][j] << " ";
		}
	}cout << endl;
}







void krawedzie(int wierzcho³ek, int krawedz, int** tabM, List** tabL)
{
	List* p;
	int ws=0, wk=1, waga;
	srand(time(0));
	for (int i = 0;i < krawedz;i++)
	{
		wk = wk % wierzcho³ek;
		if (wk == 0) { ws++; wk = ws; }
		if (wk == ws) wk++;
		/*cout << "Podaj wierzcholek poczatkowy: ";
		cin >> ws;
		cout << endl << "Podaj wierzcholek koncowy: ";
		cin >> wk;
		cout << endl << "Podaj wage: ";
		cin >> waga;*/
		waga = (rand() % 9) + 1;
		tabM[ws][wk] = waga; //zapis do macierzy

		p = new List;
		p->v = wk;
		p->weight = waga;
		p->next = tabL[ws];
		tabL[ws] = p;
		cout << endl;

		wk++;
	}

}

int main()
{
	int wierzcho³ek, krawêdz, ws, wk, waga,choice;
	cout << "Podaj liczbe wierzcholkow: ";
	cin >> wierzcho³ek;
	cout << "Wybierz gestosc grafu. 1.25% 2.50% 3. 75% 4. Graf pelny." << endl;
	cin >> choice;
	krawêdz = (wierzcho³ek * (wierzcho³ek - 1)) / 2;
	if (choice == 1) krawêdz = 0.25 * krawêdz;
	else if (choice == 2) krawêdz = 0.5 * krawêdz;
	else if (choice == 3) krawêdz = 0.75 * krawêdz;
	else if (choice == 4) krawêdz = krawêdz;
	else { cout << "Nie wybrales zadnej z dostepnych opcji "; exit(1); }
	
	

	//macierz s¹siedztwa tworzenie i uzupelnianie zerami

	int** tabM;


	tabM = new int* [wierzcho³ek];

	for (int i = 0; i < wierzcho³ek; i++)
	{
		tabM[i] = new int[wierzcho³ek];
	}

	for (int i = 0; i < wierzcho³ek;i++)
	{
		for (int j = 0; j < wierzcho³ek;j++)
		{
			tabM[i][j] = 0;
		}
	}



	//lista s¹siedztwa tworzenie
	int v1, v2;
	List** tabL;
	List* p, *r;

	tabL = new List * [wierzcho³ek];

	for (int i = 0;i < wierzcho³ek;i++)
	{
		tabL[i] = NULL;
	}

	krawedzie(wierzcho³ek, krawêdz, tabM, tabL);

	////wyswietlanie macierzy s¹siedztwa
	//cout << "Macierz sasiedztwa" << endl;
	//for (int k = 0;k < wierzcho³ek;k++)
	//{
	//	if (k == 0) cout << "  ";
	//	cout << k << " ";
	//}
	//for (int i = 0; i < wierzcho³ek;i++)
	//{
	//	cout << endl;
	//	for (int j = 0; j < wierzcho³ek;j++)
	//	{
	//		if (j == 0) cout << i << " ";
	//		cout << tabM[i][j] << " ";
	//	}
	//}cout << endl;

	////wyswietlanie listy s¹siedztwa
	//int n = 0;
	//cout << endl<<"Lista sasiedztwa" << endl;
	//cout << wierzcho³ek << " " << krawêdz << endl;
	//for (int i = 0;i < wierzcho³ek ; i++)
	//{
	//	p = tabL[i];
	//	while (p)
	//	{
	//		cout<< "L["<<n<<"]->" << i << " " << p->v << " " << p->weight;
	//		p = p->next;
	//		n++;
	//		cout << endl;
	//	}
	//}

	//zapis do pliku macierzy s¹siedztwa
	string plik_name = ("C:/Users/Lenovo/Desktop/grafM.txt");
	ofstream plik(plik_name);  //wczytywany plik
	plik << wierzcho³ek << " " << krawêdz << endl;
	for (int i = 0; i < wierzcho³ek;i++)
	{
		for (int j = 0; j < wierzcho³ek;j++)
		{
			plik << tabM[i][j] << " ";
		}
		plik << endl;
	}
	plik.close();

	//zapis do pliku listy s¹siedztwa
	string plik_name2 = ("C:/Users/Lenovo/Desktop/grafL.txt");
	ofstream plik2(plik_name2);  //wczytywany plik
	plik2 << wierzcho³ek << " " << krawêdz<<endl;
	for (int i = 0; i < wierzcho³ek;i++)
	{
		p = tabL[i];
		while (p)
		{
			plik2<<i<< " "<< p->v << " " << p->weight << endl;
			p = p->next;
		}
		cout << endl;
	}
	plik2.close();

	
	//zwolnianie pamiêci

	delete[] tabM;

	for (int i = 0;i < wierzcho³ek;i++)
	{
		p = tabL[i];
		while (p)
		{
			r = p;
			p = p->next;
			delete r;
		}
	}
	delete[] tabL;

}