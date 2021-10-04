#include <iostream>

using namespace std;

int main()
{
  int variable = 25;
  int *pointer = nullptr; // null pointer value; avoid using NULL or 0 as a null pointer constant;

  pointer = &variable; // '&' extracts the address of variabile

  // use dereference operator (*) to access the value of the referenced variable
  cout << "variable: " << variable << endl;
  cout << "*pointer: " << *pointer << endl;

  // address of 'variable'
  cout << "&variable: " << &variable << endl;
  cout << "pointer: " << pointer << endl;

  // you can mutate a variable via its pointer
  *pointer = 50;
  cout << "The value of the variable after mutation via pointer: " << variable << endl;

  // ########## arrays ##########
  const int VALUES_COUNT = 10;
  int *array;

  // allocation
  array = new int[VALUES_COUNT];
  cout << "The array was allocated \n";

  for (int i = 0; i < VALUES_COUNT; i++)
  {
    array[i] = i * 2;
  }

  cout << "Array values: ";
  for (int i = 0; i < VALUES_COUNT; i++)
  {
    // cout << array[i] << " ";
    cout << *(array + i) << " ";
  }
  cout << endl;

  // deallocation
  delete[] array;
  cout << "The array was deallocated \n";

  // ########## multi-dimensional arrays ##########

  const int MATRIX_SIZE = 3;
  int **matrix;
  matrix = new int *[MATRIX_SIZE];
  for (int i = 0; i < MATRIX_SIZE; i++)
  {
    matrix[i] = new int[MATRIX_SIZE];
  }

  for (int i = 0; i < MATRIX_SIZE; i++)
  {
    for (int j = 0; j < MATRIX_SIZE; j++)
    {
      if (i == j)
      {
        matrix[i][j] = 1;
      }
      else
      {
        matrix[i][j] = 0;
      }
    }
  }

  cout << "Matrix: \n";
  for (int i = 0; i < MATRIX_SIZE; i++)
  {
    for (int j = 0; j < MATRIX_SIZE; j++)
    {
      //cout << matrix[i][j] << " ";
      cout << *(*(matrix + i) + j) << " ";
    }
    cout << endl;
  }

  for (int i = 0; i < MATRIX_SIZE; i++)
  {
    delete[] matrix[i];
  }

  delete[] matrix;

  return 0;
}