#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include<iostream>
#include<fstream>

using namespace std;

template <class T>
class Node{
public:
    Node<T>(const T& newData ):data{newData},right{nullptr},left{nullptr},height{0}
    { /* deliberately left blank */}
    
    T data;
    Node<T> *right;
    Node<T> *left;
    int height;
};

template <class T>
class AVLTree{
public:
    AVLTree(){
        root=nullptr;
    }
    
    ~AVLTree(){
        root=makeEmpty(root);
    }

    void insert(const T& data){
        root = insertNode(root,data);
    }

    bool remove(const T& data){
        root = removeNode(root,data);//return değerlerini kontrol et!!
        
        if(root!=nullptr)
            return true;
        
        else return false;
    }

    bool search(const T& data) {
        Node<T> *query = searchNode(root, data);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

    void print(int choice)const{//1:inorder,2:preorder,3:postorder
        if(choice == 1)
            inorder(root);
        else if(choice==2)
            preorder(root);
        else if(choice==3)
            postorder(root);
        else cout<<"invalid selection!\n";

        cout << endl;
    }

    void writeFile(ofstream & outFile,int choice)const{//1:inorder,2:preorder,3:postorder
        if(choice==1)
            writeInorder(root,outFile);
        else if(choice==2)
            writePreorder(root,outFile);
        else if(choice==3)
            writePostorder(root,outFile);
        
        else cout<<"invalid selection!\n";
    }

private:
    Node<T>* root;


    Node<T>* insertNode(Node<T>* node, const T& data);
    Node<T>* removeNode(Node<T>* node,const T& data);
    Node<T>* searchNode(Node<T>* node, const T& data);

    Node<T>* makeEmpty(Node<T>* node);

    Node<T>* doBalanced(Node<T>* node);
    Node<T>* doBalanced(Node<T>* node, const T& data);
    
    Node<T>* rightRotate(Node<T>* node);
    Node<T>* leftRotate(Node<T>* node);

    Node<T>* findMin(Node<T>* node);
    Node<T>* findMax(Node<T>* node);

    int getBalance(Node<T>* node);
    int height(Node<T> * node);

    void inorder(Node<T>* node)const;
    void preorder(Node<T>* node)const;
    void postorder(Node<T>* node)const;
    
    void  writeInorder(Node<T> * node,ofstream & outFile)const;
    void  writePreorder(Node<T> * node,ofstream & outFile)const;
    void  writePostorder(Node<T> * node,ofstream & outFile)const;
};

#include "../src/AVLTree.inl"

#endif