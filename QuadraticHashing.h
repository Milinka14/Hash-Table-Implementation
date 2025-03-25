#pragma once
#include "AddressFunction.h"


class QuadraticHashing:public AddressFunction
{
private:
	int c1;
	int c2;
public:
	void PostaviParametre(int c1f, int c2f) {
		c1 = c1f; c2 = c2f;
	}
	int getAddress(long key, int adr, int i) override {
		return adr + i * c1 + i * i * c2;
	};
};

