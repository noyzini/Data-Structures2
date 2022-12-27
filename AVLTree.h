#ifndef DATA_STRUCTURES_AVLTREE_H
#define DATA_STRUCTURES_AVLTREE_H

#include "Node.h"
#include <math.h>
#include <iostream>

template<class T, typename KEY>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(T& data,KEY key);
    void remove(KEY key);
    T* find (const KEY key);
    bool checkRotation(Node<T,KEY>* node);
    int getBalanceFactor(const Node<T,KEY>* node) const;
    Node<T,KEY>* getRoot() const ;
    void rotate_right(Node<T,KEY>* a);
    void rotate_left(Node<T,KEY>* b);
    void delete_recursively(Node<T,KEY>* node);
    Node<T,KEY>* findNode( KEY key);
    int extractInOrder(Node<T, KEY> *node, Node<T, KEY>** arr);
    int getNumberOfNodes() const;
    T* findClosestRight(Node<T,KEY>* node) ;
    T* findClosestLeft(Node<T,KEY>* node) ;

    AVLTree<T, KEY>* mergeTrees(AVLTree<T, KEY>* tree2);
    Node<T,KEY>* getSubTree(Node<T,KEY>* node, KEY min, KEY max);

    Node<T, KEY> *getSubTree(Node<T, KEY> *node, KEY min, KEY max, Node<T, KEY> **keepLastHere);
private:
    Node<T,KEY>* root;
    int numNodes;

    Node<T,KEY>* addToTree(T& data, KEY& key);
    int calculateHeight(const Node<T,KEY>* b);
    void mergeArrays(Node<T, KEY> **arr1, int arr1Size, Node<T, KEY> **arr2, int arr2Size, Node<T, KEY> **output);
    AVLTree<T, KEY> *arrayToTree(Node<T, KEY> **arr, int arrSize);
    Node<T, KEY> *arrayToTreeAux(Node<T, KEY> **arr, int arrSize);
};

template<class T, typename KEY>
AVLTree<T, KEY>::AVLTree() : root(nullptr), numNodes(0) {}

template<class T, typename KEY>
Node<T, KEY> *AVLTree<T, KEY>::getRoot() const {
    return root;
}

template<class T,typename KEY>
Node<T,KEY>* AVLTree<T,KEY>::findNode( KEY key) {
    Node<T,KEY>* temp= this->root;
    while (temp!= nullptr && temp->key!=key)
    {
        if(temp->key > key)
            temp=temp->left;
        else
            temp=temp->right;
    }
    if(temp== nullptr)
        return nullptr;
    return temp;
}


template<class T, typename KEY>
T* AVLTree<T,KEY>::find(const KEY key)
{
    Node<T,KEY>* temp= findNode(key);
    if(temp== nullptr)
        return nullptr;
    return &(temp->data);
}

template<class T,typename KEY>
void AVLTree<T,KEY>::insert(T& data, KEY key)
{
    Node<T,KEY>* addedValueNode = addToTree(data,key);
    numNodes++;
    Node<T,KEY>* temp = addedValueNode;
    Node<T,KEY>* temp_parent = temp->parent;
    while (temp_parent != nullptr)
    {
        if (temp_parent->height >= temp->height +1)
            break;
        temp_parent->height = temp_parent->height + 1;
        if (checkRotation(temp_parent))
            break;
        temp = temp_parent;
        temp_parent = temp_parent->parent;
    }
}

template<class T, typename KEY>
bool AVLTree<T, KEY>::checkRotation(Node<T,KEY>* node)
{
    bool rotated = false;
    int balance_factor = getBalanceFactor(node);
    if (balance_factor == 2)
    {
        rotated = true;
        if (getBalanceFactor(node->left) >= 0)
        {
            //LL rotation
            rotate_left(node);
        }
        else //left BF should be == -1
        {
            //LR rotation
            rotate_right(node->left);
            rotate_left(node);
        }
    }
    else if (balance_factor == -2)
    {
        rotated = true;
        if (getBalanceFactor(node->right) <= 0)
        {
            //RR rotation
            rotate_right(node);
        }
        else //right BF should be == 1
        {
            //RL rotation
            rotate_left(node->right);
            rotate_right(node);
        }
    }
    return rotated;
}

template<class T, typename KEY>
int AVLTree<T, KEY>::getBalanceFactor(const Node<T,KEY>* node) const
{
    int leftTreeHeight = node->left != nullptr ? node->left->height : 0;
    int rightTreeHeight = node->right != nullptr ? node->right->height : 0;
    int balance_factor = leftTreeHeight - rightTreeHeight;
    return balance_factor;
}

template<class T,typename KEY>
void AVLTree<T,KEY>::remove(KEY key)
{
    Node<T,KEY>* to_delete= findNode(key);
    if (to_delete== nullptr)
        return;

    Node<T,KEY>* parent= to_delete->parent;
    Node<T,KEY>* balanceFrom = parent;
    //for a leaf
    if(to_delete->left== nullptr&& to_delete->right== nullptr){
        if(to_delete==root)//if it's the root then we only need to delete it.
        {
            root= nullptr;
        } else
        {
            if(to_delete->parent->right==to_delete)
            {
                to_delete->parent->right= nullptr;
            }
            else{
                to_delete->parent->left= nullptr;
            }
        }
    } else if(to_delete->right== nullptr||to_delete->left== nullptr)//only one side children
    {
        if(to_delete==root) //it's the root so we need to make sure the parent is null
        {
            if(to_delete->right== nullptr)
            {
                root=to_delete->left;
                to_delete->left->parent= nullptr;
            }
            else
            {
                root=to_delete->right;
                to_delete->right->parent= nullptr;
            }
        } else
        {
            if(to_delete->right== nullptr)//the left side isn't empty
            {
                if(to_delete->parent->right==to_delete) //making to_delete parent point to to_delete kids
                {
                    to_delete->parent->right=to_delete->left;
                } else
                {
                    to_delete->parent->left=to_delete->left;
                }
                to_delete->left->parent=to_delete->parent; //making to_delete kid have to_delete parent
            } else//the right side isn't empty
            {
                if(to_delete->parent->right==to_delete)//making to_delete parent point to to_delete kids
                {
                    to_delete->parent->right=to_delete->right;
                } else
                {
                    to_delete->parent->left=to_delete->right;
                }
                to_delete->right->parent=to_delete->parent;
            }
        }
    } else//has two kids
    {
        //finding the successor
        Node<T,KEY>* replace=to_delete->right;
        if (replace->left == nullptr) //the right son is the successor
        {
            replace->parent = to_delete->parent;
            if(to_delete==root)
            {
                root=replace;
            }
            else
            {
                if (to_delete->parent->right == to_delete)
                {
                    to_delete->parent->right = replace;
                }
                else
                {
                    to_delete->parent->left = replace;
                }
            }
            replace->left = to_delete->left;
            if (replace->left != nullptr)
                replace->left->parent = replace;
        }
        else //someone left to the right son is the successor
        {
            while (replace->left!= nullptr)
            {
                replace=replace->left;
            }
            Node<T,KEY>* replace_parent=replace->parent;
            balanceFrom = replace_parent;
            if(replace->right!= nullptr)
            {
                replace->right->parent=replace_parent;
            }
            replace_parent->left=replace->right;


            replace->right=to_delete->right;
            to_delete->right->parent=replace;

            replace->left=to_delete->left;
            if (to_delete->left!= nullptr)
                to_delete->left->parent=replace;

            replace->parent=to_delete->parent;
            if(to_delete->parent== nullptr)
            {
                root=replace;
            } else
            {
                if(to_delete->parent->right==to_delete)
                    to_delete->parent->right=replace;
                else
                    to_delete->parent->left=replace;
            }
        }
    }
    delete to_delete;
    numNodes--;

    //balancing the tree
    int previousHeight;
    while (balanceFrom != nullptr)
    {
        previousHeight=balanceFrom->height;
        balanceFrom->height= calculateHeight(balanceFrom);
        checkRotation(balanceFrom);
        if(balanceFrom->height==previousHeight)
        {
            return;
        }
        balanceFrom=balanceFrom->parent;
    }
}

template<class T, typename KEY>
Node<T, KEY> *AVLTree<T, KEY>::addToTree(T& data, KEY& key) {
    if (root == nullptr)
    {
        root = new Node<T,KEY>(data,key);
        return root;
    }
    Node<T,KEY>* temp=getRoot();
    Node<T,KEY>* keep=temp;
    while (temp!= nullptr)
    {
        keep=temp;
        if(temp->key > key)
            temp=temp->left;
        else
            temp=temp->right;
    }
    Node<T,KEY>* to_add= new Node<T,KEY>(data,key,keep);
    if(keep->key > key)
        keep->left=to_add;
    else
        keep->right=to_add;
    return to_add;
}

template<class T,typename KEY>
void AVLTree<T,KEY>::rotate_left(Node<T, KEY>* b) {
    Node<T,KEY>* a=b->left;
    b->left=a->right;
    if(a->right!= nullptr)
        a->right->parent=b;
    a->right=b;
    a->parent=b->parent;
    b->parent=a;
    if (a->parent == nullptr) //is root
        root = a;
    else
    {
        if (a->parent->right == b)
            a->parent->right = a;
        else
            a->parent->left = a;
    }
    b->height = calculateHeight(b);
    a->height = calculateHeight(a);
}

template<class T,typename KEY>
void AVLTree<T,KEY>::rotate_right(Node<T, KEY> *a)
{
    Node<T,KEY>* b=a->right;
    a->right=b->left;
    if(b->left!= nullptr)
        b->left->parent=a;
    b->left=a;
    b->parent=a->parent;
    a->parent=b;
    if (b->parent == nullptr) //is root
        root = b;
    else
    {
        if (b->parent->left == a)
            b->parent->left = b;
        else
            b->parent->right = b;
    }
    a->height= calculateHeight(a);
    b->height= calculateHeight(b);

}

template<class T,typename KEY>
int AVLTree<T,KEY>::calculateHeight(const Node<T, KEY>* b) {
    if (b == nullptr)
        return 0;
    if (b->left == nullptr && b->right == nullptr)
        return 1;
    if (b->left == nullptr)
    {
        return b->right->height+1;
    }
    else if(b->right== nullptr)
    {
        return b->left->height+1;
    }
    else
    {
        int max = b->right->height > b->left->height ? b->right->height : b->left->height;
        return max + 1;
    }
}

template<class T, typename KEY>
AVLTree<T, KEY>::~AVLTree() {
    delete_recursively(root);
}

template<class T, typename KEY>
void AVLTree<T, KEY>::delete_recursively(Node<T, KEY> *node) {
    if (node != nullptr)
    {
        delete_recursively(node->right);
        delete_recursively(node->left);
        delete node;
    }
}

template<class T, typename KEY>
AVLTree<T, KEY>* AVLTree<T, KEY>::arrayToTree(Node<T, KEY> **arr, int arrSize) {
    if (arrSize == 0 )
        return nullptr;
    AVLTree<T,KEY>* tree = new AVLTree<T,KEY>();
    if (arrSize == 1)
    {
        Node<T,KEY>* current =new Node<T,KEY>(arr[0]->data,arr[0]->key);
        tree->root = current;
        current->parent = nullptr;
        current->left = nullptr;
        current->right = nullptr;
        current->height = calculateHeight(current);
        return tree;
    }
    //preorder
    tree->root = new Node<T,KEY>(arr[arrSize/2]->data,arr[arrSize/2]->key);
    tree->root->parent = nullptr;
    int i = arrSize % 2 == 0 ? arrSize-arrSize/2 : arrSize-arrSize/2 -1;
    tree->root->left = arrayToTreeAux(arr,i);
    int arrLengthRight = arrSize-arrSize/2 -1;
    tree->root->right = arrayToTreeAux(arr + arrSize/2 + 1,arrLengthRight);
    if (tree->root->right != nullptr)
        tree->root->right->parent = tree->root;
    if (tree->root->left != nullptr)
        tree->root->left->parent = tree->root;
    tree->root->height = calculateHeight(tree->root);
    return tree;
}

template<class T, typename KEY>
Node<T, KEY>* AVLTree<T, KEY>::arrayToTreeAux(Node<T, KEY> **arr, int arrSize) {
    if (arrSize == 0 )
        return nullptr;
    if (arrSize == 1)
    {
        Node<T,KEY>* current = new Node<T,KEY>(arr[0]->data,arr[0]->key);
        current->parent = nullptr;
        current->left = nullptr;
        current->right = nullptr;
        current->height = calculateHeight(current);
        return current;
    }

    Node<T,KEY>* node = new Node<T,KEY>( arr[arrSize / 2]->data, arr[arrSize / 2]->key);
    //preorder
    int i = arrSize % 2 == 0 ? arrSize-arrSize/2 : arrSize-arrSize/2 -1;
    node->left = arrayToTreeAux(arr, i);
    if (node->left != nullptr)
        node->left->parent = node;
    int arrLengthRight = arrSize-arrSize/2 -1;
    node->right = arrayToTreeAux(arr + arrSize / 2 + 1, arrLengthRight);
    if (node->right != nullptr)
        node->right->parent = node;

    node->height = calculateHeight(node);
    return node;
}


template<class T, typename KEY>
int AVLTree<T, KEY>::extractInOrder(Node<T, KEY> *node, Node<T, KEY>** arr) {
    if (node == nullptr || arr == nullptr)
        return 0;
    int i = 0;

    i += extractInOrder(node->left, arr);
    arr[i] =  node;
    i++;
    i += extractInOrder(node->right, arr + i);
    return i;
}

template<class T, typename KEY>
int AVLTree<T, KEY>::getNumberOfNodes() const {
    return numNodes;
}

template<class T, typename KEY>
AVLTree<T, KEY>* AVLTree<T, KEY>::mergeTrees(AVLTree<T, KEY>* tree2)
{
    int numOfPlayers1 = this->getNumberOfNodes();
    int numOfPlayers2 = tree2->getNumberOfNodes();
    Node<T, KEY>** players1 = new Node<T, KEY>*[numOfPlayers1];
    Node<T, KEY>** players2 = new Node<T, KEY>*[numOfPlayers2];
    Node<T, KEY>** combined = new Node<T, KEY>*[numOfPlayers1 + numOfPlayers2];

    this->extractInOrder(this->getRoot(),players1);
    tree2->extractInOrder(tree2->getRoot(),players2);

    mergeArrays(players1, numOfPlayers1,players2,numOfPlayers2 ,combined);

    AVLTree<T, KEY>* mergedTree = this->arrayToTree(combined, numOfPlayers1 + numOfPlayers2); //allocates memory
    mergedTree->numNodes = numOfPlayers2 + numOfPlayers1;
    delete[] players1;
    delete[] players2;
    delete[] combined;
    return mergedTree;

}

template<class T, typename KEY>
void AVLTree<T, KEY>::mergeArrays(Node<T, KEY>** arr1, int arr1Size, Node<T, KEY>** arr2,int arr2Size, Node<T, KEY>** output)
{
    //output size should be arr1Size + arr2Size
    int ptr1 = 0, ptr2 = 0, ptr = 0;
    while (ptr1 < arr1Size && ptr2 < arr2Size)
    {
        if (arr1[ptr1]->key < arr2[ptr2]->key)
        {
            output[ptr] = arr1[ptr1];
            ptr1++;
        }
        else
        {
            output[ptr] = arr2[ptr2];
            ptr2++;
        }
        ptr++;
    }
    while (ptr1 < arr1Size)
    {
        output[ptr] = arr1[ptr1];
        ptr1++;
        ptr++;
    }
    while (ptr2 < arr2Size)
    {
        output[ptr] = arr2[ptr2];
        ptr2++;
        ptr++;
    }
}

template<class T, typename KEY>
T *AVLTree<T, KEY>::findClosestRight(Node<T, KEY> *node) {
    if(node== nullptr)
        return nullptr;
    Node<T,KEY>* closest= nullptr;
    Node<T,KEY>* temp= node;
    //check left to the right
    temp=node->left;
    if(temp!= nullptr) {
        while (temp->right != nullptr) {
            temp = temp->right;
        }
    }
    if((temp!= nullptr) && temp->key > node->key)
    {
        closest=temp;
    }
    //check right to the left
    temp=node->right;
    if(temp!= nullptr) {
        while (temp->left != nullptr) {
            temp = temp->left;
        }
    }
    if((temp!= nullptr) && temp->key>node->key)
    {
        if((closest!= nullptr && temp->key<closest->key)|| closest== nullptr)
            closest=temp;
    }
    //all the way back to the parent
    temp=node->parent;
    while (temp!= nullptr)
    {
        if(temp->key>node->key)
        {
            if((closest!= nullptr && temp->key<closest->key )|| closest== nullptr)
                closest=temp;
        }
        temp=temp->parent;
    }
    if(closest!= nullptr)
        return &(closest->data);
    return nullptr;
}

template<class T, typename KEY>
T *AVLTree<T, KEY>::findClosestLeft(Node<T, KEY> *node) {
    if(node== nullptr)
        return nullptr;
    Node<T,KEY>* closest= nullptr;
    Node<T,KEY>* temp= node;
    //check left to the right
    temp=node->left;
    if(temp!= nullptr) {
        while (temp->right != nullptr) {
            temp = temp->right;
        }
    }
    if((temp!= nullptr) && temp->key < node->key)
    {
        closest=temp;
    }
    //check right to the left
    temp=node->right;
    if(temp!= nullptr) {
        while (temp->left != nullptr) {
            temp = temp->left;
        }
    }
    if((temp!= nullptr) && temp->key<node->key)
    {
        if((closest!= nullptr && temp->key>closest->key)|| closest== nullptr)
            closest=temp;
    }
    //all the way back to the parent
    temp=node->parent;
    while (temp!= nullptr)
    {
        if((temp!= nullptr) && temp->key<node->key)
        {
            if((closest!= nullptr && temp->key>closest->key )|| closest== nullptr)
                closest=temp;
        }
        temp=temp->parent;
    }
    if(closest!= nullptr)
        return &(closest->data);
    return nullptr;
}

template<class T, typename KEY>
Node<T, KEY>* AVLTree<T, KEY>::getSubTree(Node<T,KEY>* node, KEY min, KEY max, Node<T, KEY> ** keepLastHere)
{
    if (node == nullptr)
        return nullptr;

    if (node->key > max)
        return getSubTree(node->left, min, max, keepLastHere);
    if (node->key < min)
        return getSubTree(node->right, min, max, keepLastHere);

    if (node->right == nullptr && node->left == nullptr)
    {
        Node<T,KEY>* lastNode = new Node<T,KEY>(node->data,node->key);
        *keepLastHere = lastNode;
        lastNode->parent = nullptr;
        return lastNode;
    }
    Node<T,KEY>* linkedList;
    Node<T,KEY>* currentNode = new Node<T,KEY>(node->data,node->key);
    currentNode->parent = nullptr;
    linkedList = currentNode;
    Node<T,KEY>* linkedListLeft = getSubTree(node->left, min, max, keepLastHere);

    if (linkedListLeft != nullptr)
    {
        linkedListLeft->parent = nullptr;
        (*keepLastHere)->right = currentNode;
        linkedList = linkedListLeft;
    }
    *keepLastHere = currentNode;
    Node<T, KEY> * previous = *keepLastHere;
    Node<T,KEY>* linkedListRight = getSubTree(node->right, min, max, keepLastHere);
    if (linkedListRight != nullptr)
        linkedListRight->parent = nullptr;
    Node<T, KEY> * temp = *keepLastHere;
    if (previous != nullptr)
        previous->right = linkedListRight;
    *keepLastHere = temp;
    (*keepLastHere)->right = nullptr;
    return linkedList;
}

#endif //DATA_STRUCTURES_AVLTREE_H
