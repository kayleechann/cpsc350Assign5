/*
Kaylee Chan
2348244
kaychan@chapman.edu
CPSC 350-03
Assignment 5
*/
#include <iostream>
using namespace std;

class Student{
public:
  int id;
  string name;
  string level;
  string major;
  double gpa;
  int advisor;

  Student();
  ~Student();
  Student(int sID, string sName, string sLevel, string sMajor, double sGPA, int sAdvisor);
  int getID();
  // void setID(int newID);
  string getName();
  string getLevel();
  string getMajor();
  double getGPA();
  int getAdvisor();
  void setAdvisor(int newAdvisor);
  void printStudent();

  int compareGradeLevel(string otherStudent);
};
