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
