#include <iostream>
#include <cassert>
#include <memory>

#include "logger.hpp"
#include "FileReader.hpp"
#include "ReaderException.hpp"
#include "Parser.hpp"
#include "SyntacticParser.hpp"

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
    const std::vector<std::string> lines = reader.read();

    log("Start parsing syntax ...");
    SyntacticParser syntacticParser { lines };
    const std::vector<MachinaExpression> expressions = syntacticParser.parse();
    
    log("Start parsing grammar ...");
    Parser parser { expressions };
    parser.parse();
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