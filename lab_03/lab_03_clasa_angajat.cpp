#include <iostream>
using namespace std;

class Angajat {
private:
    char* nume;
    char identificator[10];
    int* vanzari_lunare;
    int numar_luni;

    const int id;

public:
    static int nr_total;

    // constructor fara parametri
    Angajat()
        : id(-1)
    {
        this->nume = new char[strlen("Nedefinit") + 1];
        strcpy(this->nume, "Nedefinit");
        strcpy(this->identificator, "-");
        this->vanzari_lunare = nullptr;
        this->numar_luni = 0;
        this->nr_total = this->nr_total + 1;
    }

    // constructor cu parametri
    Angajat(const char* nume, const char* identificator, int* vanzari_lunare, int numar_luni, int id)
        : id(id)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        strcpy(this->identificator, identificator);
        this->numar_luni = numar_luni;
        if (numar_luni > 0) {
            this->vanzari_lunare = new int[numar_luni];
            for (int i = 0; i < numar_luni; i++) {
                this->vanzari_lunare[i] = vanzari_lunare[i];
            }
        } else {
            this->vanzari_lunare = nullptr;
        }
        this->nr_total++;
    }

    // constructor de copiere
    Angajat(const Angajat& copie)
        : id(copie.id + 1)
    {
        this->nume = new char[strlen(copie.nume) + 1];
        strcpy(this->nume, copie.nume);
        strcpy(this->identificator, copie.identificator);
        this->numar_luni = copie.numar_luni;
        if (copie.numar_luni) {
            this->vanzari_lunare = new int[copie.numar_luni];
            for (int i = 0; i < copie.numar_luni; i++) {
                this->vanzari_lunare[i] = copie.vanzari_lunare[i];
            }
        } else {
            this->vanzari_lunare = nullptr;
        }
        this->nr_total++;
    }

    ~Angajat()
    {
        if (nume != nullptr) {
            cout << "Dezalocare nume" << endl;
            delete[] nume;
        }
        if (vanzari_lunare != nullptr) {
            cout << "Dezalocare vanzari" << endl;
            delete[] vanzari_lunare;
        }
        this->nr_total--;
    }

    void afisare() const
    {
        cout << "Nume: " << this->nume << ", identificator: " << this->identificator << ", id: " << this->id;
        if (this->numar_luni > 0 && this->vanzari_lunare != nullptr) {
            cout << ", vanzari pe " << this->numar_luni << " luni: ";
            for (int i = 0; i < this->numar_luni; i++) {
                cout << this->vanzari_lunare[i] << " ";
            }
        } else {
            cout << ", fara vanzari";
        }
        cout << endl
             << "--------------------" << endl;
    }

    // getter
    char* getNume()
    {
        return this->nume;
    }

    // setter
    void setNume(const char* numeNou)
    {
        if (this->nume != nullptr) {
            delete[] this->nume;
        }
        this->nume = new char[strlen(numeNou) + 1];
        strcpy(this->nume, numeNou);
    }
};

int Angajat::nr_total = 0;

int main()
{
    Angajat a1 = Angajat();
    a1.afisare();

    //cout << "Numar angajati: " << Angajat::nr_total << endl;

    int vanzari_initiale[4] = { 100, 200, 140, 120 };
    Angajat a2 = Angajat("Ion Popescu", "IP", vanzari_initiale, 4, 100);
    a2.afisare();

    Angajat a4 = a2;
    a4.setNume("Andrei Petrescu");
    a4.afisare();

    Angajat* pointer_a4 = &a4;
    cout << "Pointer: " << endl;
    pointer_a4->afisare();
    pointer_a4->setNume("Nume nou");
    a4.afisare();

    char* nume_angajat_2 = a2.getNume();
    cout << nume_angajat_2 << endl;

    cout << "Numar angajati: " << Angajat::nr_total << endl;

    const Angajat a3 = Angajat("Ion Popescu 2", "IP2", vanzari_initiale, 3, 101);
    a3.afisare();

    cout << "Numar angajati: " << Angajat::nr_total << endl;

    return 0;
}

// exercitiu

class TransferBancar {
    char* nume_beneficiar;
    char iban_beneficiar[34];
    double suma;
    const int id;

    static int nr_total;
};

// constructor fara param si cu toti parametrii
// destructor
// constructor copiere
// getteri+setteri nume beneficiar
// getteri suma, iban
// in main: afisare detalii obiect pe baza getterilor
// *optional: un obiect constant si un pointer la obiect