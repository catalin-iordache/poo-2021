#include <iostream>
#include <string>

using namespace std;

int main()
{
  std::cout << "Hello, world!\n";
  cout << "Hello again!" << endl;

  // single line comment
  /*
   multiline comment
   */

  // types
  int integer = 10;
  float float_number_1 = 9.73;
  double float_number_2 = 9.72964;
  char letter = 'a';
  letter = 97; // 97 <-> 'a' in ASCII
  cout << "Letter: " << letter << endl;
  string text = "Hello, world";
  bool boolean = true;

  int x = 5, y = 6, z = 7;

  // sizeof(x) - get the size in bytes of a variable
  cout << "sizeof(integer): " << sizeof(integer) << endl;
  cout << "sizeof(float_number_1): " << sizeof(float_number_1) << endl;
  cout << "sizeof(float_number_2): " << sizeof(float_number_2) << endl;
  cout << "sizeof(letter): " << sizeof(letter) << endl;

  // naming conventions: case sensitive, no whitespaces, no special characters, etc.

  const double PI = 3.14;
  // PI = 4; // generates error, PI is declared as a constant

  // get the input from the standard input device
  int input_integer;
  cout << "Type an integer: ";
  cin >> input_integer;
  cout << "You typed " << input_integer << endl;

  // strings - you have to #include<string>
  string input_string;
  cout << "Type a text: ";
  cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear all characters from input buffer
  // cin >> input_string; // it skips all whitespace (spaces, tabs, new lines, etc.)
  getline(cin, input_string); // will stop retrieving chars from the stream if it finds a newline char (\n)
  cout << "You typed \"" << input_string + "\"" << endl;

  return 0;
}
