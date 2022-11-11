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
    infos(path);
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

vector<string> FileReader::read() {
    if (!_fileStream.is_open()) {
        throw ReaderException { "Machina file is not open" };
    }
    vector<string> lines;
    string line;
    while(getline(_fileStream, line)) {
        line = trim(line);
        if (isLineIgnored(line)) {
            continue;
        }
        lines.push_back(line);
    }
    return lines;
}
