#pragma once
#include <iostream>
#include "Enum.h"

using namespace std;

class Balance {
private:
	double balance[5];

public:
	Balance(double rub, double usd, double eur, double usdt, double btc) {
		this->balance[Rub] = rub;
		this->balance[Usd] = usd;
		this->balance[Eur] = eur;
		this->balance[Usdt] = usdt;
		this->balance[Btc] = btc;
	}

	double get(CurrencyType cur) {
		return balance[cur];
	}

	void show() {
		cout << "RUB\t- " << balance[Rub] << endl;
		cout << "USD\t- " << balance[Usd] << endl;
		cout << "EUR\t- " << balance[Eur] << endl;
		cout << "USDT\t- " << balance[Usdt] << endl;
		cout << "BTC\t- " << balance[Btc] << endl;
	}

	bool isEnough(CurrencyType currency, double value) {
		return balance[currency] >= value;
	}

	void add(CurrencyType currency, double value) {
		balance[currency] += value;
	}

	Error withdraw(CurrencyType currency, double value) {
		if (balance[currency] < value) {
			return NotEnoughFunds;
		}

		balance[currency] -= value;
		return Ok;
	}
};