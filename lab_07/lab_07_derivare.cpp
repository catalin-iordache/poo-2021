#include <iostream>
#include <string>

using namespace std;

#pragma warning(disable : 4996)

class Persoana {
private:
    char cnp[13] = { '-' };
    char* nume = nullptr;

public:
    Persoana()
    {
        cout << endl
             << "[Constructor fara parametri]";
        this->nume = new char[strlen("Anonim") + 1];
        strcpy(this->nume, "Anonim");
    }

    Persoana(const char* cnp, const char* nume)
    {
        cout << endl
             << "[Constructor cu parametri]";
        strcpy(this->cnp, cnp);
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
    }

    Persoana(const Persoana& copie)
    {
        cout << endl
             << "[Constructor copiere]";
        strcpy(this->cnp, copie.cnp);
        if (copie.nume != nullptr) {
            this->nume = new char[strlen(copie.nume) + 1];
            strcpy(this->nume, copie.nume);
        }
    }

    ~Persoana()
    {
        //cout << endl
        //     << "[Destructor]";
        if (this->nume != nullptr) {
            delete[] this->nume;
        }
    }

    char* get_cnp()
    {
        return this->cnp;
    }

    char* get_nume()
    {
        return this->nume;
    }

    void set_cnp(const char* cnp_nou)
    {
        strcpy(this->cnp, cnp_nou);
    }

    void set_nume(const char* nume_nou)
    {
        if (this->nume != nullptr) {
            delete[] this->nume;
        }
        this->nume = new char[strlen(nume_nou) + 1];
        strcpy(this->nume, nume_nou);
    }

    Persoana& operator=(const Persoana& persoana)
    {
        cout << endl
             << "[Operator=]";
        strcpy(this->cnp, persoana.cnp);
        if (this->nume != nullptr) {
            delete[] this->nume;
        }
        if (persoana.nume != nullptr) {
            this->nume = new char[strlen(persoana.nume) + 1];
            strcpy(this->nume, persoana.nume);
        } else {
            this->nume = nullptr;
        }
        return *this;
    }

    friend ostream& operator<<(ostream&, Persoana);
    friend istream& operator>>(istream&, Persoana&);

    virtual void spune_tip()
    {
        cout << endl
             << "Sunt o persoana";
    }
};

ostream& operator<<(ostream& out, Persoana persoana)
{
    out << endl
        << "----- Date personale ----- CNP: " << persoana.cnp << ", nume: ";
    if (persoana.nume != nullptr) {
        out << persoana.nume;
    } else {
        out << "-";
    }
    return out;
}

istream& operator>>(istream& in, Persoana& persoana)
{
    cout << endl
         << "Nume: ";
    char buffer[1000];
    in >> ws;
    in.getline(buffer, 1000);
    if (persoana.nume != nullptr) {
        delete[] persoana.nume;
    }
    persoana.nume = new char[strlen(buffer) + 1];
    strcpy(persoana.nume, buffer);
    cout << endl
         << "CNP: ";
    in >> persoana.cnp;
    return in;
}

// Student is a Persoana
class Student : public Persoana {
private:
    int id;

public:
    Student()
        : Persoana()
    {
        cout << endl
             << "[Constructor fara parametri student]";
        this->id
            = -1;
    }

    Student(const char* cnp, const char* nume, int id)
        : Persoana(cnp, nume)
    {
        cout << endl
             << "[Constructor cu toti parametrii student]";
        this->id = id;
    }

    Student(const Student& copie)
        : Persoana(copie)
    {
        cout << endl
             << "[Constructor de copiere student]";
        this->id = copie.id;
    }

    ~Student()
    {
        cout << endl
             << "[Destructor student]";
    }

    int get_id()
    {
        return this->id;
    }

    void set_id(int id_nou)
    {
        this->id = id_nou;
    }

    Student& operator=(const Student& student)
    {
        cout << endl
             << "[Operator= student]";
        Persoana::operator=(student);
        this->id = student.id;
        return *this;
    }

    friend ostream& operator<<(ostream&, Student);
    friend istream& operator>>(istream&, Student&);

    // overriding
    void spune_tip()
    {
        cout << endl
             << "Sunt un student";
    }
};

ostream& operator<<(ostream& out, Student student)
{
    out << (Persoana)student;
    out << ", id: " << student.id << endl;
    return out;
}

istream& operator>>(istream& in, Student& student)
{
    in >> (Persoana&)student;
    cout << "id: ";
    in >> student.id;
    return in;
}

int main()
{
    Persoana p1 = Persoana("1901010...", "Test");
    p1.spune_tip();
    //Persoana p2;
    //////p2 = p1;
    ////cin >> p2;
    //cout << p1 << p2;

    Student s1;
    s1.spune_tip();
    Student s2 = Student("190432432..", "Test", 90);
    //s1 = s2;
    //cin >> s1;
    cout << s1 << s2;

    Persoana* pp = &s2;
    Persoana* pp2 = &p1;
    //cout << pp->get_cnp();
    pp->spune_tip();
    pp2->spune_tip();
    return 0;
}

// tema:

// clasa Vehicul
// char denumire[50];
// bool necesita_inmatriculare;
// int viteza_maxima;

// class TrotinetaElectrica
// int autonomie;

// clasa Autoturism
// char* numar_inmatriculare;

// constructor fara param, cu toti params, de copiere, destructor
// getteri, setteri
// operator <<, >>, =
// testare in main
