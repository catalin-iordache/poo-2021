#include <iostream>
#include <string>

using namespace std;

#pragma warning(disable : 4996)

enum TipTransfer { NORMAL = 1,
    INSTANT,
    INTERNATIONAL };

class TransferBancar {
    char* nume_beneficiar = nullptr;
    char iban_beneficiar[34] = { '-' };
    double suma;
    const int id;
    TipTransfer tip;

    static int nr_total;

public:
    // constructor fara parametri
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

    // constructor cu toti parametrii
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

    // constructor de copiere
    TransferBancar(const TransferBancar& copie)
        : id(copie.id + 1)
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

    // destructor
    ~TransferBancar()
    {
        if (this->nume_beneficiar != nullptr) {
            delete[] nume_beneficiar;
        }
        this->nr_total--;
    }

    // getter
    char* get_nume_beneficiar()
    {
        return this->nume_beneficiar;
    }

    // setter
    void set_nume_beneficiar(const char* nume_nou)
    {
        if (this->nume_beneficiar != nullptr) {
            delete[] this->nume_beneficiar;
        }
        this->nume_beneficiar = new char[strlen(nume_nou) + 1];
        strcpy(this->nume_beneficiar, nume_nou);
    }

    TipTransfer get_tip()
    {
        return this->tip;
    }

    void set_tip(TipTransfer tip_nou)
    {
        this->tip = tip_nou;
    }

    // operator << (pentru afisare)
    friend ostream& operator<<(ostream& out, TransferBancar transfer);

    // operator >> (pentru citire)
    friend istream& operator>>(istream& in, TransferBancar& transfer);

    // operator = (atribuire)
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

    // operator + (Transfer + double)
    double operator+(double suma)
    {
        return this->suma + suma;
    }

    // operator + (double + Transfer)
    friend double operator+(double, const TransferBancar&);

    // operator + (Transfer + Transfer)
    TransferBancar operator+(const TransferBancar& transfer)
    {
        TransferBancar copie = *this;
        copie.suma += transfer.suma;
        return copie;
    }

    // operator += (Transfer += double)
    TransferBancar& operator+=(double suma_aditionala)
    {
        this->suma += suma_aditionala;
        return *this;
    }

    // preincrementare
    TransferBancar& operator++()
    {
        this->suma += 100;
        return *this;
    }

    // postincrementare
    TransferBancar operator++(int)
    {
        TransferBancar copie = *this;
        this->suma += 100;
        return copie;
    }

    // operator []
    char operator[](int index)
    {
        if (index >= 0 && index < strlen(this->iban_beneficiar)) {
            return this->iban_beneficiar[index];
        } else {
            cout << endl
                 << "Index out of range" << endl;
            return '-';
        }
    }

    // operator cast
    operator double()
    {
        return this->suma;
    }
};

double operator+(double suma, const TransferBancar& transfer)
{
    return suma + transfer.suma;
}

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
    t1.set_nume_beneficiar("Test");
    t1.set_tip(TipTransfer::INTERNATIONAL);
    cout << "t1: " << t1;
    TransferBancar t2 = TransferBancar("IonPopescu", "ROBT24242424XX", 650, TipTransfer::INSTANT);
    cout << "t2: " << t2;

    cout << "t2 + 100: " << t2 + (double)100 << endl;
    cout << "100 + t2: " << 100.00 + t2 << endl;

    TransferBancar t3 = t2 + t1;
    t3 += (double)200;
    t3 += 100.00;
    cout << "t3: " << t3.operator++(1) << endl;
    cout << "t3: " << t3 << endl;
    cout << "t3[2]: " << t3[2] << endl;
    /* cout << "t2 + t1: " << t2 + t1 << endl;*/

    cout << (double)t3 + 100.000;

    return 0;
}

// exercitiu: se porneste de la clasa din laboratorul 3
// https://github.com/catalin-iordache/poo-2021/blob/main/lab_03/lab_03_clasa_angajat.cpp
// si se realizeaza urmatoarele:

// adaugare atribut double salariu
// getteri + setteri pentru toate atributele (vanzari_lunare + nr_luni acelasi setter)
// supraincarcare operatori <<, >>, =, + (Angajat + double, double + Angajat, Angajat + Angajat), ++ (pre + post), +=, operator [], operator cast double