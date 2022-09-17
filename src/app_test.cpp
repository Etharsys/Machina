#include <iostream>
#include <cassert>

#include "logger.hpp"
#include "FileReader.hpp"
#include "ReaderException.hpp"
#include "iostream"

void parseArgs(int argc, char const* argv[]) {
    if (argc != 1) {
        error("should not have arguments", "args are : ");
        for (auto i = 0; i < argc; ++i) {
            debug(argv[i]);
        }
        throw "IllegalArgumentException";
    }
}

void hard_loop() {
    using namespace std;

    string cli_input;
    while(true) {
	    getline(cin, cli_input);
        if (cli_input.size() == 1 && cli_input.at(0) == 113)
		{
			cout << "Game ended, quiting ... ";
            break;
		}

        // DO A LOT OF THINGS

        cout << "HEY" << endl;
    }
}

void test() {
    FileReader reader { "test" };
    reader.open();

    try {
        for(MachinaExpression v : reader.read())
        {
            std::cout << v << std::endl;
        }
    } catch (ReaderException& e) {
        error(e.what());
        return;
    }

    hard_loop();
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
