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
NodePtr<T> makeNodePtr(const T &data = T(),
                       const NodePtr<T> &parent = NodePtr<T>(nullptr));

template<typename T>
class Node {
public:

    //  :: Lifecycle ::

    Node(const T &data = T(),
         const NodePtr<T> &parent = NodePtr<T>(nullptr))
        : m_data(data),
          m_parent(parent)
    {}

    //  :: Accessors ::

    const T &getData() const{
        return m_data;
    }
    T &getData() {
        return m_data;
    }
    void setData(const T &data) {
        m_data = data;
    }

    NodePtr<T> getParent() const {
        return m_parent;
    }
    void setParent(const NodePtr<T> &parent) {
        m_parent = parent;
    }

    NodePtrs<T> getChildren() const {
        return m_children;
    }
    void setChildren(const NodePtrs<T> &children) {
        m_children.clear();
        addChildren(children);
    }

    bool isMapped() const {
        return  m_mapped;
    }
    void setMapped(bool mapped) {
        m_mapped = mapped;
    }

    //  :: Methods ::

    void addChildren(const NodePtrs<T> &children) {
        for (const auto &child : children) {
            addChild(child);
        }
    }

    void addChild(const NodePtr<T> &child) {
        m_children.append(child);
    }

    void addChild(const T &child) {
        addChild(makeNodePtr(child));
    }

    int childrenCount() const {
        return m_children.size();
    }

    bool hasChildren() const {
        return !m_children.isEmpty();
    }

    const NodePtr<T> &child(int index) const {
        return m_children[index];
    }

    NodePtr<T> &child(int index) {
        return m_children[index];
    }

    bool hasParent() const {
        return !m_parent.isNull();
    }

private:
    T m_data;
    NodePtr<T> m_parent;
    NodePtrs<T> m_children;

    bool m_mapped = false;
};

template<typename T>
NodePtr<T> makeNodePtr(const T &data, const NodePtr<T> &parent) {
    auto nodePtr = new Tree::Node<T>(data, parent);
    return Tree::NodePtr<T>(nodePtr);
}

template<typename T>
bool operator==(const Node<T> &lhs, const Node<T> &rhs) {
    return lhs.getData() == rhs.getData();
}

template<typename T>
bool operator==(const NodePtr<T> &lhs, const NodePtr<T> &rhs) {
    return *lhs == *rhs;
}

}
