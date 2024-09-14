#pragma once

#include <ctime>
#include <iostream>
#include "Enum.h"
using namespace std;

class ExchangeRate {
private:
	double rate[5][5];

public:
	ExchangeRate() {
		rate[Usd][Rub] = 90; rate[Rub][Usd] = 1 / rate[Usd][Rub];
		rate[Eur][Rub] = 99.26; rate[Rub][Eur] = 1 / rate[Eur][Rub];
		rate[Eur][Usd] = 1.11; rate[Usd][Eur] = 1 / rate[Eur][Usd];
		rate[Usdt][Usd] = 0.998; rate[Usd][Usdt] = 1 / rate[Usdt][Usd];
		rate[Btc][Usd] = 59096; rate[Usd][Btc] = 1 / rate[Btc][Usd];
	}

	double get(CurrencyType cur1, CurrencyType cur2) {
		return rate[cur1][cur2];
	}

	void showAll() {
		cout << "Курс валют сейчас:\n";
		cout << "1 USD\t= " << rate[Usd][Rub] << "\tRUB\n";
		cout << "1 EUR\t= " << rate[Eur][Rub] << "\tRUB\n";
		cout << "1 EUR\t= " << rate[Eur][Usd] << "\tUSD\n";
		cout << "1 USDT\t= " << rate[Usdt][Usd] << "\tUSD\n";
		cout << "1 BTC\t= " << rate[Btc][Usd] << "\tUSD\n";
	}

	void show(CurrencyType cur1, CurrencyType cur2) {
		cout << "Текущий курс:\n";
		cout << "1 " << currencyName[cur1] << "\t = " << rate[cur1][cur2] << "\t" << currencyName[cur2] << "\n";
	}

	void change() {
		srand(time(0));

		rate[Usd][Rub] = round(rate[Usd][Rub] * (95 + (rand() % 11))) / 100;
		rate[Eur][Rub] = round(rate[Eur][Rub] * (95 + (rand() % 11))) / 100;
		rate[Eur][Usd] = round(rate[Eur][Usd] * (95 + (rand() % 11))) / 100;
		rate[Usdt][Usd] = round(rate[Usdt][Usd] * (95 + (rand() % 11)) * 10) / 1000;
		rate[Btc][Usd] = round(rate[Btc][Usd] * (0.95 + (rand() % 11) / 100));

		rate[Rub][Usd] = 1 / rate[Usd][Rub];
		rate[Rub][Eur] = 1 / rate[Eur][Rub];
		rate[Usd][Eur] = 1 / rate[Eur][Usd];
		rate[Usd][Usdt] = 1 / rate[Usdt][Usd];
		rate[Usd][Btc] = 1 / rate[Btc][Usd];
	}
};