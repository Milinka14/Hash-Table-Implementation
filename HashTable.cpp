#include "HashTable.h"

HashTable& HashTable::operator=(const HashTable& tabela2)
{
	if (this == &tabela2) {
		return *this;
	}

	delete[] keys;
	delete[] info;
	delete[] deleted;

	size = tabela2.size;
	n = tabela2.n;
	keys = new long[size];
	info = new string[size];
	deleted = new bool[size];

	for (int i = 0; i < size; i++) {
		keys[i] = tabela2.keys[i];
		info[i] = tabela2.info[i];
		deleted[i] = tabela2.deleted[i];
	}

	brojNeuspjesnihTrazenja = tabela2.brojNeuspjesnihTrazenja;
	brojPristupaNeuspjesno = tabela2.brojPristupaNeuspjesno;
	brojUmetnutih = tabela2.brojUmetnutih;
	brojTrenutnih = tabela2.brojTrenutnih;

	fja = tabela2.fja; 

	return *this;
}

int HashTable::NadjiProst(int n)
{	
	int broj = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 2; j < i; j++) {
			if (i % j == 0) {
				break;
			}
			if (j == i - 1) {
				broj = i;
			}
		}
	}
	return broj;
}

string HashTable::findKey(long key)
{
	int i = 1;
	int maticna = key % n;
	int nova = maticna;

	while (1) {
		if (keys[nova] == key) {
			return info[nova];
		}
		if (keys[nova] == -1 and deleted[nova] == false) {
			brojPristupaNeuspjesno += i;
			brojNeuspjesnihTrazenja++;
			return "0";
		}
		if (i >= size) {
			brojPristupaNeuspjesno += i;
			brojNeuspjesnihTrazenja++;
			return "0";
		}
		nova = fja->getAddress(key, maticna, i);
		nova = nova % size;
		i++;
	}
}

int HashTable::findKeyIntSucc(long key)
{
	int i = 1;
	int maticna = key % n;
	int nova = maticna;

	while (1) {
		if (keys[nova] == key) {
			return i;
		}
		if (keys[nova] == -1 and deleted[nova] == false) {
			return 0;
		}
		if (i >= size) {
			return 0;
		}
		nova = fja->getAddress(key, maticna, i);
		nova = nova % size;
		i++;
	}
}

bool HashTable::insertKey(long key, const  string& s)
{
	int i = 1;
	int maticna = key % n;
	int nova = maticna;

	while (1) {
		if (keys[nova] == key) {
			return false;
		}
		if (keys[nova] == -1) {
			keys[nova] = key;
			info[nova] = s;
			deleted[nova] = false;
			brojUmetnutih++;
			brojTrenutnih++;
			return true;
		}
		if (i >= size) {
			return false;
		}
		nova = fja->getAddress(key, maticna, i); 
		nova = nova % size;
		i++;
	}
}

bool HashTable::deleteKey(long key)
{
	int i = 1;
	int maticna = key % n;
	int nova = maticna;

	while (1) {
		if (keys[nova] == key) {
			keys[nova] = -1;
			info[nova] = "";
			deleted[nova] = true;
			brojTrenutnih--;
			return true;

		}
		if (keys[nova] == -1 and deleted[nova] == false) {
			return false;
		}
		if (i >= size) {
			return false;
		}
		nova = fja->getAddress(key, maticna, i);
		nova = nova % size;
		i++;
	}
}

float HashTable::avgAccessSuccess()
{
	int suma = 0;
	int brojac = 0;
	for (int i = 0; i < size; i++) {
		if (keys[i] != -1) {
			int temp = findKeyIntSucc(keys[i]);
			suma += temp;
			if (temp) brojac++;
		}
	}
	return (float) suma/(float) brojac;
}

float HashTable::avgAccessUnspuccess()
{
	return (float) brojPristupaNeuspjesno/(float) brojNeuspjesnihTrazenja;
}

void HashTable::clear()
{
	for (int i = 0; i < size; i++) {
		keys[i] = -1;
		info[i] = "";
		deleted[i] = false;
	}
	brojNeuspjesnihTrazenja = 0;
	brojPristupaNeuspjesno = 0;
	brojUmetnutih = 0;
	brojTrenutnih = 0;
}

HashTable& HashTable::Rehesiraj()
{
	int noviprost = NadjiProst(size*2);
	cout << endl << endl << noviprost << endl << endl;
	HashTable novatabela(size*2,noviprost,fja);
	for (int i = 0; i < size; i++) {
		if (keys[i] != -1) {
			novatabela.insertKey(keys[i], info[i]);
		}
	}
	*this = novatabela;
	return *this;
}

ostream& operator<<(ostream& os, HashTable& tabela)
{

	for (int i = 0; i < tabela.size; i++) {
		if (tabela.keys[i] == -1) {
			os << i+1 << "          " << "EMPTY" << endl;
			continue;
		}
		os << i + 1 << "          " << tabela.keys[+i] << "          " << tabela.info[i]  << endl;
	}
	return os;
}