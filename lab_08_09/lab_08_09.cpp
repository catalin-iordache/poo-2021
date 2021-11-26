#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#pragma warning(disable : 4996)

class InvalidDiscountException : exception {
public:
    InvalidDiscountException()
    {
    }

    InvalidDiscountException(const char* message)
        : exception(message)
    {
    }
};

class IDiscount {
public:
    virtual void aplica_discount(int procent) = 0;
};

class ICategorie {
public:
    virtual const char* get_categorie() = 0;
};

class Produs : IDiscount, ICategorie {
    char denumire[50];
    float pret = 0;
    static int stoc;

public:
    Produs()
    {
        strcpy(this->denumire, "Fara nume");
        stoc++;
    }

    Produs(const char* denumire, float pret)
    {
        strcpy(this->denumire, denumire);
        this->pret = pret;
        stoc++;
    }

    Produs(const Produs& copie)
    {
        strcpy(this->denumire, copie.denumire);
        this->pret = copie.pret;
        stoc++;
    }

    ~Produs()
    {
        stoc--;
    }

    float get_pret()
    {
        return this->pret;
    }

    const char* get_denumire()
    {
        return this->denumire;
    }

    void aplica_discount(int procent)
    {
        if (procent > 0 && procent < 100) {
            this->pret = this->pret * (100 - procent) / 100;
        } else {
            throw InvalidDiscountException();
        }
    }

    const char* get_categorie()
    {
        return "Fara categorie";
    }

    Produs& operator=(const Produs& produs)
    {
        strcpy(this->denumire, produs.denumire);
        this->pret = produs.pret;
        return *this;
    }

    void operator()()
    {
        cout << *this << endl;
    }

    friend ostream& operator<<(ostream&, Produs);
    friend ofstream& operator<<(ofstream& out, Produs produs);
    friend ifstream& operator>>(ifstream& in, Produs& produs);

    Produs operator+(float pret)
    {
        Produs copie = *this;
        copie.pret += pret;
        return copie;
    }

    friend Produs operator+(float pret, const Produs& produs);

    Produs operator+(const Produs& produs)
    {
        Produs copie = *this;
        copie.pret += produs.pret;
        return copie;
    }

    Produs& operator+=(float diferenta)
    {
        this->pret += diferenta;
        return *this;
    }

    Produs& operator-=(float diferenta)
    {
        this->pret -= diferenta;
        return *this;
    }

    Produs& operator/=(float diferenta)
    {
        this->pret -= diferenta;
        return *this;
    }

    Produs& operator*=(float diferenta)
    {
        this->pret *= diferenta;
        return *this;
    }

    Produs& operator++()
    {
        this->pret += 100;
        return *this;
    }

    Produs operator++(int)
    {
        Produs copie = *this;
        this->pret += 100;
        return copie;
    }
};

Produs operator+(float pret, const Produs& produs)
{
    Produs copie = produs;
    copie.pret += pret;
    return copie;
}

ostream& operator<<(ostream& out, Produs produs)
{
    out << endl
        << "Denumire: " << produs.denumire << ", pret: " << produs.pret;
    return out;
}
ofstream& operator<<(ofstream& out, Produs produs)
{
    out << produs.denumire << endl
        << produs.pret << endl;
    return out;
}

ifstream& operator>>(ifstream& in, Produs& produs)
{
    char buffer[50];
    in >> ws;
    in.getline(buffer, 50);
    strcpy(produs.denumire, buffer);
    in >> produs.pret;
    return in;
}

class CosCumparaturi : IDiscount {
    int nr_produse = 0;
    Produs* produse = nullptr;

public:
    CosCumparaturi()
    {
    }

    CosCumparaturi(int nr_produse, Produs* produse)
    {
        this->nr_produse = nr_produse;
        if (nr_produse > 0) {
            this->produse = new Produs[nr_produse];
            for (int i = 0; i < nr_produse; i++) {
                this->produse[i] = produse[i];
            }
        } else {
            this->produse = nullptr;
        }
    }

    CosCumparaturi(const CosCumparaturi& copie)
    {
        this->nr_produse = copie.nr_produse;
        if (copie.nr_produse > 0) {
            this->produse = new Produs[copie.nr_produse];
            for (int i = 0; i < copie.nr_produse; i++) {
                this->produse[i] = copie.produse[i];
            }
        }
    }

    ~CosCumparaturi()
    {
        if (this->produse != nullptr) {
            delete[] this->produse;
        }
    }

    void checkout()
    {
        cout << endl
             << "Checkout";
        float suma = 0;
        if (this->nr_produse > 0) {
            for (int i = 0; i < this->nr_produse; i++) {
                suma += this->produse[i].get_pret();
                cout << this->produse[i];
            }
        } else {
            cout << endl
                 << "Cosul este gol";
        }
        cout << endl
             << "Total de plata: " << suma;
        cout << endl;
    }

    void aplica_discount(int procent)
    {
        if (procent > 0 && procent < 100) {
            if (this->nr_produse > 0) {
                for (int i = 0; i < this->nr_produse; i++) {
                    this->produse[i].aplica_discount(procent);
                }
            }
        } else {
            throw InvalidDiscountException();
        }
    }

    void golire_cos()
    {
        this->nr_produse = 0;
        if (this->produse != nullptr) {
            delete[] this->produse;
        }
    }

    CosCumparaturi& operator=(const CosCumparaturi& cos)
    {
        this->nr_produse = cos.nr_produse;
        if (this->produse != nullptr) {
            delete[] this->produse;
        }
        if (cos.nr_produse > 0) {
            this->produse = new Produs[cos.nr_produse];
            for (int i = 0; i < cos.nr_produse; i++) {
                this->produse[i] = cos.produse[i];
            }
        } else {
            this->produse = nullptr;
        }
    }

    // pre
    CosCumparaturi& operator--()
    {
        if (this->nr_produse > 1) {
            this->nr_produse--;
            Produs* buffer = new Produs[this->nr_produse];
            for (int i = 0; i < this->nr_produse; i++) {
                buffer[i] = this->produse[i];
            }
            delete[] this->produse;
            this->produse = buffer;
        } else if (this->nr_produse == 1) {
            this->nr_produse = 0;
            delete[] this->produse;
            this->produse = nullptr;
        }
        return *this;
    }

    // post
    CosCumparaturi operator--(int)
    {
        CosCumparaturi copie = *this;
        if (this->nr_produse > 1) {
            this->nr_produse--;
            Produs* buffer = new Produs[this->nr_produse];
            for (int i = 0; i < this->nr_produse; i++) {
                buffer[i] = this->produse[i];
            }
            delete[] this->produse;
            this->produse = buffer;
        } else if (this->nr_produse == 1) {
            this->nr_produse = 0;
            delete[] this->produse;
            this->produse = nullptr;
        }
        return copie;
    }

    friend ofstream& operator<<(ofstream&, CosCumparaturi);
    friend ifstream& operator>>(ifstream&, CosCumparaturi&);

    Produs operator[](int index)
    {
        if (index >= 0 && index <= this->nr_produse && this->produse != nullptr) {
            return this->produse[index];
        } else {
            throw exception();
        }
    }
};

ofstream& operator<<(ofstream& out, CosCumparaturi cos)
{
    out << cos.nr_produse << endl;
    if (cos.nr_produse > 0) {
        for (int i = 0; i < cos.nr_produse; i++) {
            out << cos.produse[i];
        }
    }
    return out;
}

ifstream& operator>>(ifstream& in, CosCumparaturi& cos)
{
    in >> cos.nr_produse;
    //in.ignore();
    //in >> ws;
    if (cos.produse != nullptr) {
        delete[] cos.produse;
    }
    if (cos.nr_produse > 0) {
        cos.produse = new Produs[cos.nr_produse];
        for (int i = 0; i < cos.nr_produse; i++) {
            in >> cos.produse[i];
            //in.ignore();
            //in >> ws;
        }
    } else {
        cos.produse = nullptr;
    }
    return in;
}

int Produs::stoc = 0;

int main()
{

    Produs p1 = Produs("Laptop", 2000);
    p1();
    Produs p2 = Produs("Masina de spalat", 1200);
    Produs p3 = Produs("Televizor", 1600);

    Produs produse[] = { p1, p2, p3 };
    CosCumparaturi cos = CosCumparaturi(3, produse);

    try {
        cos.aplica_discount(150);
    } catch (InvalidDiscountException e) {
        cout << "Discount invalid";
    } catch (exception e) {
        cout << e.what();
    }

    cos.checkout();

    // fisiere
    cout << endl
         << "Lucru cu fisiere" << endl;
    //
    ofstream fisierOut;
    fisierOut.open("produs.txt", ofstream::out);
    fisierOut << p3;
    fisierOut.close();
    //
    ifstream fisierIn;
    fisierIn.open("produs.txt", ifstream::in);
    Produs p4;
    fisierIn >> p4;
    cout << p4;
    fisierIn.close();

    //
    fisierOut.open("produse.txt", ofstream::out);
    fisierOut << cos;
    fisierOut.close();
    //
    fisierIn.open("produse.txt", ifstream::in);

    CosCumparaturi cosCitit;
    fisierIn >> cosCitit;
    cout << endl;
    cosCitit.checkout();

    //Produs p5 = 100 + p1;
    Produs p5 = p1 + 100;
    cout << p1 + p5;
    cout << p5;

    return 0;
}