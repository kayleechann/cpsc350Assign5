/*
Kaylee Chan
2348244
kaychan@chapman.edu
CPSC 350-03
Assignment 5
*/
#include <iostream>
#include "Student.h"
#include "Faculty.h"
#include "BST.h"
#include "GenStack.h"
#include "Transaction.h"

using namespace std;

class Menu {
  public:
    BST<Student> masterStudent;
    BST<Faculty> masterFaculty;
    // GenStack<Student> reverseStudent = new GenStack<Student>();
    // GenStack<Faculty> reverseFaculty;

    Menu();
    ~Menu();

    void menuOptions();

    void readStudentFile();
    void readFacultyFile();
    void serializeFiles();

    void printMS(TreeNode<Student> *s);
    void printMF(TreeNode<Faculty> *f);

    void outputMS(TreeNode<Student> *s);
    void outputMF(TreeNode<Faculty> *f);

    void printStudentsInOrder();
    void printFacultyInOrder();

    void displayStudent();
    void displayFaculty();

    void printAdvisor();
    void printAdvisees();

    void addStudent();
    void deleteStudent();

    void addFaculty();
    void deleteFaculty();

    void changeAdvisor();
    void removeAdvisee();

    void rollback();

    void exit();

    TreeNode<Student>* getMSRoot();
    TreeNode<Faculty>* getMFRoot();

};
