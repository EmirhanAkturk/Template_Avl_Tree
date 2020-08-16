//#include<iostream>
#include "inc/AVLTree.hpp"

//using namespace std;


int main(){
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(5);
    tree.insert(0);
    
    tree.print(1);

    int x=30;
    if(tree.search(x)){
        cout<<"Found:"<<x<<endl;
    }
    else cout<<"not found\n";

    if(tree.remove(x)){
        cout<<"deleted:"<<x<<endl;
    }
    else cout<<"not deleted\n";

    tree.print(1);
    
    ofstream outFile("text.txt");
    tree.writeFile(outFile,1);

    return 0;
}