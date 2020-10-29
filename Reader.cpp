#include "Reader.h"

Reader Reader::mReader;

std::vector<std::string> Reader::getArray(std::string Path, std::string Keyword)
{    
    Clean();
    auto f = getStream(Path);
    std::vector<std::string> Result;
    GET_IFSTREAM_CHAR(
        if (mCheck)
        {
            if (c == '}')
            {
                mCheck = false;
                break;
            }
            if (c == ' ' or c == '=' or c == '{' or c == '\t' or c == '\n')
            {
                if (not mLiteral.empty())
                {
                    Result.push_back(mLiteral);
                    mLiteral.clear();
                }
                continue;
            }
            mLiteral += c;
        }
        if (tmp == Keyword)
        {
            mCheck = true;
        }
    )   

    f.close();
    return Result;
}

std::string Reader::getValue(std::string Path, std::string Keyword, int seek)
{
    Clean();
    auto f = getStream(Path);
    f.seekg(seek, std::ios::beg);
    std::string Result;
    GET_IFSTREAM_CHAR(        
        if (mCheck)
        {   
            if (c == '\n' or c == '\t' or c == '#')
            {
                return mLiteral;
                mCheck = false;
                break;
            }
            if (c == '=' || c == ' ')
            {
                continue;
            }
            mLiteral += c;
        }
        if (tmp == Keyword)
        {
            mCheck = true;
        }
    )
    f.close();
    return Result;
}

void Reader::getUI(GUITexture* guis, std::string path, bool update)
{
    auto f = getStream(path);
    f.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t, 0x10ffffUL, std::codecvt_mode::consume_header>));
    if (update)
        guis->Clear();

    GuiFormat* format = new GuiFormat();
    std::string line;
    while (std::getline(f, line))
    {
        try
        {
            auto lit = split(line, " ");
            if (lit.size() > 0)
            {
                if (lit[0] == "Name")
                    format->Name = lit[1];
                if (lit[0] == "Texture")
                    format->TextureId = std::stoi(lit[1]);
                if (lit[0] == "CenterPoint")
                    format->Position = glm::vec2(std::stof(lit[1]), std::stof(lit[2]));
                if (lit[0] == "Scale")
                    format->Scale = glm::vec2(std::stof(lit[1]), std::stof(lit[2]));
                if (lit[0] == "Color")
                    format->Color = glm::vec4(std::stof(lit[1]), std::stof(lit[2]), std::stof(lit[3]), std::stof(lit[4]));
                if (lit[0] == "Text")
                {
                    std::string result_text = "";

                    int index = 1;
                    while (true)
                    {
                        index++;
                        if (lit[index] == "]")
                            break;
                        result_text += " " + lit[index];
                    }
                    auto p1 = lit[++index];
                    auto p2 = lit[++index];
                    auto p3 = lit[++index];
                    auto p4 = lit[++index];
                    auto p5 = lit[++index];
                    auto p6 = lit[++index];
                    auto p7 = lit[++index];
                    Str str;
                    str.Text = result_text;
                    str.Position = glm::vec2(std::stof(p1), std::stof(p2));
                    str.Color = glm::vec4(std::stof(p3), std::stof(p4), std::stof(p5), std::stof(p6));
                    format->Text.emplace(
                        p7,
                        str
                    );
                }
                if (lit[0] == "Hover")
                    format->hoverColor = glm::vec4(std::stof(lit[1]), std::stof(lit[2]), std::stof(lit[3]), std::stof(lit[4]));
                if (lit[0] == "Visible")
                    format->Visible = std::stoi(lit[1]);
                if (lit[0] == "PUSH")
                {
                    guis->Add(format->Name, format);
                    format = new GuiFormat();
                }
                if (lit[0] == "PUSH_EUI")
                    guis->Add(format->Name, format);
            }
        }
        catch (std::exception& ex)
        {
            LOG(ERROR) << "UI: [" << path << "] - " << ex.what();
        }
    }

    f.close();
}

#ifdef _WIN32
void Reader::getFiles(std::string Path, std::vector<std::string>& Src)
{
    WIN32_FIND_DATAA FindFileData;
    HANDLE hFind;
    hFind = FindFirstFileA(Path.c_str(), &FindFileData);
    while (FindNextFileA(hFind, &FindFileData) != NULL)
        Src.push_back(FindFileData.cFileName);
    Src.erase(Src.begin());
    FindClose(hFind);    
}
#endif

std::ifstream Reader::getStream(std::string Path)
{
    std::ifstream f(Path);
    if (not f.is_open())
        LOG(ERROR) << std::string("Failed to open file " + Path);
    f >> std::skipws;
    return f;
}

void Reader::Clean()
{
    this->mCheck = false;
    this->mCurrentLine.clear();
    this->mLiteral.clear();
}

std::vector<std::string> Reader::split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}
