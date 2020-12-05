#include <iostream>
using namespace std;

template <typename T>
class TreeNode{

private:

public:
int key;
T* data;
TreeNode<T> *left;
TreeNode<T> *right;

TreeNode();
TreeNode(T* d, int k);
virtual ~TreeNode();
};

//TreeNode.cpp (implementation)
template <class T>
TreeNode<T>::TreeNode() {
  key = -1;
  data = T();
  left = NULL;
  right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T* d, int k) {
  key = k;
  data = d;
  left = NULL;
  right = NULL;
}

template <class T>
TreeNode<T>::~TreeNode() {
  delete data;
  delete left;
  delete right;
}
