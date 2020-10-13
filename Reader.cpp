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
            if (c == '\n' or c == '\t')
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

    if (update)
        guis->Clear();

    GuiFormat* format = new GuiFormat();
    while (!f.eof())
    {
        std::string var;
        std::string lit;
        f >> var;
        if (var == "Name")
        {
            f >> lit;
            format->Name = lit;
        }
        if (var == "Texture")
        {
            f >> lit;
            format->TextureId = std::stoi(lit);
        }
        if (var == "CenterPoint")
        {
            std::string lit[2];
            f >> lit[0];
            f >> lit[1];
            format->Position = glm::vec2(std::stof(lit[0]), std::stof(lit[1]));
        }
        if (var == "Scale")
        {
            std::string lit[2];
            f >> lit[0];
            f >> lit[1];
            format->Scale = glm::vec2(std::stof(lit[0]), std::stof(lit[1]));
        }
        if (var == "Color")
        {
            std::string lit[4];
            f >> lit[0];
            f >> lit[1];
            f >> lit[2];
            f >> lit[3];
            format->Color = glm::vec4(std::stof(lit[0]), std::stof(lit[1]), std::stof(lit[2]), std::stof(lit[3]));
        }
        if (var == "PUSH")
        {
            guis->Add(format);
            format = new GuiFormat();
        }
        if (var == "PUSH_EUI")
        {
            guis->Add(format);
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
