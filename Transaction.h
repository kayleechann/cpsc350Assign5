#include <iostream>
using namespace std;

template <typename T>
class Transaction{
public:
  Transaction();
  ~Transaction();
  Transaction(int id, string type);
  T getData();
  int getID();
  string getType();
  int getNumRollbacks();

  T t_data;
  int t_id;
  string t_type;
  int numRollbacks;
};

template <typename T>
Transaction<T>::Transaction(){
  t_data = NULL;
  t_id = 0;
  t_type = "";
  numRollbacks = 5;
}

template <typename T>
Transaction<T>::~Transaction(){

}

template <typename T>
Transaction<T>::Transaction(int id, string type){
  t_id = id;
  t_type = type;
  numRollbacks = 5;
}


template <typename T>
int Transaction<T>::getID(){
  return t_id;
}

template <typename T>
T Transaction<T>::getData(){
  return t_data;
}

template <typename T>
string Transaction<T>::getType(){
  return t_type;
}

template <typename T>
int Transaction<T>::getNumRollbacks(){
  return numRollbacks;
}
