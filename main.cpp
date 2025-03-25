#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include"QuadraticHashing.h"
#include"HashTable.h"

using namespace std;



int main() {
	srand(static_cast<unsigned int>(std::time(nullptr)));
	int n, dimenzije,brojkljuceva;
	cout << "Unesite dimenzije Hes Tabele: ";
	cin >> dimenzije;
	n = HashTable::NadjiProst(dimenzije);
	QuadraticHashing* fja = new QuadraticHashing();
	fja->PostaviParametre(0, 1);
	HashTable tabela(dimenzije, n, fja);
	int izbor;
	long kljuc,min,max;
	min = max = 0;
	string info,line;
	ifstream inputFile("text.txt");

	while (true) {
		cout << "1. Umetnite kljuc u hes tabelu" << endl;
		cout << "2. Pretrazite kljuc" << endl;
		cout << "3. Obrisite kljuc" << endl;
		cout << "4. Resetujte statistiku" << endl;
		cout << "5. Ispraznite tabelu" << endl;
		cout << "6. Da ispisete tabelu" << endl;
		cout << "7. Da zavrsite program" << endl;
		cout << "8. Za evaluaciju preformansi" << endl;
		cout << "9. Za upis iz dadoteke" << endl;
		cin >> izbor;
		switch (izbor) {
		case 1:
			cout << "Koji kljuc zelite da uneste: ";
			cin >> kljuc;
			cout << endl;
			cout << "Unesite string: ";
			cin >> info;
			cout << endl;

			if (kljuc < min || min == 0) min = kljuc;
			if (kljuc > max || max == 0) max = kljuc;
			
			tabela.insertKey(kljuc, info);

			if (tabela.fillRatio() > 0.60 or tabela.avgAccessUnspuccess() > 4.0 or tabela.avgAccessUnspuccess() > 4.0) {
				tabela.Rehesiraj();
			}

			break;
		case 2:
			cout << "Koji kljuc zelite da pretrezite: ";
			cin >> kljuc;
			cout << endl;
			cout << (tabela.findKey(kljuc) != "0" ? tabela.findKey(kljuc) : "Ne postoji zadati kljuc");
			cout << endl;
			break;
		case 3:
			cout << "Koji kljuc zelite da obrisete: ";
			cin >> kljuc;
			cout << endl;
			tabela.deleteKey(kljuc);
			break;
		case 4:
			tabela.ResetStatistics();
			break;
		case 5:
			tabela.clear();
			break;
		case 6:
			cout << tabela;
			break;
		case 7:
			delete fja;
			cout << tabela.fillRatio();
			exit(0);
			break;
		case 8:
			cout << "Koliko random kljuceva zelite da pretrazujete: ";
			cin >> brojkljuceva;
			for (int i = 0; i < brojkljuceva; i++) {
				long range = max - min + 1;
				long slucajni = min + (rand() % range);
				tabela.findKey(slucajni);
			}

			cout << "Prosjecan broj pristupa pri uspjesnoj pretrazi je: " << tabela.avgAccessSuccess();
			cout << "Prosjecan broj pristupa pri neuspjesnoj pretrazi je: " << tabela.avgAccessUnspuccess();
			cout << endl;
			break;
		case 9:
			while (inputFile >> line >> kljuc) {
				tabela.insertKey(kljuc,line);
				if (kljuc < min || min == 0) min = kljuc;
				if (kljuc > max || max == 0) max = kljuc;
			}

			if (tabela.fillRatio() > 0.60 or tabela.avgAccessUnspuccess() > 4.0 or tabela.avgAccessUnspuccess() > 4.0) {
				tabela.Rehesiraj();
			}

			break;
		}
	}

	inputFile.close();
}
/*
	tabela.insertKey(38,"1");
	tabela.insertKey(31,"2");
	tabela.insertKey(10,"3");
	tabela.insertKey(56,"4");
	tabela.insertKey(21,"5");
	tabela.deleteKey(21);
	tabela.deleteKey(10);
	cout << tabela.findKey(38) << endl;
	cout << tabela.findKey(31) << endl;
	cout << tabela.findKey(10) << endl;
	cout << tabela.findKey(56) << endl;
	cout << tabela.findKey(21) << endl;
	//cout << tabela.findKey(10) << endl;
	cout << tabela.keyCount() << endl;
	cout << tabela.avgAccessSuccess() << endl;
	cout << tabela.avgAccessUnspuccess() << endl;
	cout << tabela;
*/