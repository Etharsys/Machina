#include "ButtonFactory.hpp"

#include <algorithm>
#include <vector>
#include <map>

#include "MenuManager.hpp"

using namespace std;

Button ButtonFactory::generate(Tree tree) {
    vector<Node> children = tree.getCurrentNode().getChildren();
    map<string, string> m;
    for_each(children.begin(), children.end(), [&m](Node child) {
        m.try_emplace(child.getKey(), child.getKeyValues()[0]);
    });
    return Button { 
        m.at(_description),
        stoi(m.at(_target))
    };
}