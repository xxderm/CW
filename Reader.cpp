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
    if (update)
        guis->Clear();

    boost::property_tree::ptree pt;
    boost::property_tree::read_json(path.c_str(), pt);

    for (auto& gui_element : pt)
    {
        if (gui_element.first == "import")
        {
            this->getUI(guis, gui_element.second.get_value<std::string>(), false);
            continue;
        }
        GuiFormat* gui = new GuiFormat();
        gui->Name = gui_element.first;
        if (gui_element.second.count("Texture") > 0)
            gui->TextureId = gui_element.second.get<int>("Texture");
        gui->Position.x = gui_element.second
            .get_child("CenterPoint")
            .get<float>("x");
        gui->Position.y = gui_element.second
            .get_child("CenterPoint")
            .get<float>("y");
        gui->Scale.x = gui_element.second
            .get_child("Scale")
            .get<float>("x");
        gui->Scale.y = gui_element.second
            .get_child("Scale")
            .get<float>("y");
        gui->Color.r = gui_element.second
            .get_child("Color")
            .get<float>("r");
        gui->Color.g = gui_element.second
            .get_child("Color")
            .get<float>("g");
        gui->Color.b = gui_element.second
            .get_child("Color")
            .get<float>("b");
        gui->Color.a = gui_element.second
            .get_child("Color")
            .get<float>("a");
        gui->baseColor = gui->Color;
        if (gui_element.second.count("Text") > 0)
        {
            for (auto& element : gui_element.second.get_child("Text"))
            {
                Str String;
                String.Text = element.second.get<std::string>("String");
                String.Text = boost::locale::conv::from_utf(String.Text, "windows-1251");
                String.Position.x = element.second
                    .get_child("Location")
                    .get<float>("x");
                String.Position.y = element.second
                    .get_child("Location")
                    .get<float>("y");
                String.Color.r = element.second
                    .get_child("Color")
                    .get<float>("r");
                String.Color.g = element.second
                    .get_child("Color")
                    .get<float>("g");
                String.Color.b = element.second
                    .get_child("Color")
                    .get<float>("b");
                String.Color.a = element.second
                    .get_child("Color")
                    .get<float>("a");
                String.Scale = element.second.get<float>("Scale");
                String.BaseScale = String.Scale;
                gui->Text.emplace(element.second.get<std::string>("Name"), String);
            }
        }
        if (gui_element.second.count("Hover") > 0)
            gui->hoverColor = glm::vec4(
                gui_element.second
                .get_child("Hover")
                .get<float>("r"),
                gui_element.second
                .get_child("Hover")
                .get<float>("g"),
                gui_element.second
                .get_child("Hover")
                .get<float>("b"),
                gui_element.second
                .get_child("Hover")
                .get<float>("a")
            );
        if (gui_element.second.count("Visible") > 0) 
            gui->Visible = gui_element.second.get<bool>("Visible");
        if (gui_element.second.count("Type") > 0)
            gui->Type = gui_element.second.get<std::string>("Type");
        if (gui_element.second.count("Lobby") > 0)
            gui->LobbyIndex = gui_element.second.get<int>("Lobby");
        if (gui_element.second.count("Moveable") > 0)
            gui->Moveable = gui_element.second.get<bool>("Moveable");
        if (gui_element.second.count("For") > 0)
            gui->For = gui_element.second.get<std::string>("For");
        if (gui_element.second.count("ShowOnClickEvent") > 0)
            for (auto& i : gui_element.second.get_child("ShowOnClickEvent"))
                gui->ShowToClick.push_back(i.second.get_value<std::string>());
        if (gui_element.second.count("HideOnClickEvent") > 0)
            for (auto& i : gui_element.second.get_child("HideOnClickEvent"))
                gui->HideToClick.push_back(i.second.get_value<std::string>());
        if (gui_element.second.count("CommandOnClick") > 0)
            gui->CommandOnClick = 
                std::pair<std::string, std::vector<std::string>>
                 (gui_element.second.get<std::string>("CommandOnClick"), std::vector<std::string>());
        if (gui_element.second.count("Key") > 0)
            gui->Key = std::make_pair<bool, SDL_Keycode>(true, (SDL_Keycode)gui_element.second.get<char>("Key"));
        if (gui_element.second.count("Highlight") > 0)
            gui->ActiveHighlight = gui_element.second.get<bool>("Highlight");
        if (gui_element.second.count("HighlightIntensity") > 0)
            gui->ActiveHighlightIntensity = gui_element.second.get<float>("HighlightIntensity");
        if (gui_element.second.count("Dynamic") > 0)
            gui->DynamicText = gui_element.second.get<bool>("Dynamic");
        if (gui_element.second.count("StaticCountryTag") > 0)
            gui->SelectedCountryTag = gui_element.second.get<std::string>("StaticCountryTag");
        guis->Add(gui_element.first, gui);
    } 
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
