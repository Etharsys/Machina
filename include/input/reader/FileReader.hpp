#pragma once

#include <string_view>
#include <filesystem>
#include <fstream>

#include "logger.hpp"
#include "project_config.hpp"
#include "LineReader.hpp"

class FileReader 
{
    private:
        std::ifstream _file_stream;

        std::string _file_name;
        inline static std::string _prefix = "";
        inline static std::string _suffix = "";

    public:
        FileReader(std::string_view file_name)
            : _file_name { file_name }
        {
            _prefix = RESOURCES_PREFIX;
            _suffix = RESOURCES_SUFFIX;
        }

        static void set_prefix(std::string_view prefix) { _prefix = prefix; }
        static void set_suffix(std::string_view suffix) { _suffix = suffix; }

        void open();

        std::vector<MachinaExpression> read();
};