#include "Json.h"

#include "EFile.h"
#include<rapidjson/istreamwrapper.h>
#include<iostream>

namespace Json
{
    bool Load(const std::string& filename, rapidjson::Document& document)
    {
        std::string buffer;
        if (!File::ReadFile(filename, buffer))
        {
            return false;
        }

        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);
        
        document.ParseStream(istream);
        if (!document.IsObject())
        {
            std::cerr << "Could Not Parse Json: " << filename << std::endl;
            return false;
        }

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, int& data)
    {
        //checks if the key is present in the file
        //then checks if the data type of the key matchees to the data type of the function (int)
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
        {
            std::cerr << "Could Not Read Json Value: " << name << std::endl;

            return false;
        }

        data = value[name.c_str()].GetInt();

        return true;
    }

    ///////////// bool
    bool Read(const rapidjson::Value& value, const std::string& name, bool& data)
    {
        
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
        {
            std::cerr << "Could Not Read Json Value: " << name << std::endl;

            return false;
        }

        data = value[name.c_str()].GetBool();

        return true;
    }

    ///////////// string
    bool Read(const rapidjson::Value& value, const std::string& name, std::string& data)
    {
        
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
        {
            std::cerr << "Could Not Read Json Value: " << name << std::endl;

            return false;
        }

        data = value[name.c_str()].GetString();

        return true;
    }


}
