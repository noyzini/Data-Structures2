#ifndef DATA_STRUCTURES_NODE_H
#define DATA_STRUCTURES_NODE_H

template<class T,typename KEY>
class Node {
public:
    Node(T& data,KEY& key, Node* parent = nullptr);

    T data;
    KEY key;//we assume key is a type with < > operators
    Node* right;
    Node* left;
    Node* parent;
    int height;
};

template<class T, typename KEY>
Node<T, KEY>::Node(T& data, KEY& key, Node* parent):
        data(data),key(key),right(nullptr),left(nullptr),parent(parent) , height(1)
{}



#endif //DATA_STRUCTURES_NODE_H
