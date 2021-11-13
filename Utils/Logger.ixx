export module Logger;

#pragma message("Warning 5050 is disabled to hide a Microsoft CRT bug, remember to remove these pragmas when they fix it.")
#pragma warning(suppress:5050) // suppress debug crt bug. https://developercommunity.visualstudio.com/t/warning-c5050-when-using-stl-modules-and-one-of-md/873364
export import std.core;
#pragma warning(suppress:5050) // suppress debug crt bug. https://developercommunity.visualstudio.com/t/warning-c5050-when-using-stl-modules-and-one-of-md/873364
export import std.filesystem;

namespace Utils
{
	export auto concat = [](auto...args) -> std::string
	{
		std::stringstream stream;
		((stream << args), ...);
		return std::move(stream.str());
	};

	export class Logger
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
}