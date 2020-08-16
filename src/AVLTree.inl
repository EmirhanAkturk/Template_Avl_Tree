template<class T>
Node<T>* AVLTree<T>::makeEmpty(Node<T> *node){
    if(node == nullptr)
        return nullptr;
    
    else{
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
    }
    return nullptr;
}

template<class T>
Node<T>* AVLTree<T>::insertNode(Node<T>* node, const T& newData){
    
    Node<T> *query= searchNode(node,newData);

    if(query!=nullptr){
        if(query->data!=newData){
            query->data=newData;
        }

        return node;
    }

    /* 1. Perform the normal BST insertion */
    if(node == nullptr)
    {
        Node<T> *temp=new Node<T>(newData);
        return temp;
    }

    if(newData < node->data){
        node->left = insertNode(node->left,newData);
    }

    else if(newData > node->data){
        node->right = insertNode(node->right, newData);
    }   
    
    else return node;

    /* 2. Update height of this ancestor Node */
    node->height=max(height(node->left), height(node->right))+1;

    /* 3. Get the balance factor of this ancestor 
    Node to check whether this Node became 
    unbalanced */
    
    return doBalanced(node,newData);
}

template<class T>
Node<T>* AVLTree<T>::removeNode(Node<T>* node,const T& data) {
    
    if(node == nullptr)// Element not found
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    else if(data < node->data)
        node->left = removeNode(node->left,data);

    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if(data > node->data)
        node->right = removeNode(node->right,data);
    
    // if value is same as root's value, then This is the Node
    // to be deleted
    else 
    {   
        // Node with only one child or no child
        if( (node->left == nullptr) || (node->right == nullptr) ) {
            
            Node<T> * temp;

            if(node->left == nullptr){
                temp = node->right;
                delete node;
            }
            else{
                temp=node->left;
                delete node;
            }

            // No child case
            if(temp == nullptr){
                temp = node;
                node = nullptr;
            }

            else {// One child case
                node = temp; // Copy the contents of the non-empty child
                temp = nullptr;
            }
            //temp = nullptr;

        }
        else{
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)

            Node<T> * temp = findMin(node->right);

            // Copy the inorder successor's data to this Node
            node->data=temp->data;

            // remove the inorder successor
            node->right=removeNode(node->right,temp->data);

        }
    }
    
    // If the tree had only one Node then return
    if(node==nullptr)
        return node;

    node->height = max(height(node->left), height(node->right))+1;

    return doBalanced(node);
}

template<class T>
Node<T>* AVLTree<T>::searchNode(Node<T>* node, const T& data) {
    if(node == nullptr)
        return nullptr;
    
    else if(node->data == data)
        return node;
        
    else if(data > node->data)
        return searchNode(node->right, data);

    else return searchNode(node->left, data);

}

template<class T>
Node<T>* AVLTree<T>::findMin(Node<T>* node)
{
    if(node == nullptr)
        return nullptr;
    else if(node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}

template<class T>
Node<T> * AVLTree<T>::findMax(Node<T>* node) {
    if(node == nullptr)
        return nullptr;
    else if(node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}

template<class T>
Node<T>* AVLTree<T>::doBalanced(Node<T> *node){
    
    int balance = getBalance(node);
    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && getBalance(node->left)>=0) 
        return rightRotate(node); 

    // Left Right Case 
    if (balance > 1 && getBalance(node->left)<0) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Right Case 
    if (balance < -1 && getBalance(node->right)<=0) 
        return leftRotate(node); 

    // Right Left Case 
    if (balance < -1 && getBalance(node->left)>0) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    /* return the (unchanged) Node pointer */
    return node;

}

template<class T>
Node<T>* AVLTree<T>::doBalanced(Node<T> *node,const T& newData){

    int balance = getBalance(node);

    // If this Node becomes unbalanced, then 
    // there are 4 cases 

    // Left Left Case 
    if (balance > 1 && newData < node->left->data) 
        return rightRotate(node); 

    // Right Right Case 
    if (balance < -1 && newData > node->right->data) 
        return leftRotate(node); 

    // Left Right Case 
    if (balance > 1 && newData > node->left->data) 
    { 
        node->left = leftRotate(node->left); 
        return rightRotate(node); 
    } 

    // Right Left Case 
    if (balance < -1 && newData < node->right->data) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 

    return node;
}

template<class T>
Node<T> * AVLTree<T>::rightRotate(Node<T> *node) 
{ 
    Node<T> *x = node->left; 
    Node<T> *T2 = x->right; 

    // Perform rotation 
    x->right = node; 
    node->left = T2; 

    // Update heights 
    node->height = max(height(node->left), 
                    height(node->right)) + 1; 

    x->height = max(height(x->left), 
                    height(x->right)) + 1; 

    // Return new root 
    return x; 
} 

template<class T>
Node<T> * AVLTree<T>::leftRotate(Node<T> *node) 
{ 
    Node<T> *y = node->right; 
    Node<T> *x = y->left; 

    // Perform rotation 
    y->left = node; 
    node->right = x; 

    // Update heights 
    node->height = max(height(node->left),	 
                    height(node->right)) + 1; 
    y->height = max(height(y->left), 
                    height(y->right)) + 1; 

    // Return new root 
    return y; 
} 

template<class T>
int AVLTree<T>:: getBalance(Node<T>* node){
    if (node == NULL) 
        return 0; 
    return height(node->left) - height(node->right); 
}

template<class T>
int AVLTree<T>::height(Node<T> *node) 
{ 
    if (node == nullptr) 
        return 0; 

    return node->height; 
} 

template<class T>
void AVLTree<T>::inorder(Node<T>* node)const{
    if(node == nullptr)
        return;

    inorder(node->left);
    cout << node->data<<endl;
    inorder(node->right);
}

template<class T>
void AVLTree<T>::preorder(Node<T>* node)const{
    if(node == nullptr)
        return;

    cout << node->data<<endl;
    preorder(node->left);
    preorder(node->right);
}

template<class T>
void AVLTree<T>::postorder(Node<T>* node)const{
    if(node == nullptr)
        return;

    postorder(node->left);
    postorder(node->right);
    cout << node->data<<endl;
}

template<class T>
void  AVLTree<T>::writeInorder(Node<T> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree 
    writeInorder(node->left,outFile);

    // then deal with the Node 
    outFile << node->data<<endl;

    // now recur on right subtree 
    writeInorder(node->right,outFile);
}

template<class T>
void  AVLTree<T>::writePreorder(Node<T> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on node
    outFile << node->data<<endl;

    // then deal with the left subtree
    writePreorder(node->left,outFile);

    // now recur on right subtree 
    writePreorder(node->right,outFile);
}

template<class T>
void  AVLTree<T>::writePostorder(Node<T> * node,ofstream & outFile)const{
    if(node == nullptr)
        return;
    
    // first recur on left subtree
    writePostorder(node->left,outFile);
    
    // now recur on right subtree 
    writePostorder(node->right,outFile);
    
    // then deal with the Node 
    outFile << node->data<<endl;

}
