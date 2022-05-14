#include "logger.hpp"

#include <FileReader.hpp>

#include <iostream>

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
    } catch (const char* message) {
        return 0;
    }

    FileReader reader { "test" };
    reader.open();
    
    for(MachinaExpression v : reader.read())
    {
        std::cout << v << std::endl;
    }

    return 0;
}
