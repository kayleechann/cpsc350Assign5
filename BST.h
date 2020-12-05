/*
Kaylee Chan
2348244
kaychan@chapman.edu
CPSC 350-03
Assignment 5
*/
#include <iostream>
#include "TreeNode.h"
using namespace std;

template <typename T>
class BST{
protected:
    TreeNode<T> *root;
    int size;

  public:
    BST();
    ~BST();

    bool searchNode(int k); //returns boolean if element is in tree
    T* search(int k); // returns element itself if element is in tree
    void insertNode(TreeNode<T> *node);
    TreeNode<T>* getSuccessor(TreeNode<T> *d);
    bool deleteNode(int k);

    //Auxiliary functions
    /* this function will play a role when deleting a node.
    *d represents a node to be deleted */
    T* getMin();
    T* getMax();

    void recPrint(TreeNode<T> *node);
    void printTree();

    TreeNode<T>* getRoot();
    int getSize();
    bool isEmpty();
  };

  template <typename T>
  BST<T>::BST() {
    root = NULL;
    size = 0;
  }

  template <typename T>
  BST<T>::~BST() {

  }

  template <typename T>
  void BST<T>::recPrint(TreeNode<T> *node) {
    if(node == NULL) {
      return;
    }

    recPrint(node->left);
    cout << node->key << endl;
    recPrint(node->right);
  }


  template <typename T>
  void BST<T>::printTree() {
    recPrint(root);
  }

  template <typename T>
  TreeNode<T>* BST<T>::getRoot() {
    return root;
  }

  template <typename T>
  int BST<T>::getSize() {
    return size;
  }

  template <typename T>
  bool BST<T>::isEmpty() {
    return(size == 0);
  }

  template <typename T>
  bool BST<T>::searchNode(int k) {
    if(isEmpty()) {
      return false;
    }

    TreeNode<T> *curr = root;
    while(curr->key != k) {
      if(k < curr->key) {
        curr = curr->left;
      }else {
        curr = curr->right;
      }
      if(curr == NULL) {
        return false;
      }
    }
    return true;
  }

  template <typename T>
  T* BST<T>::search(int k) {
    if(root == NULL) {
      return NULL;
    }

    if(searchNode(k)) {
      TreeNode<T> *curr = root;

      while(curr->key != k) {
        if(k < curr->key) {
          curr = curr->left;
        }else {
          curr = curr->right;
        }

        if(curr == NULL) {
          return NULL;
        }
      }
      return curr->data;
    }
    else {
      return NULL;
    }
  }

  template <typename T>
  void BST<T>::insertNode(TreeNode<T> *node) {
    if(root == NULL) {
      root = node;
    }
    else {
      TreeNode<T> *curr = root;
      TreeNode<T> *parent;

      while(true) {
        parent = curr;
        if(node->key < curr->key) {
          curr = curr->left;
          if(curr == NULL) {
              parent->left = node;
              break;
          }
        }else {
          if(node->key > curr->key) {
            curr = curr->right;
            if(curr == NULL) {
              parent->right = node;
              break;
            }
          }
        }
      }
    }
    ++size;
  }

  template <typename T>
  TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d) {
    TreeNode<T> * sp = d; //sp = successor's parent
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;

    while(current != NULL){
      sp = successor;
      successor = current;
      current = current->left;
    }

    if(successor != d->right){
      sp->left = successor->right;
      successor->right = d->right;
    }
    return successor;
  }

  template <typename T>
  bool BST<T>::deleteNode(int k) {
      if(isEmpty()){  //root == NULL
        return false;
      }
      //invoke search to determine whether it exists or not
      TreeNode<T> *parent = NULL;
      TreeNode<T> *curr = root;
      bool isLeftNode = true;

      while(curr->key != k){
        parent = curr;

        if(k < curr->key){
          isLeftNode = true;
          curr = curr->left;
        }else{
          isLeftNode = false;
          curr = curr->right;
        }

        if(curr == NULL){
          return false; //value does not exist
        }

        //at this point, we have found our key/value. now let's proceed to delete this node
      }

      //case 1: node to be deleted does not have children, AKA a leaf node
      if(curr->left == NULL && curr->right == NULL){
        if(curr == root){
          root = NULL;
        }else if(isLeftNode){
          parent->left = NULL;
        }else{
          parent->right = NULL;
        }
        //case 2: node to be deleted has one child. need to deterimine whether descendant is left or right
      }else if(curr->right == NULL){
        //does not have a right child, must have left
        if(curr == root){
          root = curr->left;
        }else if(isLeftNode){
          parent->left = curr->left;
        }else{
          //node to be deleted is a right child
          parent->right = curr->left;
        }
      }else if(curr->left == NULL){
        //does not have a left child, must have right child
        if(curr == root){
          root = curr->right;
        }else if(isLeftNode){
          parent->left = curr->right;
        }else{
          //node to be deleted is a right child
          parent->right = curr->right;
        }
      }else{
        //node to be deleted has two children. at this point, we begin to cry.
        //we have to find the successor .

        TreeNode<T> *successor = getSuccessor(curr); //current is the node to be deleted

        if(curr == root){
          root = successor;
        }else if(isLeftNode){
          parent->left = successor;
        }else{
          parent->right = successor;
          successor ->left = curr->left;
        }
      }
      //delete  curr????? could be exam question on final?
      //do we need to delete (garbage collect) in this function or do we do soemthing special in the destructor??
      return true;
  }

  template <typename T>
  T* BST<T>::getMin() {
    TreeNode<T> *curr = root; //Start at root

    if(root == NULL) {
      return NULL;
    }

    while(curr->left != NULL) {
      curr = curr->left;
    }

    return curr;
  }

  template <typename T>
  T* BST<T>::getMax() {
    TreeNode<T> *curr = root;

    if(root == NULL) {
      return NULL;
    }

    while(curr->right != NULL) {
      curr = curr->right;
    }

    return curr;
  }
