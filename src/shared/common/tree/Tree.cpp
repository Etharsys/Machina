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

void Tree::addChild(string key, vector<string> keyValues) {
    _currentNode->addChild(key, keyValues);
}

void Tree::addAndMoveToChild(string key, vector<string> keyValues) {
    _currentNode = _currentNode->addChild(key, keyValues);
}

void displayVector(vector<string> keyValues) {
    cout << " { ";
    for_each(keyValues.begin(), keyValues.end(), [](const string& value) { cout << value << " "; });
    cout << "}";
}

void Tree::display(Node node) {
    if (node.isLeaf()) {
        cout << node.getKey();
        displayVector(node.getKeyValues());
        return;
    }
    cout << node.getKey();
    displayVector(node.getKeyValues());
    cout << " [ ";
    for (Node& child: node.getChildren()) {
        display(child);
        cout << " ";
    }
    cout << "]";
    return;
}

/* ------------------------- */

Node::Node()
    : _key { "root" }, _parent { nullptr }
    { }

Node::Node(string key, vector<string> keyValues, shared_ptr<Node> parent)
    : _key { key }, _keyValues { keyValues }, _parent { parent }
    { }

string Node::getKey() {
    return _key;
}

vector<string> Node::getKeyValues() {
    return _keyValues;
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


vector<string> Node::getChildrenKeys() {
    vector<string> children;
    for (shared_ptr<Node>& node: _children) {
        children.push_back(node->getKey());
    }
    return children;
}

shared_ptr<Node> Node::addChild(string key, vector<string> keyValues) {
    shared_ptr<Node> child_ptr = make_shared<Node>(Node(key, keyValues, shared_from_this()));
    _children.push_back(child_ptr);
    return child_ptr;
}

bool Node::isNode() {
    return getChildren().size() > 0;
}

bool Node::isLeaf() {
    return getChildren().size() == 0;
}

    
