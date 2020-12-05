/*
Kaylee Chan
2348244
kaychan@chapman.edu
CPSC 350-03
Assignment 5
*/
#include <iostream>
using namespace std;

template <typename T>
class ListNode{
public:
  T data;
  ListNode *next; 

  ListNode();
  ListNode(T d);
  ~ListNode();
};

template <typename T>
ListNode<T>::ListNode(){
  data = NULL;
  next = NULL;
}

template <typename T>
ListNode<T>::ListNode(T d){
  data = d;
  next = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){
  //build and research for yourself
  next = NULL;
  delete next;
}
