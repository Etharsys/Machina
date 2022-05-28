#pragma once

#include <string_view>
#include <filesystem>
#include <fstream>
#include <optional>

#include "logger.hpp"
#include "project_config.hpp"
#include "LineReader.hpp"

class FileReader {
    private:
        std::ifstream _fileStream;
        std::string _fileName;
        inline static std::string _prefix = "";
        inline static std::string _suffix = "";

        const std::optional<MachinaExpression> checkLine(const std::string& line, u_int& index);

    public:
        FileReader(std::string_view fileName);

        static void setPrefix(std::string_view prefix);
        static void setSuffix(std::string_view suffix);

        void open();
        std::vector<MachinaExpression> read();
};