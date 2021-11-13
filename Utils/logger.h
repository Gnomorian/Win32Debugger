#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>

auto concat = [](auto...args) -> std::string
{
	std::stringstream stream;
	((stream << args), ...);
	return std::move(stream.str());
};

class Logger
{
	std::ofstream logFile;
	bool mirrorToStdout{ true };
public:
	explicit Logger(std::filesystem::path file)
		: logFile{ std::filesystem::absolute(file.c_str()), std::ios_base::app }
	{}
	void log(const std::string& msg)
	{
		logFile << msg << std::endl;
		std::cout << msg << std::endl;
	}
	template<typename...Args>
	void log(Args...args)
	{
		std::stringstream stream;
		((stream << args), ...);
		logFile << stream.str() << std::endl;
		std::cout << stream.str() << std::endl;
	}
};