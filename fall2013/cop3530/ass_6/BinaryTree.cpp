/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86

Discussion Section #: 1085

*/

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include "myException.h"
#include "BinaryTree.h"

using namespace std;

BinaryTree::BinaryTree(){
    root = NULL;
    size = 0;    
}
BinaryTree::BinaryTree(const int& key, const int& value){
    root = new Node(key, value);
    size = 0;    
}
BinaryTree::~BinaryTree(){
    // root->RecursiveDelete(root);
    delete root;
}

void BinaryTree::preOrderPrint(){
    preOrder(root);
}

void BinaryTree::inOrderPrint(){
    inOrder(root);
}

void BinaryTree::postOrderPrint(){
    postOrder(root);
}

void BinaryTree::levelOrderPrint(){
    queue<Node*> q;
    q.push(root);
    // q.front()->print();
    int i = 1;
    int j = 1;
    while(!q.empty()){
        q.front()->print();
        if(i++ == (int)pow(2,j)-1){
            cout << endl;
            j++;
        }
        if(q.front()->leftChild)
            q.push(q.front()->leftChild);
        if(q.front()->rightChild)
            q.push(q.front()->rightChild);
        q.pop();
    } 
}
void BinaryTree::preOrder(Node* ptr){
    if(!ptr) return;
    ptr->print();
    if(ptr->leftChild != NULL)
        preOrder(ptr->leftChild);
    if(ptr->rightChild != NULL)
        preOrder(ptr->rightChild);
}

void BinaryTree::inOrder(Node* ptr){
    if(!ptr) return;
    if(ptr->leftChild != NULL)
        inOrder(ptr->leftChild);

    ptr->print();

    if(ptr->rightChild != NULL)
        inOrder(ptr->rightChild);
}

void BinaryTree::postOrder(Node* ptr){
    if(!ptr) return;
    if(ptr->leftChild != NULL)
        postOrder(ptr->leftChild);
    if(ptr->rightChild != NULL)
        postOrder(ptr->rightChild);
    
    ptr->print();
}

void BinaryTree::insert(const int& key, const int& value){
    Node* current = root;
    Node* parent = NULL;
    while(current != NULL){
        parent = current;
        if(key <= current->key)
            current = current->leftChild;
        else
            if(key > current->key)
                current = current->rightChild;
            else{
                current->value = value;
            }
    }

    Node* newNode = new Node(key, parent, value);
    if(root != NULL)
        if(key <= parent->key)
            parent->leftChild = newNode;
        else
            parent->rightChild = newNode;
    else
        root = newNode;
    size++;
}

BinaryTree::Node* BinaryTree::search(int key){
    // cout << "/search";
    Node* current = root;
    while(current != NULL){
        if(current->key == key) return current;
        if(key < current->key)
            current = current->leftChild;
        else    
            current = current->rightChild;
    }
    return NULL;
}

BinaryTree::Node* BinaryTree::minimum(){
    return min(root);
}

BinaryTree::Node* BinaryTree::min(Node* anchor){
    if(anchor->leftChild == NULL)
        return anchor;
    else{
        return(min(anchor->leftChild));
    }
}


BinaryTree::Node* BinaryTree::maximum(){
    return max(root);
}

BinaryTree::Node* BinaryTree::max(Node* anchor){
    Node* temp = anchor;
    while(temp->rightChild != NULL)
        temp = temp->rightChild;
    return temp;
}
void BinaryTree::eraseKey(int key){
    // cout << "/eraseKey" << key;
    Node *temp;
    temp = search(key);
    cout << "erase ";
    temp->print();
    eraseNode(temp);
}
void BinaryTree::eraseNode(Node* current){
    // perror("/eraseNode");
    if(current == NULL)
        return; // no pair with key
    // if leaf  
    else if(current->leftChild == NULL && current->rightChild == NULL){
        // perror("/leaf");
        if(current == root){
            root->~Node();
            root = NULL;
        }
        // if current is left leaf of parent
        else if(current->parent->leftChild == current){
            // perror("/leftleaf");
            current->parent->leftChild = NULL;
            delete current;
        }
        // if current is right leaf of parent
        else{
            // perror("/rightleaf");
            current->parent->rightChild = NULL;
            delete current;
        }
    }
    // if has only right subtree
    else if(current->leftChild == NULL && current->rightChild != NULL){
        // perror("/rightsubtree");
        if(current == root){
            root = current->rightChild;
            current->rightChild->parent = NULL;
            current->~Node();
        }
        // if current is left child of parent
        else if(current->parent->leftChild == current){
            // perror("/leftleaf");
            current->parent->leftChild = current->rightChild;
            current->rightChild->parent = current->parent;
            current->~Node();
        }
        // if current is right leaf of parent
        else{
            // perror("/rightleaf");
            current->parent->rightChild = current->rightChild;
            current->rightChild->parent = current->parent;
            current->~Node();
        }
    }
    // if has only left subtree
    else if(current->leftChild != NULL && current->rightChild == NULL){
        // perror("/leftsubtree");
        if(current == root){
            root = current->leftChild;
            current->leftChild->parent = NULL;
            current->~Node();
        }
        // if current is left leaf of parent
        else if(current->parent->leftChild == current){
            // perror("/leftleaf");
            current->parent->leftChild = current->leftChild;
            current->leftChild->parent = current->parent;
            current->~Node();
        }
        // if current is right leaf of parent
        else{
            // perror("/rightleaf");
            current->parent->rightChild = current->leftChild;
            current->leftChild->parent = current->parent;
            current->~Node();
        }
    }
    // if has left and right subtree
    else{
        // perror("/two children");
        // find smallest key in right subtree
        Node* successor = min(current->rightChild);
        // replace current key with those values
        current->key = successor->key;
        current->value = successor->value;
        // recursively delete successor
        eraseNode(successor);
    }   
    size--;
    // delete current;
}
/*
int main(){
    BinaryTree* bin = new BinaryTree();
    int k = 0;
    int j = 0;
    int* entries = new int[10];
    srand(time(NULL));
    for(int i = 0; i < 6; i++){
        k = rand()%100;
        entries[i] = k;
        // j = rand()%100;
        cout << entries[i] << " ";
        bin->insert(k,rand()%100);
    }
    cout << endl;
    bin->preOrderPrint();
    cout << endl;
    bin->inOrderPrint();
    cout << endl;

    delete bin;

    bin->preOrderPrint();
    
    int n,f;
    bool erase;
    bool insert;
    bool continu = true;
    while(continu){
        cout << "insert?";
        cin >> insert;
        if(insert){
            cout << "enter key ";
            cin >> n;
            bin->insert(n,0);
            bin->preOrderPrint();
        }
        cout << "erase?";
        cin >> erase;
        if(erase){
            cout << "enter key ";
            cin >> f;
            bin->eraseKey(f);
            bin->preOrderPrint();
        }
    }

    for(int i = 0; i < 6; i++){
        bin->eraseKey(entries[i]);
    }

    cout << "enter erase ";
    // int m = 0;
    // cin >> m;
    // bin->eraseKey(m);
    cout << endl;
    bin->preOrderPrint();
    cout << endl;
    bin->inOrderPrint();
    cout << endl;
    // delete bin;
    // bin->print();    

    for(int i = 0; i < 6; i++){
        bin->insert(entries[i],rand()%100);
    }

    bin->preOrderPrint();
    cout << endl;
    bin->inOrderPrint();
    cout << endl;


}*/