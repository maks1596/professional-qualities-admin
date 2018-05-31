#pragma once

#include <QList>
#include <QSharedPointer>

namespace Tree {

template<typename>
struct Node;

template<typename T>
using NodePtr = QSharedPointer<Node<T>>;

template<typename T>
using NodePtrs = QList<NodePtr<T>>;

template<typename T>
struct Node {
    Node()
        : data(),
          parent(nullptr)
    {}

    T data;
    NodePtrs<T> children;
    NodePtr<T> parent;

    bool mapped = false;
};

template<typename T>
bool operator==(const Tree::Node<T> &lhs, const Tree::Node<T> &rhs) {
    return lhs.data == rhs.data;
}

template<typename T>
bool operator==(const Tree::NodePtr<T> &lhs, const Tree::NodePtr<T> &rhs) {
    return *lhs == *rhs;
}
}



