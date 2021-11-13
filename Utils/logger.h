#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>

constexpr auto concat = [](auto...args) -> std::string
{
	std::stringstream stream;
	((stream << args), ...);
	return std::move(stream.str());
};

class Logger
{
	std::wofstream logFile;
	bool mirrorToStdout{ true };
public:
	explicit Logger(std::filesystem::path file)
		: logFile{ std::filesystem::absolute(file.c_str()), std::ios_base::app }
	{}
	void log(const std::wstring& msg)
	{
		logFile << msg << std::endl;
		std::wcout << msg << std::endl;
	}
	template<typename...Args>
	void log(Args...args)
	{
		std::wstringstream stream;
		((stream << args), ...);
		logFile << stream.str() << std::endl;
		std::wcout << stream.str() << std::endl;
	}
};