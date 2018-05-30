#pragma once

#include <QList>

namespace Tree {

template<typename>
struct Node;

template<typename T>
using Nodes = QList<Node<T>>;

template<typename T>
struct Node {
    T data;
    Nodes<T> children;
    Node<T> *parent;
};

}

template<typename T>
bool operator==(const Tree::Node<T> &lhs, const Tree::Node<T> &rhs) {
    return lhs.data == rhs.data;
}
