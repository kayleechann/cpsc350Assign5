/*
Kaylee Chan
2348244
kaychan@chapman.edu
CPSC 350-03
Assignment 5
*/
#include "Student.h"

Student::Student(){
  // id = 0;
  // name = "";
  // level = "";
  // major = "";
  // gpa = 0.0;
  // advisor = 0;
}

Student::~Student(){
  //
}

Student::Student(int sID, string sName, string sLevel, string sMajor, double sGPA, int sAdvisor){
  id = sID;
  name = sName;
  level = sLevel;
  major = sMajor;
  gpa = sGPA;
  advisor = sAdvisor;
}

int Student::getID(){
  return id;
}
// void setID(int newID);
string Student::getName(){
  return name;
}
string Student::getLevel(){
  return level;
}

string Student::getMajor(){
  return major;
}

double Student::getGPA(){
  return gpa;
}

int Student::getAdvisor(){
  return advisor;
}

void Student::setAdvisor(int newAdvisor){
  advisor = newAdvisor;
}

int Student::compareGradeLevel(string otherStudent){ //returns 1 is student being compared is older,  -1 is the student "to be compared" is older, 0 if equal
  if(level == ""){
    return -2;
  }else if(otherStudent == level){
    return 0;
  }else if(otherStudent == "Freshman"){
      return 1;
  }else if(otherStudent == "Senior"){
      return -1;
  }else if(otherStudent == "Junior"){
    if(level == "Senior"){
      return 1;
    }else{
      return -1;
    }
  }else if(otherStudent == "Sophomore"){
    if(level == "Freshman"){
      return -1;
    }else{
      return 1;
    }
  }else{
    cout << "ERROR: Invalid string" << endl;
    return -1;
  }
}

void Student::printStudent(){
  cout << "Student ID: " << id << endl;
  cout << "Name: " << name << endl;
  cout << "Level: " << level << endl;
  cout << "Major: " << major << endl;
  cout << "GPA: " << gpa << endl;
  cout << "Advisor: " << advisor << endl;
}
