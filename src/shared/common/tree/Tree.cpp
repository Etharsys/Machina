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

void Tree::displayNode(Node node) {
    cout << node.getKey();
    const vector<string> values = node.getKeyValues();
    if (values.empty()) {
        return;
    }
    cout << " -> ";
    for_each(values.begin(), values.end(), [](const string& value) { cout << value << " "; });
}

void Tree::displayTree(Node node) {
    for (int i = 0; i < node.getDepth(); ++i) {
        cout << " | ";
    }
    if (node.isLeaf()) {
        displayNode(node);
        return;
    }
    displayNode(node);
    const auto children = node.getChildren();
    for_each(children.begin(), children.end(), [this](const Node& child) { cout << "\n"; displayTree(child); });
    return;
}

void Tree::display(Node node) {
    displayTree(node);
    cout << "\n";
}

/* ------------------------- */

Node::Node()
    : _key { "root" }, _depth { 0 }, _parent { nullptr }
    { }

Node::Node(string key, int depth, vector<string> keyValues, shared_ptr<Node> parent)
    : _key { key }, _depth { depth }, _keyValues { keyValues }, _parent { parent }
    { }

string Node::getKey() {
    return _key;
}

int Node::getDepth() {
    return _depth;
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
    shared_ptr<Node> child_ptr = make_shared<Node>(Node(key, _depth+1, keyValues, shared_from_this()));
    _children.push_back(child_ptr);
    return child_ptr;
}

bool Node::isNode() {
    return getChildren().size() > 0;
}

bool Node::isLeaf() {
    return getChildren().size() == 0;
}

    
