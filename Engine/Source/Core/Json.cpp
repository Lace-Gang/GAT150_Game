#include "Json.h"

#include "EFile.h"
#include "./Math/Vector2.h"
#include "Math/Rect.h"

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

    bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool isRequired)
    {
        //checks if the key is present in the file
        //then checks if the data type of the key matchees to the data type of the function (int)
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
        {
            if(isRequired) std::cerr << "Could Not Read Json Value: " << name << std::endl;

            return false;
        }

        data = value[name.c_str()].GetInt();

        return true;
    }

    ///////////// bool
    bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool isRequired)
    {
        
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
        {
            if (isRequired) std::cerr << "Could Not Read Json Value: " << name << std::endl;

            return false;
        }

        data = value[name.c_str()].GetBool();

        return true;
    }

    ///////////// string
    bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool isRequired)
    {
        
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
        {
            if (isRequired) std::cerr << "Could Not Read Json Value: " << name << std::endl;

            return false;
        }

        data = value[name.c_str()].GetString();

        return true;
    }

    bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool isRequired)
    {

        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
        {
            if (isRequired) std::cerr << "Could Not Read Json Value: " << name << std::endl;

            return false;
        }

        data = value[name.c_str()].GetFloat();

        return true;
    }

    //bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data)
    //{

      //  if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
      //  {
      //      std::cerr << "Could Not Read Json Value: " << name << std::endl;
      //
      //      return false;
      //  }
      //
      //  if (value[name.c_str()][0].IsFloat())
      //  {
      //      data.x = value[name.c_str()][0].GetFloat();
      //  }
      //  else
      //  {
      //      data.y = value[name.c_str()][0].GetInt();
      //  }
      //
      //  if (value[name.c_str()][1].IsFloat())
      //  {
      //      data.x = value[name.c_str()][1].GetFloat();
      //  }
      //  else
      //  {
      //      data.y = value[name.c_str()][1].GetInt();
      //  }
        

        //return true;
    //}


    bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data, bool isRequired)
    {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }
    
        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }
    
            // get the data
            data[i] = array[i].GetFloat();
        }
    
        return true;
    }



    bool Read(const rapidjson::Value& value, const std::string& name, Color& data, bool isRequired)
    {
        // check if the value has the "<name>" and is an array with 2 elements
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            // get the data
            data[i] = array[i].GetFloat();
        }

        return true;
    }
    bool Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool isRequired)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
        {
            if (isRequired) std::cerr << "Could not read Json value: " << name << std::endl;
            return false;
        }

        // get json array object
        auto& array = value[name.c_str()];
        // get array values
        for (rapidjson::SizeType i = 0; i < array.Size(); i++)
        {
            if (!array[i].IsNumber())
            {
                std::cerr << "Could not read Json value: " << name << std::endl;
                return false;
            }

            data.x = array[0].GetInt();
            data.y = array[1].GetInt();
            data.w = array[2].GetInt();
            data.h = array[3].GetInt();

        }
        
        return true;

    }
}
