#include <FileReader.hpp>

using namespace std;

void FileReader::open()
{
    const string path = filesystem::current_path().string() + "" + _prefix + "" + _file_name + "" + _suffix;
    infos(path);
    _file_stream = ifstream { path.c_str() };
}

vector<MachinaExpression> FileReader::read() { 
    vector<MachinaExpression> expressions;
    if (_file_stream.is_open())
    {
        string line;
        while(getline(_file_stream, line))
        {
            LineReader line_reader { line };
            if (line_reader.skip()) continue;

            line_reader.parse();
            expressions.emplace_back(line_reader.get_m_expr());
        }
    }
    return expressions;
}