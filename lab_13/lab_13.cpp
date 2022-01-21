#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>
// standard template library

using namespace std;

#pragma warning(disable : 4996)


class Vehicul {

    const int id; // auto-incrementat pe baza nr_total
    char* denumire = nullptr;

    static int nr_total;

public:
    // constructor fara parametri, cu 1 parametru (denumire), cu toti parametrii
    // destructor
    // operator=
    // getteri + setteri
    // afisare la consola cu operator<<
    // citire de la consola cu operator>>

    Vehicul()
        : id(nr_total++)
    {
        this->denumire = new char[strlen("-") + 1];
        strcpy(this->denumire, "-");
    }

    Vehicul(const char* nume)
        : id(nr_total++)
    {
        if (nume != nullptr) {
            this->denumire = new char[strlen(nume) + 1];
            strcpy(this->denumire, nume);
        } else {
            this->denumire = new char[strlen("-") + 1];
            strcpy(this->denumire, "-");
        }
    }

    Vehicul(const char* nume, int id)
        : id(id)
    {
        if (nume != nullptr) {
            this->denumire = new char[strlen(nume) + 1];
            strcpy(this->denumire, nume);
        } else {
            this->denumire = new char[strlen("-") + 1];
            strcpy(this->denumire, "-");
        }
    }

    Vehicul(const Vehicul& copie)
        : id(copie.id)
    {
        if (copie.denumire != nullptr) {
            this->denumire = new char[strlen(copie.denumire) + 1];
            strcpy(this->denumire, copie.denumire);
        } else {
            this->denumire = new char[strlen("-") + 1];
            strcpy(this->denumire, "-");
        }
    }

    ~Vehicul()
    {
        if (this->denumire != nullptr) {
            delete[] this->denumire;
        }
        nr_total--;
    }

    Vehicul& operator=(const Vehicul& persoana)
    {
        if (this->denumire != nullptr) {
            delete[] this->denumire;
        }
        if (persoana.denumire != nullptr) {
            this->denumire = new char[strlen(persoana.denumire) + 1];
            strcpy(this->denumire, persoana.denumire);
        } else {
            this->denumire = new char[strlen("-") + 1];
            strcpy(this->denumire, "-");
        }
        return *this;
    }

    void set_nume(const char* numeNou)
    {
        if (this->denumire != nullptr) {
            delete[] this->denumire;
        }
        if (numeNou != nullptr) {
            this->denumire = new char[strlen(numeNou) + 1];
            strcpy(this->denumire, numeNou);
        } else {
            this->denumire = new char[strlen("-") + 1];
            strcpy(this->denumire, "-");
        }
    }

    const char* get_nume() const
    {
        return this->denumire;
    }

    int get_id() const
    {
        return this->id;
    }

    friend ostream& operator<<(ostream& out, Vehicul vehicul)
    {
        out << endl
            << "Denumire vehicul: ";
        if (vehicul.denumire != nullptr) {
            out << vehicul.denumire;
        } else {
            out << "-";
        }
        out << ", id: " << vehicul.id;
        return out;
    }

    friend istream& operator>>(istream& in, Vehicul& vehicul)
    {
        if (vehicul.denumire != nullptr) {
            delete[] vehicul.denumire;
        }
        char buffer[50];
        cout << endl
             << "Introduceti denumirea: ";
        in >> ws;
        in.getline(buffer, 50);
        vehicul.denumire = new char[strlen(buffer) + 1];
        strcpy(vehicul.denumire, buffer);
        return in;
    }

    virtual void functie_virtuala()
    {
        cout << endl
             << "apel din Vehicul";
    }

    bool operator<(const Vehicul& vehicul) const
    {
        if (this->denumire == nullptr) {
            return true;
        } else if (vehicul.denumire == nullptr) {
            return false;
        }

        return strcmp(this->denumire, vehicul.denumire) < 0 ? true : false;
    }

    void salveazaFisierBinar(const char* nume_fisier)
    {
        ofstream fisier_out;
        fisier_out.open(nume_fisier, ofstream::out | ofstream::binary);
        if (fisier_out.is_open()) {
            if (this->denumire == nullptr) {
                int lungime_zero = 0;
                fisier_out.write((char*)&lungime_zero, sizeof(int));
            } else {
                int lungime = strlen(this->denumire) + 1;
                fisier_out.write((char*)&lungime, sizeof(int));
                fisier_out.write(this->denumire, lungime * sizeof(char));
            }

            fisier_out.write((char*)&this->id, sizeof(int));
            fisier_out.close();
        } else {
            throw exception("Fisierul binar nu a putut fi deschis");
        }
    }

    static Vehicul initializareDinFisierBinar(const char* nume_fisier)
    {
        ifstream fisier_in;
        fisier_in.open(nume_fisier, ifstream::in | ifstream::binary);
        if (fisier_in.is_open()) {
            int id, lungime;
            char buffer[50];
            fisier_in.read((char*)&lungime, sizeof(int));
            if (lungime > 0) {
                fisier_in.read(buffer, lungime * sizeof(char));
            } else {
                strcpy(buffer, "-");
            }

            fisier_in.read((char*)&id, sizeof(id));
            char* denumire = new char[lungime];
            strcpy(denumire, buffer);
            fisier_in.close();
            return Vehicul(denumire, id);
        } else {
            throw exception("Fisierul binar nu a putut fi deschis");
        }
    }
};

int Vehicul::nr_total = 0;

int main()
{
    Vehicul v1 = Vehicul("Audi", 0);
    //Vehicul v2;
    /*   cin >> v2;
    cout << v2;*/
    Vehicul v2 = Vehicul("Tesla");
    Vehicul v3 = Vehicul("Renault");
    Vehicul v4 = Vehicul("BMW");
    //v3.functie_virtuala();

    Vehicul arr[3] = { v1, v2, v3 };
    for (int i = 0; i < 3; i++) {
        cout << endl
             << arr[i].get_nume();
    }
    cout << endl
         << "arr size: " << sizeof(arr) / sizeof(arr[0]);

    vector<Vehicul> vect;
    vect.push_back(v1);
    vect.push_back(v2);
    vect.push_back(v3);
    vect.pop_back();

    cout << endl
         << "afisare vector: ";
    for (int i = 0; i < vect.size(); i++) {
        cout << endl
             << vect[i].get_nume();
    }
    vect.push_back(v4);
    cout << endl
         << "-";
    for (int i = 0; i < vect.size(); i++) {
        cout << endl
             << vect[i].get_nume();
    };

    list<Vehicul> lista;
    lista.push_back(v1);
    lista.push_front(v2);
    lista.push_front(v3);
    lista.push_front(v3);
    lista.sort();
    lista.reverse();

    cout << endl
         << "afisare lista: ";
    list<Vehicul>::iterator it;
    for (it = lista.begin(); it != lista.end(); it++) {
        cout << endl
             << *it;
    }

    map<int, Vehicul> catalog;
    catalog[10] = v1;
    catalog[11] = v2;
    catalog[0] = v3;
    cout << "\nAfisare map:";
    map<int, Vehicul>::iterator it_map;
    for (it_map = catalog.begin(); it_map != catalog.end(); it_map++) {
        cout << endl
             << it_map->first << ", " << it_map->second.get_nume();
    }

    set<Vehicul> catalog_unic;
    catalog_unic.insert(v1);
    catalog_unic.insert(v2);
    catalog_unic.insert(v1);
    Vehicul v5 = Vehicul("Audi", 100);
    catalog_unic.insert(v5);

    set<Vehicul>::iterator it_set;
    cout << "\nAfisare set: ";

    for (it_set = catalog_unic.begin(); it_set != catalog_unic.end(); it_set++) {
        cout << endl
             << it_set->get_nume();
    }

    cout << v5;

    v5.salveazaFisierBinar("vehicul.dat");
    cout << "\nVehicul citit";
    cout << Vehicul::initializareDinFisierBinar("vehicul.dat");
}