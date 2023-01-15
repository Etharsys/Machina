#pragma once

#include <vector>
#include <string>
#include <memory>

class Node : public std::enable_shared_from_this<Node> {

  private:
      std::string _key;
      int _filePosition; // TODO : key and file position can be the same object
      int _depth;
      std::vector<std::string> _keyValues {};
      std::shared_ptr<Node> _parent;
      std::vector<std::shared_ptr<Node>> _children {};

      Node(std::string key, int depth, std::vector<std::string> keyValues, int filePosition, std::shared_ptr<Node> parent);

  public:
      Node();

      std::string getKey();

      int getDepth();

      std::vector<std::string> getKeyValues();

      int getFilePosition();

      std::shared_ptr<Node> getParent();

      std::vector<Node> getChildren();

      std::vector<std::string> getChildrenKeys();

      std::shared_ptr<Node> addChild(std::string key, std::vector<std::string> keyValues, int filePosition);

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

      void addChild(std::string key, std::vector<std::string> keyValues, int filePosition);

      void addAndMoveToChild(std::string key, std::vector<std::string> keyValues, int filePosition);
      
      void display();
};
