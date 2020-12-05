/*
Kaylee Chan
2348244
kaychan@chapman.edu
CPSC 350-03
Assignment 5
*/
#include "Faculty.h"

Faculty::Faculty(){
  // id = 0;
  // name = "";
  // level = "";
  // department = "";
  // advisees = new SinglyLinkedList<int>();
}

Faculty::~Faculty(){
  delete []adviseeArray;
}

Faculty::Faculty(int fID, string fName, string fLevel, string fDepartment){
  id = fID;
  name = fName;
  level = fLevel;
  department = fDepartment;
  //advisees = new SinglyLinkedList<int>();

  adviseeArray = new int[5];
  numAdvisee = 0;
  maxSize = 5;

  for(int i = 0; i < 5; ++i){
    adviseeArray[i] = -1;
  }
}

int Faculty::getID(){
  return id;
}

string Faculty::getName(){
  return name;
}

string Faculty::getLevel(){
  return level;
}

string Faculty::getDepartment(){
  return department;
}

void Faculty::setDepartment(string newDeparment){
  department = newDeparment;
}

void Faculty::printFaculty(){
  cout << "Faculty id: " << id << endl;
  cout << "Name: " << name << endl;
  cout << "Level: " << level << endl;
  cout << "Department: " << department << endl;
  cout << "List of Advisees: "<< endl;
  //advisees->printList();
  printAdvisee();
}

void Faculty::printAdvisee(){
  if(numAdvisee == 0){
    cout << "No advisees" << endl;
  }else{
    for(int i = 0; i < maxSize; ++i){
      if(adviseeArray[i] != -1){
        cout << adviseeArray[i];
        if(i < numAdvisee - 1){
          cout << ", ";
        }
      }
    }
  }
  cout << endl;
}

int Faculty::getAdviseeID(){
  return numAdvisee;
}

void Faculty::addAdvisee(int ID){
  //advisees->insertBack(ID);
  if(numAdvisee != maxSize){
    int temp = 0;

    for(int i = 0; i < maxSize; ++i){
      if(adviseeArray[i]== ID){
        temp = maxSize;
      }
    }

    while(temp < maxSize){
      if(adviseeArray[temp] == -1){
        adviseeArray[temp] = ID;
        ++numAdvisee;
        break;
      }
      ++temp;
    }
  }else {
    if(numAdvisee == maxSize) {
      int *tempArray = new int[numAdvisee];
      for(int i = 0; i < numAdvisee; ++i) {
        tempArray[i] = adviseeArray[i];
      }

      adviseeArray = new int[numAdvisee + 1];
      maxSize = numAdvisee + 1;

      for(int i = 0; i < numAdvisee; ++i) {
        adviseeArray[i] = tempArray[i];
      }

      for(int i = numAdvisee; i < numAdvisee + 1; ++i) {
        adviseeArray[i] = -1;
      }
      adviseeArray[++numAdvisee] = ID;
    }
  }
}

bool Faculty::removeAdvisee(int adviseeID){
  //advisees->deletePos(adviseeID);
  bool removed = false;

  for(int i = 0; i < maxSize; ++i) {
    if(adviseeArray[i] == adviseeID) {
      adviseeArray[i] = -1;
      --numAdvisee;
      removed = true;
    }
    if(!removed) {
      cout << "Advisee removed" << endl;
    }
    return removed;
  }
}

int Faculty::getSizeArray() {
  return maxSize;
}
