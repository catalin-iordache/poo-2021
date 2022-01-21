#include <iostream>
#include <string>

using namespace std;

#pragma warning(disabled : 4996)

template <typename T>
bool egal(T first, T second)
{
    return first == second;
}

template <typename T>
T scadere(T first, T second)
{
    return first - second;
}

// exercitii seminar

enum TipBursa {
    PERFORMANTA = 1,
    MERIT,
    SOCIALA
};

template <typename T>
class Bursa {
    TipBursa tip;
    int nr_persoane;
    T* persoane = nullptr;

    // constructor fara param, cu param, de copiere, destructor, operator=, operator<< consola
};

class Student {
    char* nume = nullptr;
    int id;

    // constructor fara param, cu param, de copiere, destructor, operator=, operator<< consola
};

// optional

class Elev {
    string nume;
    int nr_matricol;
};

int main()
{
    int a = 5;
    int b = 6;
    if (egal<int>(a, b) == true) {
        cout << "a si b sunt egale" << endl;
    } else {
        cout << "a este diferit de b" << endl;
    }

    string x = "test";
    string y = "test1";
    if (egal<string>(x, y) == true) {
        cout << "x si y sunt acelasi string" << endl;
    } else {
        cout << "x este un string diferit de y" << endl;
    }

    float f1 = 9.5;
    float f2 = 5;
    cout << "Rezultatul scaderii a doua valori de tip float este " << scadere<float>(f1, f2) << endl;

    //Bursa<Student> bursa = Bursa();

    return 0;
}