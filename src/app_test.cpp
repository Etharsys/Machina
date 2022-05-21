#include <iostream>

#include "logger.hpp"
#include "FileReader.hpp"
#include "ReaderException.hpp"

void parseArgs(int argc, char const* argv[])
{
    if (argc != 1)
    {
        error("should not have arguments", "args are : ");
        for (auto i = 0; i < argc; ++i)
        {
            debug(argv[i]);
        }
        throw "IllegalArgumentException";
    }
}

int main(int argc, char const *argv[])
{
    try {
        parseArgs(argc, argv);
    } catch (const std::string& message) {
        return 0;
    }

    FileReader reader { "test" };
    reader.open();

    try {
        for(MachinaExpression v : reader.read())
        {
            std::cout << v << std::endl;
        }
    } catch (ReaderException& e) {
        error(e.what());
    }
    
    return 0;
}
