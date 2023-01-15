#include "Tree.hpp"

#include <iostream>

#include "logger.hpp"

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

void Tree::addChild(string key, vector<string> keyValues, int filePosition) {
    _currentNode->addChild(key, keyValues, filePosition);
}

void Tree::addAndMoveToChild(string key, vector<string> keyValues, int filePosition) {
    _currentNode = _currentNode->addChild(key, keyValues, filePosition);
}

inline string displayNode(Node node) {
    string nodeString = node.getKey();
    const std::vector<std::string> values = node.getKeyValues();
    if (!values.empty()) {
        nodeString = nodeString.append(" -> ");
        for_each(values.begin(), values.end(), [&nodeString](const std::string& value) { nodeString = nodeString.append(value + " "); });
    }
    return nodeString;
}

inline void displayTreeLine(Node node) {
    string line = "";
    for (int i = 0; i < node.getDepth(); ++i) {
        line = line.append(" | ");
    }
    if (node.isLeaf()) {
        log(line.append(displayNode(node)));
        return;
    }
    log(line.append(displayNode(node)));
    const auto children = node.getChildren();
    for_each(children.begin(), children.end(), [&line](const Node& child) { displayTreeLine(child); });
}

void Tree::display() {
    log("Final parsed tree (from root) : ");
    displayTreeLine(getRoot());
}

/* ------------------------- */

Node::Node()
    : _key { "root" }, _depth { 0 }, _parent { nullptr }
    { }

Node::Node(string key, int depth, vector<string> keyValues, int filePosition, shared_ptr<Node> parent)
    : _key { key }, _depth { depth }, _keyValues { keyValues }, _filePosition { filePosition }, _parent { parent }
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

int Node::getFilePosition() {
    return _filePosition;
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

shared_ptr<Node> Node::addChild(string key, vector<string> keyValues, int filePosition) {
    shared_ptr<Node> child_ptr = make_shared<Node>(Node(key, _depth+1, keyValues, filePosition, shared_from_this()));
    _children.push_back(child_ptr);
    return child_ptr;
}

bool Node::isNode() {
    return getChildren().size() > 0;
}

bool Node::isLeaf() {
    return getChildren().size() == 0;
}
