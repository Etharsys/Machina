#include "Generator.hpp"

#include <algorithm>

using namespace std;

Generator* Generator::getInstance() {
    if (_instance == nullptr) {
        _instance = new Generator{};
    }
    return _instance;
}

Generator::Generator() {}

Main Generator::generate(const Tree& tree) {
    Main main{};
    // main.generate(tree);
    return main;
}

/*
inline void genTmp(Node node) {
    if (node.isLeaf()) {
        return;
    }
    const auto children = node.getChildren();
    for_each(children.begin(), children.end(), [](const Node& child) { genTmp(child); });
}
*/

// chaque IGen sait comment il se génère
// donc les fonctions d'IGen s'appelent entres elles avec l'arbre

// je pense qu'on peut def 3 cas : 
// 1 si nombre finit t => très facile / naturel (1 menu à des champs bien définit)
// 2 si nombre indéfini n => switch ? (1 menus a un t[menu] de longueur n)
// 3 si enfant optionnels ... => ... (un champ sstitre dans menu optionnel) => (for_each sur children et emplace si existent)

// en fait : non !
// => on for_each tout le temps sur les children pour se délier de l'ordre des enfants
// du coup on gère 1 et 3 de la même manière
// je pense que le cas 2 n'est pas exact en réalité parce que:
//   -> s'il s'agit d'un tableau d'enfants t[enfants] (comme menu dans menus) le for_each devrait suffire avec une cond en +
//   -> s'il s'agit d'un tableau d'enfants non définit t[gen] (comme menus, loop... dans main) 
//      alors en réalité il s'agit d'optionel d'éléments à définir dans la grammaire, ainsi le for_each switch devrait suffire