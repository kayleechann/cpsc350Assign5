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

//print the menu to the user and sends them to the option they choose
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
    cout << "\nPlease Select a Menu Option: ";
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

void Menu::readStudentFile() {
  ifstream MSFile;
  string s;
  int numStudent = 0;
  int numFaculty = 0;
  int totalFaculty = 0;
  int totalAdvisee = 0;
  int numLine = 1;

  int srID = 0;
  string sname = "";
  string slevel = "";
  string smajor = "";
  double gpa = 0;
  int advisorID = 0;

  MSFile.open("studentTable.txt");
  if(MSFile.is_open()) {
    // try {
    //   getline(MSFile, input);
    //
    //   if(input != "") {
    //     numStudent = atoi(input.c_str());
    //   }
    // }
    // catch(exception e) {
    //   cout << "\nIncorrect File Format" << endl;
    // }
    for(int i = 0; i < (7 * numStudent); ++i) {
      getline(MSFile, s);
      switch(numLine) {
        case 1: {
          if(s != "--") {
            cout << "\nIncorrect File Format" << endl;
          }
          break;
        }
        case 2: {
          try {
            srID = atoi(s.c_str());
          }
          catch(exception e) {
            cout << "\nIncorrect File Format" << endl;
          }
          break;
        }
        case 3: {
          sname = s;
          break;
        }
        case 4: {
          slevel = s;
          break;
        }
        case 5: {
          smajor = s;
        }
        case 6: {
          try {
            gpa = atof(s.c_str());
          }
          catch(exception e) {
            cout << "\nIncorrect File Format" << endl;
          }
          break;
        }
        case 7: {
          try {
            advisorID = atoi(s.c_str());

            Student *student = new Student(srID, sname, slevel, smajor, gpa, advisorID);
            TreeNode<Student> *studentNode = new TreeNode<Student>(student, srID);
            masterStudent.put(studentNode);
          }
          catch(exception e) {
            cout << "\nIncorrect File Format" << endl;
          }
          break;
        }
        default:
          break;
      }

      ++numLine;
      if(numLine > 7) {
        numLine = 1;
      }
    }
  } else {
    cout << "\nNo 'studentTable.txt' found! Will start with empty database." << endl;
  }

  MSFile.close();
}

void Menu::readFacultyFile(){
    ifstream MFFile;
    //Faculty
    int frID = 0;
    string fname = "";
    string flevel = "";
    string department = "";
    int adviseeID = 0;
    string input;
    int numStudent = 0;
    int numFaculty = 0;
    int totalFaculty = 0;
    int totalAdvisee = 0;
    int numLine = 1;

    //Faculty Import
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

      //Reads the imported file and distributes the lines to their correct variables
      while(getline(MFFile, input)) {
        switch(numLine) {
          case 1: {
            if(input != "--") {
              cout << "\nIncorrect File Format" << endl;
            }
            break;
          }
          case 2: {
            try {
              frID = atoi(input.c_str());
            }
            catch(exception e) {
              cout << "\nIncorrect File Format" << endl;
            }
            break;
          }
          case 3: {
            fname = input;
            break;
          }
          case 4: {
            flevel = input;
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

            Faculty *faculty = new Faculty(frID, fname, flevel, department);
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

            TreeNode<Faculty> *facultyNode = new TreeNode<Faculty>(faculty, frID);
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

void Menu::serializeFiles() {
  ofstream writeMS;
  ofstream writeMF;

  //Student
  writeMS.open("studentTable.txt");
  if(writeMS.is_open()) {
    writeMS << masterStudent.getSize() << endl;
    TreeNode<Student> *s = masterStudent.getRoot();
    outputMS(s);
  }

  writeMS.close();

  //Faculty
  writeMF.open("facultyTable.txt");
  if(writeMF.is_open()) {
    writeMF << masterFaculty.getSize() << endl;
    TreeNode<Faculty> *f = masterFaculty.getRoot();
    outputMF(f);
  }

  writeMF.close();
}

//traverses the tree to print the students
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

//traveses the tree to print the faculty
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

//outputs the students to the file to be used when opening the program again
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

//outputs the faculty to the file to be used when opening the program again
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


//go through the tree printing all the students IN ORDER
void Menu::printStudentsInOrder() {
  if(masterStudent.isEmpty()) {
    cout << "\nStudent Database is Empty" << endl;
  }
  else {
    printMS(masterStudent.getRoot());
  }
}

//go through the tree printing all the faculty IN ORDER
void Menu::printFacultyInOrder() {
  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty Database is Empty" << endl;
  }
  else {
    printMF(masterFaculty.getRoot());
  }
}

void Menu::displayStudent() {
  int id;
  if(masterStudent.isEmpty()) {
    cout << "\nStudent database is empty. Nothing to print." << endl;
  }else {
    while(true) {
      cout << "\nPlease Provide a Student ID: ";
      cin >> id;
        if(masterStudent.contains(id)) {
          masterStudent.find(id)->printStudent();
          break;
        }else {
          cout << "\nThat student doesn't exist!" << endl;
        }
    }
  }
}

//Prints a single faculty member and their information that the user chooses
void Menu::displayFaculty() {
  int id;
  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty database is empty. Nothing to print." << endl;
  }else {
    while(true) {
      cout << "\nPlease enter the faculty id to be displayed: ";
      cin >> id;
        if(masterFaculty.contains(id)) {
          masterFaculty.find(id)->printFaculty();
          break;
        }else {
          cout << "\nThat faculty doesn't exist!" << endl;
        }
    }
  }
}

//prints an advisor given a student ID number from the user
void Menu::printAdvisor() {
  int printingAd;
  if(masterStudent.isEmpty()) {
    cout << "\nStudent database is empty. Nothing to print." << endl;
  }else {
    while(true) {
      cout << "\nEnter the student id for which you'd like to see the advisor of: ";
      cin >> printingAd;
        if(masterStudent.contains(printingAd)) {
          Student *student = masterStudent.find(printingAd);
          masterFaculty.find(student->getAdvisor())->printFaculty();
          break;
        }else {
          cout << "\nThat student doesn't exist!" << endl;
        }
    }
  }
}

//prints an advisee information given the faculty ID user provides
void Menu::printAdvisees(){
  int showadvisee;
  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty database is empty. Nothing to print." << endl;
  }else {
    while(true) {
      cout << "\nEnter the faculty id for which you'd like to see the advisees: ";
      cin >> showadvisee;

        if(masterFaculty.contains(showadvisee)) {
          Faculty *faculty = masterFaculty.find(showadvisee);
          for(int i = 0; i < faculty->getSizeArray(); ++i) {
            if(faculty->adviseeArray[i] != -1) {
              masterStudent.find(faculty->adviseeArray[i])->printStudent();
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

//allows the user to add a student to the records
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

  //studentID (integer from 100 to 999)
  srand(time(NULL));
  int range = max - min + 1;
  int newID = rand() % range + min;

  while(idexists == false){
    if(masterStudent.contains(newID) == false){
      idexists = true;
    }
    else {
      int newID = rand() % range + min;
      idexists = false;
    }
  }

  cout << "\nStudnet ID: " << newID << endl;
  cin.fail();
  cout << "Enter student's  name: " ;
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
      if(masterFaculty.contains(advisorID) || advisorID == -1) {
        Faculty *faculty = masterFaculty.find(advisorID);
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
}

//allows the user to input a student ID number and delete that student from the records
void Menu::deleteStudent() {
  int deleteSID;

  if(masterStudent.isEmpty()) {
    cout << "\nStudent database is empty. Nothing to delete! " << endl;
  }else {
    while(true) {
      cout << "Enter the student ID to be deleted: " << endl;
      cin >> deleteSID;
        if(masterStudent.contains(deleteSID)) {
          if(masterStudent.find(deleteSID)->getAdvisor() != -1) {
            masterFaculty.find(masterStudent.find(deleteSID)->getAdvisor())->removeAdvisee(deleteSID);
          }
          masterStudent.erase(deleteSID);
          break;
        }
        else {
          cout << "The student ID doesnt exist " << endl;
        }
    }
  }
}

//allows the user to add a faculty member to the records
void Menu::addFaculty() {
  int numAdvisees = 0;
  string name;
  string level;
  string department;
  int sID = 0;
  int max = 1000;
  int min = 5000;
  bool idexists = false;
  //Generate Faculty ID

  srand(time(NULL));
  int range = max - min + 1;
  int fID = rand() % range + min;

  while(idexists == false){
    if(masterFaculty.contains(fID) == false){
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

    if(numAdvisees != 0) {
      cout << "\nHere is a list of students in database: " << endl;
      printStudentsInOrder();
    }

    for(int i = 0; i < numAdvisees; ++i) {
      while(true) {
        cout << "[" << numAdvisees << " Remaining] Please Provide a Student ID: ";
        cin >> sID;
          if(masterStudent.contains(sID)) {
            faculty->addAdvisee(sID);
            masterStudent.find(sID)->setAdvisor(fID);
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

//allows the user to delete a faculty member from the records given an ID number and transfer their advisees to a new advisor
void Menu::deleteFaculty() {
  int deleteID = 0;
  int transferID = 0;

  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty database is empty. Nothing to delete!" << endl;
  }else {
    while(true) {
      cout << "\nPlease provide ID of faculty to be deleted: ";
      cin >> deleteID;
        if(masterFaculty.contains(deleteID)) {
          if(masterFaculty.find(deleteID)->numAdvisee > 0) {
            while(true) {
              cout << "\nEnter faculty ID to move advisee to: ";
              cin >> transferID;
                if(masterFaculty.contains(transferID)) {
                  for(int i = 0; i < masterFaculty.find(deleteID)->maxSize; ++i) {
                    if(masterFaculty.find(deleteID)->adviseeArray[i] != -1) {
                      masterStudent.find(masterFaculty.find(deleteID)->adviseeArray[i])->setAdvisor(transferID);
                    }
                  }
                }else {
                  cout << "\nThat faculty doesn't exist." << endl;
                }
                break;
            }
          }else{
            masterFaculty.erase(deleteID);
            break;
          }
        }else{
          cout << "\nThat faculty doesn't exist." << endl;
        }
      break;
    }
  }
}

//allows the user to change the advisor of a student from one faculty member
// to another given all the IDs neccessary
void Menu::changeAdvisor() {
  int toNewAdvisor = 0;
  int changetofaculty = 0;

  if(masterFaculty.isEmpty() || masterStudent.isEmpty()) {
    cout << "\nEither Studnet or Faculty database is empty. Nothing to change" << endl;
  }else {
    while(true) {
      cout << "\nTo change advisor, please enter the student ID: ";
      cin >> toNewAdvisor;

        if(masterStudent.contains(toNewAdvisor)) {
          while(true) {
            cout << "\nPlease Provide a Faculty ID: ";
            cin >> changetofaculty;
              if(masterFaculty.contains(changetofaculty)) {
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
    masterStudent.find(toNewAdvisor)->setAdvisor(changetofaculty);
    masterFaculty.find(changetofaculty)->addAdvisee(toNewAdvisor);
  }
}

//allows the user to remove an advisee from an advisor given the ID numbers of both
void Menu::removeAdvisee() {
  int thefaculty = 0;
  int removingAdvisee = 0;

  if(masterFaculty.isEmpty() || masterStudent.isEmpty()) {
    cout << "\nStudent and/or Faculty Database is Empty" << endl;
  }else {
    while(true) {
      cout << "\nPlease Provide a Faculty ID: ";
      cin >> thefaculty;

        if(masterFaculty.contains(thefaculty)) {
          cout << "\nList of Advisees for Faculty ID: " << thefaculty << endl;
          masterFaculty.find(thefaculty)->printAdvisee();

          while(true) {
            cout << "\nPlease Provide a Student ID: ";
            cin >> removingAdvisee;
              if(masterStudent.contains(removingAdvisee)) {
                break;
              }else {
                cout << "\nERROr: That student doesn't exist! " << endl;
              }
          }
          break;
        }else {
          cout << "\nERROR: That faculty doesn't exist!" << endl;
        }
    }

    if(masterFaculty.find(thefaculty)->removeAdvisee(removingAdvisee)) {
      masterStudent.find(removingAdvisee)->setAdvisor(-1);
    }

    char c;
    cout << "\nWoudld you like the advisee to have a new advisor? (y/n) ";
    cin >> c;

    if(c == 'Y' || c == 'y') {
      while(true) {
        cout << "Please Provide a Faculty ID: ";
        cin >> thefaculty;

          if(masterFaculty.contains(thefaculty)) {
            break;
          }else {
            cout << "\nERROR: That faculty doesn't exist!" << endl;
          }
      }
      masterStudent.find(removingAdvisee)->setAdvisor(thefaculty);
    }
  }
}

//allows the user to undo the last five commands they did
void Menu::rollback() {

}

//exits the program
void Menu::exit() {
  cout << "EXITING PROGRAM..." << endl;
}
