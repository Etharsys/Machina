#include "FileReader.hpp"

using namespace std;

FileReader::FileReader(string_view fileName) 
    : _fileName { fileName } {
    _prefix = RESOURCES_PREFIX;
    _suffix = RESOURCES_SUFFIX;
}

void FileReader::setPrefix(string_view prefix) {
    _prefix = prefix;
}

void FileReader::setSuffix(string_view suffix) {
    _suffix = suffix;
}

void FileReader::open() {
    const string path = filesystem::current_path().string() + "" + _prefix + "" + _fileName + "" + _suffix;
    log("Path to read at : " + path);
    _fileStream = ifstream { path.c_str() };
}

const string FileReader::trim(string line) {
    auto is_space = [](unsigned char const c) { return isspace(c); };
    line.erase(remove_if(line.begin(), line.end(), is_space), line.end());
    return line;
}


bool FileReader::isLineIgnored(const string& line) {
    return (line.empty() || line.at(0) == '#');
}

vector<pair<int, string>> FileReader::read() {
    if (!_fileStream.is_open()) {
        throw ReaderException { "Cannot open Machina file" };
    }
    int lineNumber = 0;
    vector<pair<int, string>> lines;
    string line;
    while(getline(_fileStream, line)) {
        line = trim(line);
        lineNumber++;
        if (isLineIgnored(line)) {
            continue;
        }
        log("Reading line (trimed & considered) : " + line);
        lines.push_back(make_pair(lineNumber, line));
    }
    return lines;
}
