#pragma once

#include <string>
#include <filesystem>	

namespace File
{
	std::string GetFilePath();
	bool SetFilePath(const std::string& filepath);

	bool FileExists(const std::string& filepath);
	bool GetFileSize(const std::string& filepath, int& size); //bool returns if it exists, and the size you pass in will be assigned the size

	bool ReadFile(const std::string& filepath, std::string& buffer);
}