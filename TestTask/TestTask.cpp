#include <iostream>
#include <limits>
#include "ExchangeRate.h"
#include "Balance.h"
#include "Enum.h"


using namespace std;

void clearCin() {
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
}

double doubleInput() {
    double number;
    while (!(cin >> number)) {
        cout << "\nНеверный ввод. Введите число > ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return number;
}

Error exchange(Balance* user, CurrencyType userCur, double userValue, Balance* terminal, CurrencyType terminalCur, double terminalValue) {
    if (!user->isEnough(userCur, userValue)) {
        return NotEnoughToBuy;
    }
    if (!terminal->isEnough(terminalCur, terminalValue)) {
        return NotEnoughToSell;
    }

    user->withdraw(userCur, userValue);
    terminal->add(userCur, userValue);
    terminal->withdraw(terminalCur, terminalValue);
    user->add(terminalCur, terminalValue);

    return Ok;
}

void dialogExchange(Balance* user, Balance* terminal, ExchangeRate* rate, CurrencyType terminalCur, CurrencyType userCur) {
    rate->show(terminalCur, userCur);
    cout << "На вашем счете: " << currencyName[userCur] << " - " << user->get(userCur) << endl;
    cout << "Введите количество для покупки:\n> ";
    double buyValue = doubleInput();

    if (buyValue <= 0) {
        cout << "Ошибка. Неверная сумма\n\n";
        return;
    }

    double sellValue = buyValue * rate->get(terminalCur, userCur);
    Error e = exchange(user, userCur, sellValue, terminal, terminalCur, buyValue);

    rate->change();

    switch (e)
    {
    case Ok:
        cout << "Обмен прошел успешно!\n";
        cout << "С Вашего счета списано " << sellValue << " " << currencyName[userCur] << "\n\n";
        break;
    case NotEnoughToBuy:
        cout << "На вашем счете недостаточно средств\n\n";
        break;
    case NotEnoughToSell:
        cout << "На терминале недостаточно средств\n\n";
        break;
    }
}

void dialogChooseCurrency(Balance* user, Balance* terminal, ExchangeRate* rate) {
    while (true) {
        char buyCurr;
        cout << "\nВыберете валюту для покупки:\n"
            << "1 - RUB\n"
            << "2 - USD\n"
            << "3 - EUR\n"
            << "4 - USDT\n"
            << "5 - BTC\n"
            << "6 - назад\n> ";
        cin >> buyCurr;
        switch (buyCurr)
        {
        case '1':
        {
            char sellCurr;
            cout << "\nВыберете валюту для продажи:\n"
                << "1 - USD\n"
                << "2 - EUR\n"
                << "3 - назад\n> ";
            cin >> sellCurr;
            switch (sellCurr)
            {
            case '1':
                dialogExchange(user, terminal, rate, Rub, Usd);
                break;
            case '2':
                dialogExchange(user, terminal, rate, Rub, Eur);
                break;
            case '3':
                break;
            default:
                cout << "Неверный ввод. Повторите еще раз\n\n";
                clearCin();
                break;
            }
            break;
        }
        case '2':
        {
            char sellCurr;
            cout << "\nВыберете валюту для продажи:\n"
                << "1 - RUB\n"
                << "2 - EUR\n"
                << "3 - USDT\n"
                << "4 - BTC\n"
                << "5 - назад\n> ";
            cin >> sellCurr;
            switch (sellCurr)
            {
            case '1':
                dialogExchange(user, terminal, rate, Usd, Rub);
                break;
            case '2':
                dialogExchange(user, terminal, rate, Usd, Eur);
                break;
            case '3':
                dialogExchange(user, terminal, rate, Usd, Usdt);
                break;
            case '4':
                dialogExchange(user, terminal, rate, Usd, Btc);
                break;
            case '5':
                break;
            default:
                cout << "Неверный ввод. Повторите еще раз\n\n";
                clearCin();
                break;
            }
            break;
        }
        case '3':
        {
            char sellCurr;
            cout << "\nВыберете валюту для продажи:\n"
                << "1 - RUB\n"
                << "2 - USD\n"
                << "3 - назад\n> ";
            cin >> sellCurr;
            switch (sellCurr)
            {
            case '1':
                dialogExchange(user, terminal, rate, Eur, Rub);
                break;
            case '2':
                dialogExchange(user, terminal, rate, Eur, Usd);
                break;
            case '3':
                break;
            default:
                cout << "Неверный ввод. Повторите еще раз\n\n";
                clearCin();
                break;
            }
            break;
        }
        case '4':
        {
            char sellCurr;
            cout << "\nВыберете валюту для продажи:\n"
                << "1 - USD\n"
                << "2 - назад\n> ";
            cin >> sellCurr;
            switch (sellCurr)
            {
            case '1':
                dialogExchange(user, terminal, rate, Usdt, Usd);
                break;
            case '2':
                break;
            default:
                cout << "Неверный ввод. Повторите еще раз\n\n";
                clearCin();
                break;
            }
            break;
        }
        case '5':
        {
            char sellCurr;
            cout << "\nВыберете валюту для продажи:\n"
                << "1 - USD\n"
                << "2 - назад\n> ";
            cin >> sellCurr;
            switch (sellCurr)
            {
            case '1':
                dialogExchange(user, terminal, rate, Btc, Usd);
                break;
            case '2':
                break;
            default:
                cout << "Неверный ввод. Повторите еще раз\n\n";
                clearCin();
                break;
            }
            break;
        }
        case '6':
            return;
        default:
            cout << "Неверный ввод. Повторите еще раз\n\n";
            clearCin();
            break;
        }
    }
}

int main()
{
    setlocale(LC_CTYPE, "rus");

    ExchangeRate* rate = new ExchangeRate();
    Balance* terminal = new Balance(10000, 1000, 1000, 1000, 1.5);
    Balance* user = new Balance(1000000, 0, 0, 0, 0);
    bool run = true;

    while (run) {
        char answer;
        cout << "Выберете операцию:\n"
            << "1 - Ваш счет\n"
            << "2 - Текущий курс валют\n"
            << "3 - Обменять валюту\n> ";
        cin >> answer;
        switch (answer) {
        case '1':
            user->show();
            cout << "\n";
            break;
        case '2':
            rate->showAll();
            cout << "\n";
            break;
        case '3':
            dialogChooseCurrency(user, terminal, rate);
            break;
        default:
            cout << "Неверный ввод. Повторите еще раз\n\n";
            clearCin();
            break;
        }   
    }
}
