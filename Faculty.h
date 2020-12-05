#include <iostream>
#include "SinglyLinkedList.h"
using namespace std;

class Faculty{
public:
  int id;
  string name;
  string level;
  string department;
  SinglyLinkedList<int> *advisees;
  int *adviseeArray;
  unsigned int numAdvisee;
  unsigned int maxSize;

  Faculty();
  ~Faculty();
  Faculty(int fID, string fName, string fLevel, string fDepartment);
  int getID();
  string getName();
  string getLevel();
  string getDepartment();
  void setDepartment(string newDeparment);

  void printFaculty();
  void printAdvisee();
  int getAdviseeID();
  void addAdvisee(int ID);
  bool removeAdvisee(int adviseeID);
  int getSizeArray();

};
