/*
Kaylee Chan
2348244
kaychan@chapman.edu
CPSC 350-03
Assignment 5
*/
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include "Menu.h"


Menu::Menu() {
  // masterStudent = new BST<Student>();
  // masterFaculty = new BST<Faculty>();
}

Menu::~Menu() {

}

//display menu options to the user and user chooses
void Menu::menuOptions() {
  int option;
  bool running = true;

  while (running) {
    cout << "MENU  OPTIONS: Enter a number from 1-14 respectively " << endl;
    cout << "1. Print all students and their information (sorted by ascending id #) " << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #) " << endl;
    cout << "3. Find and display student information given the students id " << endl;
    cout << "4. Find and display faculty information given the faculty id " << endl;
    cout << "5. Given a student’s id, print the name and info of their faculty advisor " << endl;
    cout << "6. Given a faculty id, print ALL the names and info of his/her advisees. " << endl;
    cout << "7. Add a new student " << endl;
    cout << "8. Delete a student given the id " << endl;
    cout << "9. Add a new faculty member " << endl;
    cout << "10. Delete a faculty member given the id. " << endl;
    cout << "11. Change a student’s advisor given the student id and the new faculty id. " << endl;
    cout << "12. Remove an advisee from a faculty member given the ids " << endl;
    cout << "13. Rollback " << endl;
    cout << "14. Exit " << endl;
    cout << "Select a Menu Option: ";
    cin >> option;

    if(option == 1){
      printStudentsInOrder();
    }else if(option == 2){
      printFacultyInOrder();
    }else if(option == 3){
      displayStudent();
    }else if(option == 4){
      displayFaculty();
    }else if(option == 5){
      printAdvisor();
    }else if(option == 6){
      printAdvisees();
    }else if(option == 7){
      addStudent();
    }else if(option == 8){
      deleteStudent();
    }else if(option == 9){
      addFaculty();
    }else if(option == 10){
      deleteFaculty();
    }else if(option == 11){
      changeAdvisor();
    }else if(option == 12){
      removeAdvisee();
    }else if(option == 13){
      rollback();
    }else if(option == 14){
      exit();
      running = false;
    }else{
      cout << "Not an option. Try entering a number from 1-14! " << endl << endl;
    }
  }
}

//add student to database
void Menu::addStudent() {
  string name;
  string level;
  string major;
  double gpa;
  int advisorID;
  bool idexists = false;
  bool correctgpa = true;
  int max = 999;
  int min = 100;

  //generating random studentID ------ strictly is an integer from 100 to 999
  srand(time(NULL));
  int range = max - min + 1;
  int newID = rand() % range + min;

  while(idexists == false){
    if(masterStudent.searchNode(newID) == false){
      idexists = true;
    }
    else {
      int newID = rand() % range + min;
      idexists = false;
    }
  }

  cout << "\nStudent ID: " << newID << endl;
  cin.fail();
  cout << "Enter student's name: " ;
  cin.ignore();
  getline(cin, name);
  cout << "Enter student's level: ";
  cin >> level;
  cout << "Enter student's major: ";
  cin >> major;

  while(correctgpa) {
    cout << "Enter student's GPA: ";
    cin >> gpa;

    if(gpa <= 5 && gpa >= 0) {
      break;
      correctgpa = false;
    }else {
      cout << "\nERROR! Wrong GPA input. Enter a valid GPA from 0-5" << endl;
      correctgpa = true;
    }
  }

  if(!masterFaculty.isEmpty()) {
    cout << "Enter student's advisor ID: ";
    while(true) {
      cin >> advisorID;
      if(masterFaculty.searchNode(advisorID) || advisorID == -1) {
        Faculty *faculty = masterFaculty.search(advisorID);
        faculty->addAdvisee(newID);
        break;
      }else {
        cout << "\nThat faculty doesn't exist. " << endl;
        cout << "Please enter a new, valid advisor id: " << endl;
      }
    }
  }
  else {
    advisorID = -1;
  }

  Student *student = new Student(newID, name, level, major, gpa, advisorID);
  TreeNode<Student> *studentNode = new TreeNode<Student>(student, newID);
  masterStudent.put(studentNode);
  // Transaction<Student> *t = new Transaction<Student>(newID, "insert");
  // reverseStudent.push(*t);
}

//delete student
void Menu::deleteStudent() {
  int deleteSID;

  if(masterStudent.isEmpty()) {
    cout << "\nStudent database is empty. Nothing to delete! " << endl;
  }else {
    while(true) {
      cout << "Enter the student ID to be deleted: " << endl;
      cin >> deleteSID;
        if(masterStudent.searchNode(deleteSID)) {
          if(masterStudent.search(deleteSID)->getAdvisor() != -1) {
            masterFaculty.search(masterStudent.search(deleteSID)->getAdvisor())->removeAdvisee(deleteSID);
          }
          masterStudent.deleteNode(deleteSID);
          break;
        }
        else {
          cout << "The student ID doesnt exist " << endl;
        }
    }
  }
}

//checks for studentTable.txt and intializes tree accordingly
void Menu::readStudentFile() {
  ifstream MSFile;
  string s;
  int numStudent = 0;
  int numFaculty = 0;
  int totalFaculty = 0;
  int totalAdvisee = 0;
  int numLine = 1;
  int id = 0;
  string name = "";
  string level = "";
  string major = "";
  double gpa = 0;
  int advisorID = 0;

  MSFile.open("studentTable.txt");
  if(MSFile.is_open()) {
    //read all lines
    for(int i = 0; i < (7 * numStudent); ++i) {
      getline(MSFile, s);
      //read file and intialize database with information
      switch(numLine) {
        case 1: {
          if(s != "--") {
            cout << "\nIncorrect File Format" << endl;
          }
          break;
        }
        case 2: {
          cin >> id;
          if(cin.fail()){
            cout << "incorrect file" <<endl;
          }
          break;
        }
        case 3: {
          name = s;
          break;
        }
        case 4: {
          level = s;
          break;
        }
        case 5: {
          major = s;
        }
        case 6: {
          cin >> gpa;
          if(cin.fail()){
            cout << "incorrect file" << endl;
          }
          break;
        }
        case 7: {
            cin >> advisorID;
            if(cin.fail()){
              cout << "incorrect file" << endl;
            }else{
            Student *student = new Student(id, name, level, major, gpa, advisorID);
            TreeNode<Student> *studentNode = new TreeNode<Student>(student, id);
            masterStudent.put(studentNode);
          }
          break;
        }
        default:
          break;
      }
      ++numLine;
      //because it takes 7 lines to create one student, then go to next 7 lines
      if(numLine > 7) {
        numLine = 1;
      }
    }
  }else {
    cout << "\nNo 'studentTable.txt' found! Will start with empty database." << endl;
  }
  MSFile.close();
}

//checks for facultyTable.txt and intializes tree accordingly
void Menu::readFacultyFile(){
    ifstream MFFile;
    int id = 0;
    string name = "";
    string level = "";
    string department = "";
    int adviseeID = 0;
    string input;
    int numStudent = 0;
    int numFaculty = 0;
    int totalFaculty = 0;
    int totalAdvisee = 0;
    int numLine = 1;

    MFFile.open("facultyTable.txt");
    if(MFFile.is_open()) {
      try {
        getline(MFFile, input);

        if(input != "") {
          numFaculty = atoi(input.c_str());
        }
      }
      catch(exception e) {
        cout << "\nIncorrect File Format" << endl;
      }
      while(getline(MFFile, input)) {
        switch(numLine) {
          case 1: {
            if(input != "--") {
              cout << "\nIncorrect File Format" << endl;
            }
            break;
          }
          case 2: {
            cin >> id;
            if(cin.fail()){
              cout << "could not read id from file" << endl;
            }
            break;
          }
          case 3: {
            name = input;
            break;
          }
          case 4: {
            level = input;
            break;
          }
          case 5: {
            department = input;
            break;
          }
          case 6: {
            try {
              totalAdvisee = atoi(input.c_str());
            }
            catch(exception e) {
              cout << "\nIncorrect File Format" << endl;
            }

            Faculty *faculty = new Faculty(id, name, level, department);
            totalFaculty++;

            for(int j = 0; j < totalAdvisee; ++j) {
              getline(MFFile, input);
              try {
                adviseeID = atoi(input.c_str());
              }
              catch(exception e) {
                cout << "\nIncorrect File Format" << endl;
              }
              faculty->addAdvisee(adviseeID);
            }

            TreeNode<Faculty> *facultyNode = new TreeNode<Faculty>(faculty, id);
            masterFaculty.put(facultyNode);
            break;
          }
          default:
            break;
        }
        ++numLine;
        if(totalFaculty == numFaculty) {
          break;
        }
        if(numLine > 6) {
          numLine = 1;
        }
      }
    }else {
      cout << "\nNo 'facultyTable.txt' found! Will start with empty database." << endl;
    }
    MFFile.close();
}

//write files after done adding or deleting
void Menu::serializeFiles() {
  ofstream writeMS;
  ofstream writeMF;
  writeMS.open("studentTable.txt");
  if(writeMS.is_open()) {
    writeMS << masterStudent.getSize() << endl;
    TreeNode<Student> *s = masterStudent.getRoot();
    outputMS(s);
  }
  writeMS.close();
  writeMF.open("facultyTable.txt");
  if(writeMF.is_open()) {
    writeMF << masterFaculty.getSize() << endl;
    TreeNode<Faculty> *f = masterFaculty.getRoot();
    outputMF(f);
  }
  writeMF.close();
}

void Menu::printMS(TreeNode<Student> *s) {
  if(s != NULL) {
    if(s->left != NULL) {
      printMS(s->left);
    }
    s->data->printStudent();

    if(s->right != NULL) {
      printMS(s->right);
    }
  }else {
    cout << "Student database is empty. Nothing to print." << endl;
  }
}

void Menu::printMF(TreeNode<Faculty> *f) {
  if(f != NULL) {
    if(f->left != NULL) {
      printMF(f->left);
    }
    f->data->printFaculty();

    if(f->right != NULL) {
      printMF(f->right);
    }
  }else {
    cout << "Faculty database is empty. Nothing to print." << endl;
  }
}


void Menu::outputMS(TreeNode<Student> *s) {
  ofstream outFacFile;
  outFacFile.open("studentTable.txt");

  if(s != NULL) {
    outFacFile << "--" << endl;
    outFacFile << s->data->getID() << endl;
    outFacFile << s->data->getName() << endl;
    outFacFile << s->data->getLevel() << endl;
    outFacFile << s->data->getMajor() << endl;
    outFacFile << s->data->getGPA() << endl;
    outFacFile << s->data->getAdvisor() << endl;

    if(s->left != NULL) {
      outputMS(s->left);
    }

    if(s->right != NULL) {
      outputMS(s->right);
    }
  }else {
    cout << "Student Database is Empty" << endl;
  }

  outFacFile.close();
}

void Menu::outputMF(TreeNode<Faculty> *f) {
  ofstream outSFile;
  outSFile.open("facultyTable.txt");

  if(f != NULL) {
    outSFile << "--" << endl;
    outSFile << f->data->getID() << endl;
    outSFile << f->data->getName() << endl;
    outSFile << f->data->getLevel() << endl;
    outSFile << f->data->getDepartment() << endl;
    outSFile << f->data->getAdviseeID() << endl;

    if(f->data->getAdviseeID() > 0) {
      for(int i = 0; i < f->data->maxSize; ++i) {
        if(f->data->adviseeArray[i] != -1) {
          outSFile << f->data->adviseeArray[i] << endl;
        }
      }
    }

    if(f->left != NULL) {
      outputMF(f->left);
    }
    if(f->right != NULL) {
      outputMF(f->right);
    }
  }else {
    cout << "Faculty Database is Empty" << endl;
  }

  outSFile.close();
}

TreeNode<Student>* Menu::getMSRoot() {
  return masterStudent.getRoot();
}

TreeNode<Faculty>* Menu::getMFRoot() {
  return masterFaculty.getRoot();
}

//used recursive print function to print students from ascending order
void Menu::printStudentsInOrder() {
  if(masterStudent.isEmpty()) {
    cout << "\nStudent Database is Empty" << endl;
  }
  else {
    printMS(masterStudent.getRoot());
  }
}

//used recursive print function to print faculty from ascending order
void Menu::printFacultyInOrder() {
  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty Database is Empty" << endl;
  }
  else {
    printMF(masterFaculty.getRoot());
  }
}

//prints student to console given id
void Menu::displayStudent() {
  int id;
  if(masterStudent.isEmpty()) {
    cout << "\nStudent database is empty. Nothing to print." << endl;
  }else {
    while(true) {
      cout << "\nPlease Provide a Student ID: ";
      cin >> id;
      //check if student is in database
        if(masterStudent.searchNode(id)) {
          masterStudent.search(id)->printStudent();
          break;
        }else {
          cout << "\nThat student doesn't exist!" << endl;
        }
    }
  }
}

//prints faculty to console given id
void Menu::displayFaculty() {
  int id;
  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty database is empty. Nothing to print." << endl;
  }else {
    while(true) {
      cout << "\nPlease enter the faculty id to be displayed: ";
      cin >> id;
      //check if faculty is in database
        if(masterFaculty.searchNode(id)) {
          masterFaculty.search(id)->printFaculty();
          break;
        }else {
          cout << "\nThat faculty doesn't exist!" << endl;
        }
    }
  }
}

//print advisor given id of student
void Menu::printAdvisor() {
  int printingAd;
  if(masterStudent.isEmpty()) {
    cout << "\nStudent database is empty. Nothing to print." << endl;
  }else {
    while(true) {
      cout << "\nEnter the student id for which you'd like to see the advisor of: ";
      cin >> printingAd;
        if(masterStudent.searchNode(printingAd)) {
          Student *student = masterStudent.search(printingAd);
          masterFaculty.search(student->getAdvisor())->printFaculty();
          break;
        }else {
          cout << "\nThat student doesn't exist!" << endl;
        }
    }
  }
}

//print list of advisees given faculty id
void Menu::printAdvisees(){
  int showadvisee;
  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty database is empty. Nothing to print." << endl;
  }else {
    while(true) {
      cout << "\nEnter the faculty id for which you'd like to see the advisees: ";
      cin >> showadvisee;
      //make sure that faculty is in database
        if(masterFaculty.searchNode(showadvisee)) {
          Faculty *faculty = masterFaculty.search(showadvisee);
          for(int i = 0; i < faculty->getSizeArray(); ++i) {
            if(faculty->adviseeArray[i] != -1) {
              masterStudent.search(faculty->adviseeArray[i])->printStudent();
              break;
            }else {
              cout << "\nFaculty currently has no advisees!" << endl;
            }
          }
          break;
        }else {
          cout << "\nThat faculty doesn't exist!" << endl;
        }
    }
  }
}


void Menu::addFaculty() {
  int numAdvisees = 0;
  string name;
  string level;
  string department;
  int sID = 0;
  int max = 5000;
  int min = 1000;
  bool idexists = false;

  srand(time(NULL));
  int range = max - min + 1;
  int fID = rand() % range + min; //randomly generated facultyId ------ strictly is an integer from 1000 to 5000

  while(idexists == false){
    if(masterFaculty.searchNode(fID) == false){
      idexists = true;
    }
    else {
      int fID = rand() % range + min;
      idexists = false;
    }
  }

  cout << "Faculty ID: " << fID << endl;
  cin.clear();
  cout << "Enter faculty's name: ";
  cin.ignore();
  getline(cin, name);
  cout << "Enter faaculty's level: ";
  cin >> level;
  cout << "Enter faculty's department: ";
  cin >> department;
  Faculty *faculty = new Faculty(fID, name, level, department);

  if(!masterStudent.isEmpty()) {
    cout << "Enter number of advisees that the new faculty has: " << endl;
    while(true) {
      cin >> numAdvisees;
      if(numAdvisees > -1){
        break;
      }else{
        cout << "ERROR: invalid number of advisees. Please enter a number >0 " << endl;
      }
    }
    //for the given number of inputted advisees by the user
    //it will loop that many times and ask user to input advisees
    for(int i = 0; i < numAdvisees; ++i) {
      while(true) {
        cout << "Provide student id: " << endl;
        cin >> sID;
          if(masterStudent.searchNode(sID)) {
            faculty->addAdvisee(sID);
            masterStudent.search(sID)->setAdvisor(fID);
            --numAdvisees;
            break;
          }else {
            cout << "That student doesn't exist" << endl;
          }
      }
    }
  }

  TreeNode<Faculty> *fNode = new TreeNode<Faculty>(faculty, fID);
  masterFaculty.put(fNode);
}

//delete faculty member in database
void Menu::deleteFaculty() {
  int deleteID = 0;
  int transferID = 0;

  //check if faculty database is empty
  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty database is empty. Nothing to delete!" << endl;
  }else {
    while(true) {
      cout << "\nPlease provide ID of faculty to be deleted: ";
      cin >> deleteID;
      //check if faculty exists in database
        if(masterFaculty.searchNode(deleteID)) {
          //check if the number of advisees that the faculty has is >0
          if(masterFaculty.search(deleteID)->numAdvisee > 0) {
            while(true) {
              //following referential integrity!
              //transfer advisees first so that they still have an advisor
              cout << "\nEnter faculty ID to move advisee to: ";
              cin >> transferID;
              //transfer advisee
                if(masterFaculty.searchNode(transferID)) {
                  for(int i = 0; i < masterFaculty.search(deleteID)->maxSize; ++i) {
                    //make sure that faculty has an advisee
                    if(masterFaculty.search(deleteID)->adviseeArray[i] != -1) {
                      masterStudent.search(masterFaculty.search(deleteID)->adviseeArray[i])->setAdvisor(transferID);
                    }
                  }
                }else {
                  cout << "\nThat faculty doesn't exist." << endl;
                }
                break;
            }
          }else{
            //proceed to delete faculty
            masterFaculty.deleteNode(deleteID);
            break;
          }
        }else{
          cout << "\nThat faculty doesn't exist." << endl;
        }
      break;
    }
  }
}

//change student's advisor
void Menu::changeAdvisor() {
  int toNewAdvisor = 0;
  int changetofaculty = 0;

  //output message is database is empty
  if(masterFaculty.isEmpty() || masterStudent.isEmpty()) {
    cout << "\nEither Studnet or Faculty database is empty. Nothing to change" << endl;
  }else {
    while(true) {
      cout << "\nTo change advisor, please enter the student ID: ";
      cin >> toNewAdvisor;

      //check if student is in database
        if(masterStudent.searchNode(toNewAdvisor)) {
          while(true) {
            cout << "\nPlease Provide a Faculty ID: ";
            cin >> changetofaculty;
            //check if the provided faculty id is in databse
              if(masterFaculty.searchNode(changetofaculty)) {
                break;
              } else {
                cout << "\nERROR: That faculty doesn't exist!" << endl;
              }
          }
          break;
        }else {
          cout << "\nERROr: That student doesn't exist! " << endl;
        }
    }
    masterStudent.search(toNewAdvisor)->setAdvisor(changetofaculty);
    masterFaculty.search(changetofaculty)->addAdvisee(toNewAdvisor);
  }
}

//used to remove advisee
void Menu::removeAdvisee() {
  int thefaculty = 0;
  int removingAdvisee = 0;

  if(masterFaculty.isEmpty() || masterStudent.isEmpty()) {
    cout << "\nStudent and/or Faculty Database is Empty" << endl;
  }else {
    while(true) { //if database isn't empty then proceed
      cout << "\nPlease Provide a Faculty ID: ";
      cin >> thefaculty;

      //check is faculty id is in databse
        if(masterFaculty.searchNode(thefaculty)) {
          while(true) {
            cout << "\nPlease Provide a Student ID: ";
            cin >> removingAdvisee;
            //check if advisee is a real student in the database
              if(masterStudent.searchNode(removingAdvisee)) {
                break;
              }else {
                cout << "\nERROR: That student doesn't exist! " << endl;
              }
          }
          break;
        }else {
          cout << "\nERROR: That faculty doesn't exist!" << endl;
        }
    }

    if(masterFaculty.search(thefaculty)->removeAdvisee(removingAdvisee)) {
      masterStudent.search(removingAdvisee)->setAdvisor(-1);
    }
    char c;
    cout << "\nWoudld you like the advisee to have a new advisor? (y/n) ";
    cin >> c;

    if(c == 'Y' || c == 'y') {
      while(true) {
        cout << "Please Provide a Faculty ID: ";
        cin >> thefaculty;

          if(masterFaculty.searchNode(thefaculty)) {
            break;
          }else {
            cout << "\nERROR: That faculty doesn't exist!" << endl;
          }
      }
      masterStudent.search(removingAdvisee)->setAdvisor(thefaculty);
    }
  }
}

void Menu::rollback() {
//rollback implementation doesn't work :'(
}

//exit program and output message to user
void Menu::exit() {
  cout << "*******Exiting program*******" << endl;
}
