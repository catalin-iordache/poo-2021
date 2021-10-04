#include <string>
#include <iostream>

using namespace std;

//typedef struct {
//	string nume;
//	int id;
//	float medie;
//} Student;

//struct {
//	string nume;
//	int id;
//	float medie;
//} student1 = {"Ion Popescu", 105, 9.32}

struct Student
{
  string nume;
  int id;
  float medie;
};

void afisare_student(Student student)
{
  cout << "Nume: " << student.nume << "; Id: " << student.id << "; Medie: " << student.medie << endl;
}

int main()
{

  Student student1 = {"Ion Popescu", 105, 9.32};

  // cout << "Nume: " << student1.nume << "; Id: " << student1.id << "; Medie: " << student1.medie;
  afisare_student(student1);

  Student *pointer_student = &student1;

  // cout << "Nume pointer: " << (*pointer_student).nume << endl;
  cout << "Nume pointer: " << pointer_student->nume << endl;
}