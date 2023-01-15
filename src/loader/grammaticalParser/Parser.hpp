#pragma once

#include <vector>
#include <stack>

#include "Grammar.hpp"
#include "MachinaExpression.hpp"
#include "Tree.hpp"

namespace Statuses {
    /**
     * @brief represent a grammatical behaviour to parse
     */
    enum Statuses { 
        Parent, 
        OpeningBrace, 
        Body, 
        ClosingBrace 
    };

    const std::string statuses_str[] = { "Parent", "OpeningBrace", "Body", "ClosingBrace" };
}

using grammarValues = std::vector<std::pair<std::string, std::string>>;

class Parser {

    private:
        inline static Parser* _instance = nullptr;
        Tree _tree {};
        std::string _currentNodeKey;

        Statuses::Statuses _status;

        std::vector<MachinaExpression> _expressions;
        std::vector<MachinaExpression>::iterator _currentExpressionIterator;
        std::string _currentExpressionKey;
        int _currentExpressionFilePosition;
        std::vector<std::string> _currentExpressionKeyValues;

        Grammar* grammar = Grammar::getInstance();

        std::stack<grammarValues> _grammarResult = {};

        /**
         * @brief Construct a new Parser object
         * 
         * @param expressions list of expression (parsed by the syntactic parser)
         */
        Parser(const std::vector<MachinaExpression>& expressions);

        /**
         * @brief move _currentExpressionIterator
         * 
         */
        void fetchNextExpression();

        /**
         * @brief check is the token with name key exist in the grammar 
         * and return the assiociated value
         * 
         * @param key the key to check
         * @throw GrammaticalParserException when key does not exist
         * @return grammarValues& values associated to the key
         */
        grammarValues checkAndGetGrammarValuesByKey(const std::string& key);

        /**
         * @brief process to check if a token associated to a grammar key is rightly setup
         * 
         * @param values set of values associated to a key
         * @param keyIterator the token iterator in the grammar to process
         * @throw GrammaticalParserException when keyIterator does not exist
         * @throw GrammaticalParserException when keyIterator has already been setup
         */
        void checkKeyIterator(grammarValues& values, const grammarValues::iterator& keyIterator);

        /**
         * @brief parse computation when parser has is Statuses set to 'Parent'
         *  
         * @throw GrammaticalParserException with call to checkToken with _currentExpressionKey
         */
        void parseParent();

        /**
         * @brief parse computation when parser has is Statuses set to 'OpeningBrace'
         * 
         * @throw GrammaticalParserException when no opening brace is provided
         */
        void parseOpeningBrace();

        /**
         * @brief parse computation when parser has is Statuses set to 'Body'
         * 
         * @throw GrammaticalParserException with call to checkKeyIterator
         */
        void parseBody();

        /**
         * @brief parse computation when parser has is Statuses set to 'ClosingBrace'
         * 
         * @throw GrammaticalParserException when a token associated to a key is missing
         */
        void parseClosingBrace();

        /**
         * @brief process a step (parsing one MachinaExpression) using a current status
         * 
         * @throw GrammaticalParserExcpetion with call of parseParent, parseOpeningBrace, 
         *        parseBody and parseClosingBrace
         */
        void validateGrammar();

    public:
        Parser(Parser &other) = delete;

        void operator=(const Parser &) = delete;

        static Parser *getInstance(const std::vector<MachinaExpression>& expressions);

        /**
         * @brief process the parsing 
         * 
         * @throw GrammaticalParserException when an opening brace has not been closed
         */
        void parse();

};
