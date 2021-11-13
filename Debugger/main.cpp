#include <string_view>
#include <vector>
#include <algorithm>
#include "Debugger.h"
#include "DebugEventListener.h"

std::vector<std::wstring_view> getArgs(int argc, wchar_t* argv[])
{
	auto generator = [&argv, i=0]() mutable -> std::wstring_view
	{
		return std::wstring_view{ argv[i++] };
	};
	std::vector<std::wstring_view> args{ static_cast<decltype(args)::size_type>(argc)};
	std::generate(args.begin(), args.end(), generator);
	return args;
}

auto attachSwitch(const auto& cmdline)
{
	return std::find(cmdline.cbegin(), cmdline.cend(), L"--attach");
}

auto startSwitch(const auto& cmdline)
{
	return std::find(cmdline.cbegin(), cmdline.cend(), L"--start");
}

auto attachPid(const auto& cmdline)
{
	auto itr{ attachSwitch(cmdline) };
	if (itr == cmdline.end())
		return static_cast<unsigned long>(-1);
	auto& str{ *(itr + 1) };
	wchar_t* end{ 0 };
	return std::wcstoul(str.data(), &end, 10);
}

int wmain(int argc, wchar_t* args[])
{
	const auto cmdline{ getArgs(argc, args) };
	auto pid{ attachPid(cmdline) };
	if (pid == -1)
		return -1;
	Logger logger{ "./Debug.log" };
	Debugger debugger{ logger, pid };
	debugger.setEventHandler(DebugEventListener{ logger });
	debugger.attach();
	debugger.processEvents();
}