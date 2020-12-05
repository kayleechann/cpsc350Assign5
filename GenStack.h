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
class GenStack{
public:
  GenStack();
  GenStack(int maxSize);
  ~GenStack();

  void resize();
  void push(T data);
  T pop(); //removes first item on stack
  T peek(); //looks at first item on stack

  bool isFull();
  bool isEmpty();
  int getSize();

private:
  int top;
  int mSize;
  char *myArray;

};

//overloaded constructor
template <typename T>
GenStack<T>::GenStack(int maxSize){
  myArray = new char[maxSize];
  mSize = maxSize;
  top = -1;
}

//destructor
template <typename T>
GenStack<T>::~GenStack(){
  delete myArray;
}

/*
resize method - automatically allocates more memory is stack is full
void - does not have return type
parameter - none
*/
template <typename T>
void GenStack<T>::resize(){
  T *tempArray = new T[mSize*2];
  for(int i = 0; i < mSize; ++i){
    tempArray[i] = myArray[i];
  }
  myArray = tempArray;
  mSize = mSize*2;
}

//push(T data)  - inserts element to the top of the stack
template <typename T>
void GenStack<T>::push(T data){
  if(isFull()){
    resize();
  }
  myArray[++top] = data; //preincrement --> increment before we add
}

//pop() - returns anmd removes the top element
template <typename T>
T GenStack<T>::pop(){
  if(isEmpty()){
    cout << "ERROR: stack is empty" << endl;
    return  '\0';
  }
  return myArray[top--]; //doesn't actually remove from array, we're just decrementing the variable that keeps
  //track of the current element
}

//peeK() - returns but does not remove the top element in the stack
template <typename T>
T GenStack<T>::peek(){
  if(isEmpty()){
    cout << "stack is currently empty" << endl;
    return 0;
  }
  return myArray[top];
}

//isEmpty() - returns true/false if stack is empty
template <typename T>
bool GenStack<T>::isEmpty(){
  //1 = true, 0 = false
  return (top == -1);
}

//isFull() - returns true/false is stack is full
template <typename T>
bool GenStack<T>::isFull(){
  return (top  == mSize -1 );
}

//getSize() - returns integer of size of stack
template <typename T>
int GenStack<T>::getSize(){
  return top + 1;
}
