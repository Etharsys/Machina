#pragma once

#include <string>
#include <vector>

#include "MachinaExpression.hpp"

class SyntacticParser {

    private:
        std::vector<MachinaExpression> _expressions {};
        std::vector<std::string> _lines;

        /**
         * @brief split a line with according to a delimiter
         * 
         * @param line the line to split
         * 
         * @param delimiter the delimiter to apply
         * 
         * @return const std::vector<std::string> the result of the split
         */
        const std::vector<std::string> split(std::string line, std::string_view delimiter);

        /**
         * @brief parse the line's arguments
         * 
         * @param currentLine the line which is currently parsed
         * 
         * @throw SyntacticParserException if there is no argument
         */
        void parseArgument(std::string currentLine);

    public:

        /**
         * @brief Construct a new Syntactic Parser object
         * 
         * @param lines list of lines (readed by the file reader)
         */
        SyntacticParser(const std::vector<std::string>& lines);

        /**
         * @brief process the parsing
         * 
         * @return const std::vector<MachinaExpression> the lines which has been converted to machina expression
         * 
         * @throw SyntacticParserException when the character ':' is at the beginning of a line
         */
        const std::vector<MachinaExpression> parse();
};
