#include <iostream>
#include <string>

using namespace std;

#pragma warning(disable : 4996)

class Student {
    char nume[50];
    int nr_note = 0;
    int* note = nullptr;
    bool este_bursier = false;

    static int nr_burse;

public:
    // constructor fara parametri
    Student()
    {
        strcpy(this->nume, "Anonim");
    }

    // constructor cu 1 parametru
    Student(const char* nume)
    {
        strcpy(this->nume, nume);
    }

    // constructor cu toti parametrii
    Student(const char* nume, int nr_note, int* note, bool este_bursier)
    {
        strcpy(this->nume, nume);
        this->nr_note = nr_note;
        if (nr_note > 0) {
            this->note = new int[nr_note];
            for (int i = 0; i < nr_note; i++) {
                this->note[i] = note[i];
            }
        }
        this->este_bursier = este_bursier;
        if (este_bursier) {
            nr_burse++;
        }
    }

    // constructor de copiere
    Student(const Student& copie)
    {
        strcpy(this->nume, copie.nume);
        this->nr_note = copie.nr_note;
        if (copie.nr_note > 0) {
            this->note = new int[copie.nr_note];
            for (int i = 0; i < copie.nr_note; i++) {
                this->note[i] = copie.note[i];
            }
        }
        this->este_bursier = copie.este_bursier;
        if (copie.este_bursier) {
            nr_burse++;
        }
    }

    // destructor
    ~Student()
    {
        if (this->note != nullptr) {
            delete[] this->note;
        }
        if (this->este_bursier) {
            nr_burse--;
        }
    }

    // metoda statica "getter"
    static int get_nr_burse()
    {
        return nr_burse;
    }

    // supraincarcarea operatorului de atribuire
    Student& operator=(const Student& student)
    {
        strcpy(this->nume, student.nume);
        this->nr_note = student.nr_note;
        if (this->note != nullptr) {
            delete[] this->note;
        }
        if (student.nr_note > 0) {
            this->note = new int[student.nr_note];
            for (int i = 0; i < student.nr_note; i++) {
                this->note[i] = student.note[i];
            }
        } else {
            this->note = nullptr;
        }
        if (!this->este_bursier && student.este_bursier) {
            nr_burse++;
        } else if (this->este_bursier && !student.este_bursier) {
            nr_burse--;
        }
        this->este_bursier = student.este_bursier;

        return *this;
    }

    // supraincarcare operator <<
    friend ostream& operator<<(ostream& out, Student student);

    // supraincarcare operator + (Student + int)
    Student operator+(int nota_noua)
    {
        Student copie = *this;
        if (copie.nr_note > 0) {
            int* note_buffer = new int[copie.nr_note + 1];
            for (int i = 0; i < copie.nr_note; i++) {
                note_buffer[i] = copie.note[i];
            }
            note_buffer[copie.nr_note] = nota_noua;
            delete[] copie.note;
            copie.note = note_buffer;
            copie.nr_note++;
        } else {
            copie.note = new int[1];
            copie.note[0] = nota_noua;
            copie.nr_note = 1;
        }
        return copie;
    }

    // supraincarcare operator + (int + Student)
    friend Student operator+(int nota_noua, Student& student);

    // preincrementare (alegem sa acordam bursa unui student)
    Student& operator++()
    {
        if (!this->este_bursier) {
            nr_burse++;
        }
        this->este_bursier = true;
        return *this;
    }

    // postincrementare (alegem sa acordam bursa unui student)
    Student operator++(int)
    {
        Student copie = *this;
        if (!this->este_bursier) {
            nr_burse++;
        }
        this->este_bursier = true;
        return copie;
    }
};

ostream& operator<<(ostream& out, Student student)
{
    out << endl
        << "Student: " << student.nume << ", ";
    if (student.este_bursier) {
        out << "bursier, ";
    }
    if (student.nr_note > 0) {
        out << "note: ";
        for (int i = 0; i < student.nr_note; i++) {
            out << student.note[i] << " ";
        }
    } else {
        out << "fara note";
    }
    return out;
}

Student operator+(int nota_noua, Student& student)
{
    Student copie = student;
    if (copie.nr_note > 0) {
        int* note_buffer = new int[copie.nr_note + 1];
        for (int i = 0; i < copie.nr_note; i++) {
            note_buffer[i] = copie.note[i];
        }
        note_buffer[copie.nr_note] = nota_noua;
        delete[] copie.note;
        copie.note = note_buffer;
        copie.nr_note++;
    } else {
        copie.note = new int[1];
        copie.note[0] = nota_noua;
        copie.nr_note = 1;
    }
    return copie;
}

int Student::nr_burse = 0;

int main()
{
    int note_s1[3] = { 10,
        9,
        10 };
    Student s1 = Student("Ion Popescu", 3, note_s1, true);
    cout << endl
         << "s1: " << s1;
    Student s2 = Student("Andrei George");
    Student s3 = s2 + 10;
    cout << endl
         << "s2: " << s2; // notele lui s2 raman nemodificate
    cout << endl
         << "s3: " << s3;

    cout << endl
         << "Nr burse: " << Student::get_nr_burse();

    s1 = s1 + 8;
    s1 = 10 + s1;
    cout << endl
         << "s1: " << s1; // s-au adaugat notele 8 si 10

    cout << endl
         << "s2++: " << s2++;
    cout << endl
         << "s2: " << s2;

    Student s4;
    s4 = s2;
    cout << endl
         << "s4 (dupa executia operatorului de atribuire): " << s4;

    cout << endl;
    return 0;
}

// exercitiu
class Cladire {
    char* adresa;
    float suprafata;
    int pret;
    const int id;
};

// constructori fara parametri, cu 2 parametri, cu toti parametrii, de copiere, destructor
// operator=
// operator<<
// operator- (scade pretul) - ambele variante
// operator++ (preincrementare, postincrementare a pretului cu 100)
