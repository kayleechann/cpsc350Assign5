/*
Kaylee Chan
2348244
kaychan@chapman.edu
CPSC 350-03
Assignment 5
*/
#include "Menu.h"
using namespace std;

int main(int argc, char** argv) {
  Menu m;

  m.readStudentFile();
  m.readFacultyFile();
  m.menuOptions();
  m.serializeFiles();

  return 0;
}
