#include <FileReader.hpp>


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

const optional<MachinaExpression> FileReader::checkLine(const string& line, u_int& index) {
    index++;
    LineReader lineReader { line };
    try {
        if (lineReader.skip()) {
            return nullopt;
        }
        lineReader.parse();
    } catch (const ReaderException& e) {
        throw ReaderException { string(e.what()) + " (at line " + to_string(index) + " -> '" + line +  "')" };
    }
    return lineReader.getMachinaExpression();
}

vector<MachinaExpression> FileReader::read() { 
    if (!_fileStream.is_open()) {
        throw ReaderException { "Machina file is not open" };
    }
    vector<MachinaExpression> expressions;
    string line;
    u_int index = 0;
    while(getline(_fileStream, line)) {
        optional<MachinaExpression> res = checkLine(line, index);
        if (res.has_value()){
            expressions.emplace_back(res.value());
        }
    }
    return expressions;
}