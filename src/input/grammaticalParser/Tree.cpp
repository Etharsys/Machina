#include "Tree.hpp"

#include <iostream>

using namespace std;

Tree::Tree()
    : _root { make_shared<Node>(Node()) }, _currentNode { _root }
    { }

Node Tree::getRoot() {
    return *_root;
}

Node Tree::getCurrentNode() {
    return *_currentNode;
}

bool Tree::isRoot() {
    return _root == _currentNode;
}

void Tree::moveToRoot() {
    _currentNode = _root;
}

void Tree::moveToParent() {
    _currentNode = _currentNode->getParent();
}

void Tree::addChild(string value) {
    _currentNode->addChild(value);
}

void Tree::addAndMoveToChild(string value) {
    _currentNode = _currentNode->addChild(value);
}

void Tree::display(Node node) {
    if (node.isLeaf()) {
        cout << node.getValue();
        return;
    }
    cout << node.getValue() << " [ ";
    for (Node& child: node.getChildren()) {
        display(child);
        cout << " ";
    }
    cout << "]";
    return;
}

/* ------------------------- */

Node::Node()
    : _value { "root" }, _parent { nullptr }
    { }

Node::Node(string value, shared_ptr<Node> parent)
    : _value { value }, _parent { parent }
    { }

string Node::getValue() {
    return _value;
}

shared_ptr<Node> Node::getParent() {
    return _parent;
}


vector<Node> Node::getChildren() {
    vector<Node> children;
    for (shared_ptr<Node>& node: _children) {
        children.push_back(*node);
    }
    return children;
}


vector<string> Node::getChildrenValue() {
    vector<string> children;
    for (shared_ptr<Node>& node: _children) {
        children.push_back(node->getValue());
    }
    return children;
}

shared_ptr<Node> Node::addChild(string value) {
    shared_ptr<Node> child_ptr = make_shared<Node>(Node(value, shared_ptr<Node>(this)));
    _children.push_back(child_ptr);
    return child_ptr;
}

bool Node::isNode() {
    return getChildren().size() > 0;
}

bool Node::isLeaf() {
    return getChildren().size() == 0;
}

    
