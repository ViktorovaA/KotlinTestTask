#pragma once

enum CurrencyType
{
	Rub,
	Usd,
	Eur,
	Usdt,
	Btc
};

const char* currencyName[] = { "Rub", "Usd", "Eur", "Usdt", "Btc"};

enum Error
{
	Ok,
	NotEnoughFunds,
	NotEnoughToBuy,
	NotEnoughToSell,
	WrongInput
};