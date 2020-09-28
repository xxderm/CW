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

std::string Reader::getValue(std::string Path, std::string Keyword)
{
    Clean();
    auto f = getStream(Path);
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
