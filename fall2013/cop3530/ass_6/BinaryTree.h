/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#ifndef BinaryTree_
#define BinaryTree_
#include <iostream>
using namespace std;

class BinaryTree{

  public:

    class Node{

      public:
        Node(){
            this->key = -999999;
            this->value = -999999;
            this->leftChild = NULL; 
            this->rightChild = NULL;
            this->parent = NULL;
        };
        Node(const int& key, const int& value){
            this->key = key;
            this->value = value;
            this->leftChild = NULL; 
            this->rightChild = NULL;
            this->parent = NULL;
        }
        Node(const int& key, Node* par, const int& value){
            this->key = key;
            this->value = value;
            this->leftChild = NULL; 
            this->rightChild = NULL;
            this->parent = par;
        }
        Node(const int& key, const int& value, Node* right){
            this->key = key;
            this->value = value;
            this->leftChild = NULL;
            this->rightChild = right;
            this->parent = NULL;
        }
        Node(Node* left, const int& key, const int& value){
            this->key = key;
            this->value = value;
            this->leftChild = left;
            this->rightChild = NULL;
            this->parent = NULL;
        }
        Node(Node* left, const int& key, const int& value, Node* right){
            this->key = key;
            this->value = value;
            this->leftChild = left;
            this->rightChild = right;
            this->parent = NULL;
        }
        ~Node(){
            // parent = NULL;
/*            if(leftChild)
                delete leftChild;
            if(rightChild)
                delete rightChild;
*/          
            // delete leftChild;
            // delete rightChild;
        }
        void RecursiveDelete(Node* ptr){
            if(!ptr) return;
            Node* temp = ptr;

            RecursiveDelete(temp->leftChild);
            RecursiveDelete(temp->rightChild);
            delete ptr;

        }

        void print(){
            cout << "key: " << key << " value: " << value << endl;
        }
          
        int key;
        int value;
        Node *leftChild, *rightChild, *parent;
    };

    Node *root;
    int size;
  
    
    BinaryTree();
    BinaryTree(const int& key, const int& value);
    ~BinaryTree();
    void preOrder(Node* ptr);
    void preOrderPrint();
    void inOrder(Node* ptr);
    void inOrderPrint();
    void levelOrderPrint();
    void postOrder(Node* ptr);
    void postOrderPrint();
    virtual void insert(const int& key, const int& value);
    Node* search(int key);
    Node* min(Node* anchor);
    Node* minimum();
    Node* max(Node* anchor);
    Node* maximum();
    void eraseKey(int key);
    void eraseNode(Node* current);

};

#endif

