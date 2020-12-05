#include "ListNode.h"
using namespace std;

template <typename T>
class SinglyLinkedList{
private:
  ListNode<T> *front;
  ListNode<T> *back;
  unsigned int size;

public:
  SinglyLinkedList();
  ~SinglyLinkedList();
  void insertFront(T d);
  void insertBack(T d);
  T removeFront();
  T removeBack();
  T find(T value); //AKA search()
  T deletePos(T pos);

  void printList();
  bool isEmpty();
  unsigned int getSize();
};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(){
  front = NULL;
  back = NULL;
  size = 0;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList(){
  //build some character, research
}

template <typename T>
void SinglyLinkedList<T>::insertFront(T d){
  ListNode<T> *node = new ListNode<T>(d);
  if (size == 0){ //make sure front and back aren't going to be the same except fit heres one thing
    back = node;
  }
  node->next = front;
  front = node;
  ++size;
}

template <typename T>
void SinglyLinkedList<T>::insertBack(T d){
  ListNode<T> *node = new ListNode<T>(d);

  if(front == NULL){
    front = back;
  }else {
    back-> next = node;
  }
  back = node;
  ++size;

}

//you have removeFront
template <typename T>
T SinglyLinkedList<T>::removeFront(){
  T temp = front->data;
  ListNode<T> *ft = front;
  front = front->next;
  ft->next = NULL;
  --size;
  delete ft;
  return temp;
}

//you need to implement removeBack();
template <typename T>
T SinglyLinkedList<T>::removeBack(){
  T temp = back->data;
  ListNode<T> *bk = back;
  back = back->next;
  bk->next = NULL;
  --size;
  delete bk;
  return temp;
}

template <typename T>
void SinglyLinkedList<T>::printList(){
  ListNode<T> *curr = front;
  while(curr != NULL){
    cout << curr->data << endl;
    curr = curr->next;
  }
  //don't have to delete curr because once its out of scope, its gone
  //we're also not allocating memory
}

template <typename T>
T SinglyLinkedList<T>::find(T value){
  int pos = -1;
  ListNode<T> *curr = front;

  while(curr != NULL){
    ++pos;
    if(curr->data == value){
      break;
    }
    curr = curr->next;
  }

  //we didn't find it
  if(curr = NULL){
    pos = -1;
  }
  return pos;
}

template <typename T>
bool SinglyLinkedList<T>::isEmpty(){
  return (size == 0);
}

template <typename T>
T SinglyLinkedList<T>::deletePos(T pos){
  int p = 0; //want to interate list, so p is used ot keep track of where you are in linked list
  ListNode<T> *curr = front;
  ListNode<T> *prev = front;

  while(p != pos){
    prev = curr;
    curr = curr->next;
    p++;
  }

  //we found the correct position, continue with removal
  prev->next = curr->next;
  curr->next = NULL;
  T temp = curr->data;
  size--;

  delete curr;
  return temp;
}

template <typename T>
unsigned int SinglyLinkedList<T>::getSize(){
  return size;
}
