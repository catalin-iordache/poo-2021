#include <iostream>
#include <string>

using namespace std;

class NumeClasa {
    // date/atribute
    // functii
};

/*
  clasa - implementeaza un concept abstract
  obiect - manifestarea concretă a clasei, se obține prin instanțiere
*/

// gruparea membrilor clasei după dreptul de acces: private, protected, public

/* tipuri de funcții într-o clasă
    1. constructor
    2. destructor
    3. funcții de acces
    4. metode
*/

class Student {
    int id = -1;
    float medie = 0;
    string nume = "Nedefinit";

public:
    Student()
    {
        cout << "Apel constructor fara parametri" << endl;
        // nume = "Nedefinit";
        // id = -1;
        // medie = 0;
    }

    Student(int id); // corpul funcției este definit în afara clasei

    Student(string _nume)
    {
        cout << "Apel constructor cu 1 parametru" << endl;
        nume = _nume;
    }

    // definire recomandată a unui constructor, folosind pointerul this
    // this este adresa obiectului pentru care se apelează funcția
    Student(string nume, int id, float medie)
    {
        cout << "Apel constructor cu 3 parametri" << endl;
        this->nume = nume;
        this->id = id;
        this->medie = medie;
    }

    ~Student()
    {
        cout << "Destructor;" << endl;
    }

    // nerecomandat, exemplu strict didactic:
    //void intializare(string _nume, int _id, float _medie)
    //{
    //    nume = _nume;
    //    id = _id;
    //    medie = _medie;
    //}

    void afisare(int tipAfisare)
    {
        if (tipAfisare == 1) {
            cout << "Student: " << this->nume << ", id: " << this->id << ", medie: " << (*this).medie << endl;
        } else {
            cout << this->nume << ", "
                 << this->medie << endl;
        }
    }

    void afisare_secundara(); // corpul funcției este definit în afara clasei
};

Student::Student(int id)
{
    this->id = id;
}

void Student::afisare_secundara()
{
    cout << "Afisare secundara id: " << this->id << endl;
}

int main()
{
    Student s1; // instanțierea unui obiect de tip Student, apelând implicit constructorul fără parametri
    // s1.intializare("Ion Popescu", 100, 9.30); // a nu se folosi în practică
    s1.afisare(1);

    Student s2 = Student("Ion Popescu", 100, 9.3); // constructorul cu 3 parametri
    s2.afisare(1);

    Student s3 = Student("Ion Popescu"); // constructorul cu 1 parametru
    s3.afisare(0);

    Student s4 = Student(500);
    s4.afisare(1);
    s4.afisare_secundara();

    // destructorul se apelează în acest caz pentru fiecare obiect instanțiat, la sfârșitul programului
    return 0;
}

// exercitiu:

// class Angajat {
//     string nume = "";
//     int* vanzari_lunare = nullptr;
//     int numar_luni = 0;
// };

// constructor cu si fara params
// metoda de afisare angajat
// destructor
// metoda de afisare a mediei vanzarilor pentru un angajat
