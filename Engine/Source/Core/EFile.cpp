#include "EFile.h"

//using namespace std::filesystem would make some of the code lines shorter, but it's not required and in some cases is bad ettiquet

std::string File::GetFilePath()
{
    return std::filesystem::current_path().string();
}

bool File::SetFilePath(const std::string filepath)
{
    std::error_code ec;
    std::filesystem::current_path(filepath, ec);
    //ec passed in and will be set to errorcode (0 means was successful)

    return !ec; //returns if it was successful or not
}
