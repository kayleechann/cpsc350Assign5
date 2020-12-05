#include <iostream>
using namespace std;

template <typename T>
class ListNode{
public:
  T data;
  ListNode *next; //pointer of type ListNode because its pointer to next ListNode

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
