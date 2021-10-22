#include <iostream>
#include <string>

using namespace std;

#pragma warning(disable : 4996)

enum TipTransfer { NORMAL = 1,
    INSTANT,
    INTERNATIONAL };

class TransferBancar {
    char* nume_beneficiar = nullptr;
    char iban_beneficiar[34];
    double suma;
    const int id;
    TipTransfer tip;

    static int nr_total;

public:
    TransferBancar()
        : id(this->nr_total + 1)
    {
        this->nume_beneficiar = new char[strlen("Anonim") + 1];
        strcpy(this->nume_beneficiar, "Anonim");
        strcpy(this->iban_beneficiar, "-");
        this->suma = 0;
        this->tip = TipTransfer::NORMAL;
        this->nr_total++;
    }

    TransferBancar(const char* nume_beneficiar, const char* iban_beneficiar, double suma, TipTransfer tip)
        : id(this->nr_total + 1)
    {
        if (nume_beneficiar != nullptr) {
            this->nume_beneficiar = new char[strlen(nume_beneficiar) + 1];
            strcpy(this->nume_beneficiar, nume_beneficiar);
        }
        if (iban_beneficiar != nullptr) {
            strcpy(this->iban_beneficiar, iban_beneficiar);
        }
        this->suma = suma;
        this->tip = tip;
        this->nr_total++;
    }

    TransferBancar(const TransferBancar& copie)
        : id(copie.id)
    {
        if (copie.nume_beneficiar != nullptr) {
            this->nume_beneficiar = new char[strlen(copie.nume_beneficiar) + 1];
            strcpy(this->nume_beneficiar, copie.nume_beneficiar);
        }
        strcpy(this->iban_beneficiar, copie.iban_beneficiar);
        this->suma = copie.suma;
        this->tip = copie.tip;
        this->nr_total++;
    }

    ~TransferBancar()
    {
        if (this->nume_beneficiar != nullptr) {
            delete[] nume_beneficiar;
        }
        this->nr_total--;
    }

    friend ostream& operator<<(ostream& out, TransferBancar transfer);

    friend istream& operator>>(istream& in, TransferBancar& transfer);

    TransferBancar& operator=(const TransferBancar& transfer)
    {
        if (this->nume_beneficiar != nullptr) {
            delete[] this->nume_beneficiar;
        }
        if (transfer.nume_beneficiar != nullptr) {
            this->nume_beneficiar = new char[strlen(transfer.nume_beneficiar) + 1];
            strcpy(this->nume_beneficiar, transfer.nume_beneficiar);
        } else {
            this->nume_beneficiar = nullptr;
        }
        strcpy(this->iban_beneficiar, transfer.iban_beneficiar);
        this->suma = transfer.suma;
        this->tip = transfer.tip;

        return *this;
    }
};

ostream& operator<<(ostream& out, TransferBancar transfer)
{
    out << endl
        << "Nume: ";
    if (transfer.nume_beneficiar != nullptr) {
        out << transfer.nume_beneficiar;
    } else {
        out << " - ";
    }
    out << ", IBAN:" << transfer.iban_beneficiar << ", suma: " << transfer.suma << " RON"
        << ", tip:" << transfer.tip << ", id: " << transfer.id;
    out << endl;
    return out;
}

istream& operator>>(istream& in, TransferBancar& transfer)
{
    cout << endl
         << "IBAN beneficiar: ";
    in >> transfer.iban_beneficiar;
    cout << endl
         << "Nume beneficiar: ";
    char buffer[1000];
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    in.getline(buffer, 1000);

    if (transfer.nume_beneficiar != nullptr) {
        delete[] transfer.nume_beneficiar;
    }
    transfer.nume_beneficiar = new char[strlen(buffer) + 1];
    strcpy(transfer.nume_beneficiar, buffer);
    cout << endl
         << "Suma: ";
    in >> transfer.suma;
    cout << endl
         << "Tip transfer (Normal: 1, Instant: 2, Urgent: 3): ";
    int tip_transfer;
    in >> tip_transfer;
    switch (tip_transfer) {
    case 1:
        transfer.tip = TipTransfer::NORMAL;
        break;
    case 2:
        transfer.tip = TipTransfer::INSTANT;
        break;
    case 3:
        transfer.tip = TipTransfer::INTERNATIONAL;
        break;
    default:
        transfer.tip = TipTransfer::NORMAL;
        break;
    }
    return in;
}

int TransferBancar::nr_total = 0;

int main()
{
    TransferBancar t1 = TransferBancar();
    cout << "t1: " << t1;
    TransferBancar t2 = TransferBancar("IonPopescu", "ROBT24242424XX", 650, TipTransfer::INSTANT);
    cout << "t2: " << t2;
    TransferBancar t3;
    cout << "t3: " << t3;
    t3 = t2;
    cout << "t3" << t3;

    TransferBancar t4;
    cin >> t4;
    cout << "t4" << t4;

    return 0;
}

// exercitiu
class Carte {
    char* denumire;
    char isbn[13];
    int numar_pagini;
    // enum tip carte
};

/*
- constructor fara parametri, cu 1 parametru, cu toti parametrii
- constructor de copiere
- destructor
- supraincarcare operator =
*/

// testare main()

/*
- supraincarcare operatori <<, >>
*/

/*
- getteri + setteri pentru toate atributele
*/