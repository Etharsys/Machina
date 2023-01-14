#pragma once

#include <string_view>
#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>

#include "logger.hpp"
#include "project_config.hpp"
#include "ReaderException.hpp"

class FileReader {
    private:
        std::ifstream _fileStream;
        std::string _fileName;
        inline static std::string _prefix = "";
        inline static std::string _suffix = "";

        /**
         * @brief delete useless spaces
         * 
         * @param line the current line to trim
         * @return const std::string the line which has been trimed
         */
        const std::string trim(std::string line);

        /**
         * @brief check if the line is empty or if the line is a comment
         * 
         * @param line the current line to check
         * @return true 
         * @return false 
         */
        bool isLineIgnored(const std::string& line);

    public:

        /**
         * @brief Construct a new File Reader object
         * 
         * @param fileName the name of the file to read
         */
        FileReader(std::string_view fileName);

        /**
         * @brief Set the relative file path prefix
         * 
         * @param prefix 
         */
        static void setPrefix(std::string_view prefix);

        /**
         * @brief Set the relative file path prefix
         * 
         * @param suffix 
         */
        static void setSuffix(std::string_view suffix);

        /**
         * @brief open the file to read
         * 
         */
        void open();

        /**
         * @brief read the file
         * 
         * @return std::vector<std::string> the lines of the file
         * 
         * @throw ReaderException if the file is not opened
         */
        std::vector<std::string> read();
};