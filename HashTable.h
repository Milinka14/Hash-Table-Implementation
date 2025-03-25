#pragma once
#include <iostream>
#include <string>
#include "QuadraticHashing.h"

using namespace std;

class HashTable
{
private:
	int brojNeuspjesnihTrazenja = 0;
	int brojPristupaNeuspjesno = 0;
	int brojUmetnutih = 0;
	int brojTrenutnih = 0;
	int n;
	int size;
	long* keys;
	bool* deleted;
	string* info;
	AddressFunction* fja;
public:
	HashTable(int size, int prost, AddressFunction* fja) :size(size),n(prost), fja(fja) {
		keys = new long[size];
		info = new string[size];
		deleted = new bool[size];
		for (int i = 0; i < size; i++) {
			keys[i] = -1;
			info[i] = "";
			deleted[i] = false;
		}
	}
	HashTable& operator=(const HashTable& tabela2);
	static int NadjiProst(int n);
	string findKey(long key);
	int findKeyIntSucc(long key);
	bool insertKey(long key, const string& s);
	bool deleteKey(long key);
	float avgAccessSuccess();
	float avgAccessUnspuccess();
	int keyCount() { return brojUmetnutih; }
	void ResetStatistics() { brojNeuspjesnihTrazenja = 0; brojPristupaNeuspjesno = 0; };
	int tableSize() { return size; }
	friend ostream& operator<<(ostream& os, HashTable& tabela);
	void clear();
	double fillRatio() {
		return (double)brojTrenutnih / (double)size;
	};
	HashTable& Rehesiraj();
	~HashTable() {
		delete[] keys; 
		delete[] info;
		delete[] deleted;
	}
};
