#include <iostream>
#include <cassert>
#include <memory>

#include "logger.hpp"
#include "FileReader.hpp"
#include "ReaderException.hpp"
#include "GrammaticalParser.hpp"
#include "SyntacticParser.hpp"
#include "Main.hpp"
#include "Generator.hpp"
#include "Tree.hpp"

void parseArgs(int argc, char const* argv[]) {
    if (argc != 1) {
        error("should not have arguments", "args are : ");
        for (auto i = 0; i < argc; ++i) {
            debug(argv[i]);
        }
        throw "IllegalArgumentException";
    }
}

void test() {
    log("Start reading program '" + std::string(TEST_PROGRAM) + "' ... ");
    FileReader reader { std::string(TEST_PROGRAM) };
    reader.open();
    const std::vector<std::pair<int, std::string>> lines = reader.read();

    log("Start parsing syntax ...");
    SyntacticParser syntacticParser { lines };
    const std::vector<MachinaExpression> expressions = syntacticParser.parse();
    
    log("Start parsing grammar ...");
    GrammaticalParser* parser = GrammaticalParser::getInstance(expressions);
    const Tree tree = parser->parse();
    
    log("Start generator ...");
    Generator* generator = Generator::getInstance();
    Main main = generator->generate(tree);

    log("Start Machina program ...");
    main.fakeLoop();
}

int main(int argc, char const *argv[]) {
    try {
        parseArgs(argc, argv);
    } catch (const std::string& message) {
        error(message);
        return 1;
    }
    test();
    return 0;
}