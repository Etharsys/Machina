#pragma once

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <functional>


using pairSS = std::pair<std::string, std::string>;
using grammarValues = std::vector<pairSS>;
using grammarType = std::map<std::string, grammarValues>;

class Grammar {
    private:
        inline static Grammar* _instance = nullptr;

        const std::string DEFAULT_VALUE = "#NONE";
        grammarType _grammar = {};

        Grammar();

        /**
         * @brief callback vector of all main keys
         * 
         */
        const std::vector<std::function<void(void)>> callbackContainer {
            [this]{ emplaceMenu(); },
            [this]{ emplaceButton(); }
        };

        void emplaceMenu();

        void emplaceButton();

    public:
        Grammar(Grammar &other) = delete;
        void operator=(const Grammar &) = delete;

        /**
         * @brief Get the Instance object (singleton)
         * 
         * @return Grammar* 
         */
        static Grammar *getInstance();

        /**
         * @brief get the real grammar map
         * 
         * @return const grammarType 
         */
        const grammarType get();

        /**
         * @brief get a machina default value 
         * 
         * @return const std::string 
         */
        const std::string defaultValue();

};
