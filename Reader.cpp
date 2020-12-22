#include "Reader.h"

Reader Reader::mReader;

std::vector<std::string> Reader::getArray(std::string Path, std::string Keyword, bool isDigit)
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
            if ((c == ' ' or c == '=' or c == '{' or c == '\t' or c == '\n'))
            {
                if (not mLiteral.empty())
                {
                    Result.push_back(mLiteral);
                    mLiteral.clear();
                }
                continue;
            }       
            if (!isDigit)
                mLiteral += c;
            else if (isdigit(c))
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

std::vector<std::string> Reader::get2DArray(std::string Path, std::string Keyword, std::string key, std::string sep, bool isDigit)
{
    Clean();
    auto f = getStream(Path);
    std::vector<std::string> Result;
    bool inSecondDim = false;
    bool inKey = false;
    GET_IFSTREAM_CHAR(
        if (mCheck)
        {
            if (c == '}')
            {
                Result = split(mLiteral, sep);
                mLiteral.clear();
                inKey = false;
                inSecondDim = false;
                mCheck = false;
            }
            if (inKey)
            {
                mLiteral += c;
            }
            if (inSecondDim && c == '{')
            {
                inKey = true;
            }
            if (c == '{')
                inSecondDim = true;
        }
        if (!inSecondDim && tmp == Keyword)
        {
            mCheck = true;
        }
    )
    f.close();
    return Result;
}

std::vector<std::string> Reader::getFileLines(std::string Path)
{
    std::vector<std::string> result;
    std::string line;
    auto f = getStream(Path);
    while (std::getline(f, line))
        result.push_back(line);
    f.close();
    return result;
}

std::vector<std::string> Reader::getLangLines(std::string Path, std::string Keyword, std::string sep)
{
    std::vector<std::string> result;
    auto f = getStream(Path);

    while (getline(f, mCurrentLine))
    {         
        auto splitLine = split(mCurrentLine, sep);
        if (splitLine.size() > 0)
        {
            if (splitLine[0] == " " + Keyword)
                result.push_back(mCurrentLine);
        }        
    }

    f.close();
    return result;
}

std::string Reader::getValue(std::string Path, std::string Keyword, int seek, bool digit, bool skipws)
{
    Clean();
    auto f = getStream(Path);
    f.seekg(seek, std::ios::beg);
    std::string Result;
    GET_IFSTREAM_CHAR(
        if (int(c) < 0)
            continue;
        if (int(c) > 255)
            continue;
        if (mCheck)
        {   
            if (c == '\n' or c == '\t' or c == '#')
            {
                mCheck = false;
                return mLiteral;
            }
            if (c == '=' || (c == ' ' && skipws))
            {
                continue;
            }
            if (!isdigit(c) && !mLiteral.empty() && digit)
                return mLiteral;
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
                if (lit[0] == "#import")
                    this->getUI(guis, lit[1], false);
                if (lit[0] == "Name")
                    format->Name = lit[1];
                if (lit[0] == "Texture")
                    format->TextureId = std::stoi(lit[1]);
                if (lit[0] == "CenterPoint")
                    format->Position = glm::vec2(std::stof(lit[1]), std::stof(lit[2]));
                if (lit[0] == "Scale")
                    format->Scale = glm::vec2(std::stof(lit[1]), std::stof(lit[2]));
                if (lit[0] == "Color")
                {
                    format->Color = glm::vec4(std::stof(lit[1]), std::stof(lit[2]), std::stof(lit[3]), std::stof(lit[4]));
                    format->baseColor = format->Color;
                }
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
                    auto p8 = lit[++index];
                    Str str;
                    str.Text = result_text;
                    str.Position = glm::vec2(std::stof(p1), std::stof(p2));
                    str.Color = glm::vec4(std::stof(p3), std::stof(p4), std::stof(p5), std::stof(p6));
                    str.Scale = std::stof(p8);
                    format->Text.emplace(
                        p7,
                        str
                    );
                }
                if (lit[0] == "Hover")
                    format->hoverColor = glm::vec4(std::stof(lit[1]), std::stof(lit[2]), std::stof(lit[3]), std::stof(lit[4]));
                if (lit[0] == "Visible")
                    format->Visible = std::stoi(lit[1]);
                if (lit[0] == "Type")
                    format->Type = lit[1];
                if (lit[0] == "Lobby")
                    format->LobbyIndex = std::stoi(lit[1]);
                if (lit[0] == "For")
                    format->For = lit[1];               
                if (lit[0] == "ShowOnClickEvent")
                {
                    lit.erase(lit.begin());
                    format->ShowToClick = lit;
                }
                if (lit[0] == "HideOnClickEvent")
                {
                    lit.erase(lit.begin());
                    format->HideToClick = lit;
                }
                if (lit[0] == "CommandOnClick")
                {
                    lit.erase(lit.begin());
                    std::string Command = lit[0];
                    if(lit.size() > 2)
                        lit.erase(lit.begin());
                    format->CommandOnClick = std::pair<std::string, std::vector<std::string>>(Command, lit);
                }
                if (lit[0] == "Key")
                    format->Key = std::make_pair<bool, SDL_Keycode>(true, (SDL_Keycode)lit[1][0]);
                if (lit[0] == "Highlight")
                    format->ActiveHighlight = std::stoi(lit[1]);
                if (lit[0] == "HighlightIntensity")
                    format->ActiveHighlightIntensity = std::stof(lit[1]);
                if (lit[0] == "Dynamic")
                    format->DynamicText = std::stoi(lit[1]);
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
