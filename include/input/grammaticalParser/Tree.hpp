#pragma once

#include<vector>
#include<string>
#include <memory>

class Node {
  private:
      std::string _value;
      std::shared_ptr<Node> _parent;
      std::vector<std::shared_ptr<Node>> _children {};

      Node(std::string value, std::shared_ptr<Node> parent);

  public:
      Node();

      std::string getValue();
      std::shared_ptr<Node> getParent();
      std::vector<Node> getChildren();
      std::vector<std::string> getChildrenValue();
      std::shared_ptr<Node> addChild(std::string value);
      bool isNode();
      bool isLeaf();
};

class Tree {
  private:
      std::shared_ptr<Node> _root;
      std::shared_ptr<Node> _currentNode;

  public:
      Tree();

      Node getRoot();
      Node getCurrentNode();
      bool isRoot();
      void moveToRoot();
      void moveToParent();
      void addChild(std::string value);
      void addAndMoveToChild(std::string value);
      void display(Node node);
};