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

// chaque IGen sait comment il se g�n�re
// donc les fonctions d'IGen s'appelent entres elles avec l'arbre

// je pense qu'on peut def 3 cas : 
// 1 si nombre finit t => tr�s facile / naturel (1 menu � des champs bien d�finit)
// 2 si nombre ind�fini n => switch ? (1 menus a un t[menu] de longueur n)
// 3 si enfant optionnels ... => ... (un champ sstitre dans menu optionnel) => (for_each sur children et emplace si existent)

// en fait : non !
// => on for_each tout le temps sur les children pour se d�lier de l'ordre des enfants
// du coup on g�re 1 et 3 de la m�me mani�re
// je pense que le cas 2 n'est pas exact en r�alit� parce que:
//   -> s'il s'agit d'un tableau d'enfants t[enfants] (comme menu dans menus) le for_each devrait suffire avec une cond en +
//   -> s'il s'agit d'un tableau d'enfants non d�finit t[gen] (comme menus, loop... dans main) 
//      alors en r�alit� il s'agit d'optionel d'�l�ments � d�finir dans la grammaire, ainsi le for_each switch devrait suffire