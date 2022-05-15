#include <FileReader.hpp>

using namespace std;

void FileReader::open()
{
    const string path = filesystem::current_path().string() + "" + _prefix + "" + _file_name + "" + _suffix;
    infos(path);
    _file_stream = ifstream { path.c_str() };
}

vector<MachinaExpression> FileReader::read() 
{ 
    vector<MachinaExpression> expressions;
    if (_file_stream.is_open())
    {
        string line;
        u_int index = 0;
        while(getline(_file_stream, line))
        {
            index++;
            LineReader line_reader { line };
            try 
            {
                if (line_reader.skip()) continue;
                line_reader.parse();
            } catch (ReaderException& e) 
            {
                throw ReaderException(string(e.what()) 
                    + " (at line " + to_string(index) + " -> '" + line +  "')");
            }
            expressions.emplace_back(line_reader.get_m_expr());
        }
    } else 
    {
        throw ReaderException("Machina file is not open");
    }
    return expressions;
}