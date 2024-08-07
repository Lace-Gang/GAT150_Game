#include "EFile.h"

#include<iostream>
#include<fstream>

//using namespace std::filesystem would make some of the code lines shorter, but it's not required and in some cases is bad ettiquet

std::string File::GetFilePath()
{
    return std::filesystem::current_path().string();

}

bool File::SetFilePath(const std::string& filepath)
{
    std::error_code ec;
    std::filesystem::current_path(filepath, ec);
    //ec passed in and will be set to errorcode (0 means was successful)

    return !ec; //returns if it was successful or not
}

bool File::FileExists(const std::string& filepath)
{
    return std::filesystem::exists(filepath);
}

bool File::GetFileSize(const std::string& filepath, int& size)
{
    //std::filesystem::path path(filepath); //path is what you are actually passing into when you pass in filepath to file_size
    std::error_code ec;
    size = (int)std::filesystem::file_size(filepath, ec);
    return !ec;
}

bool File::ReadFile(const std::string& filepath, std::string& buffer)
{
    if (!FileExists(filepath))
    {
        std::cerr << "File Does Not Exist: " << filepath << std::endl;
        return false;
    }
    
    //opening the text file so that it will be readable
    std::ifstream stream(filepath, std::ios::in); //ifstream is in, ofstream is out (ios means input-output stream) (the second perameter, *may* be optional)
    if (!stream.is_open())
    {
        std::cerr << "Could Not Open File: " << filepath << std::endl;
        return false;
    }

    //turning it into an ostring
    std::ostringstream ostream;
    ostream << stream.rdbuf(); //rdbuff I think means readbuffer?

    buffer = ostream.str();

    return true;
}
