#include "DebugEventListener.h"
#include <conversion.h>
#include <sstream>

struct ProcInfo
{
	const CREATE_PROCESS_DEBUG_INFO& processInfo;
	ProcInfo(const CREATE_PROCESS_DEBUG_INFO& proc)
		: processInfo{ proc }
	{}
	std::wstring imageName() const
	{
		if (processInfo.fUnicode)
		{
			return { static_cast<const wchar_t*>(processInfo.lpImageName) };
		}
		else
		{
			return { char_to_wchar(static_cast<const char*>(processInfo.lpImageName)) };
		}
	}

};

struct DllInfo
{
	const LOAD_DLL_DEBUG_INFO& dllInfo;
	DllInfo(const LOAD_DLL_DEBUG_INFO& dll)
		: dllInfo{ dll }
	{}
	std::wstring imageName() const
	{
		if (dllInfo.fUnicode)
		{
			return { static_cast<const wchar_t*>(dllInfo.lpImageName) };
		}
		else
		{
			return { char_to_wchar(static_cast<const char*>(dllInfo.lpImageName)) };
		}
	}
};

struct ThreadInfo
{
	const CREATE_THREAD_DEBUG_INFO& threadInfo;
	ThreadInfo(const CREATE_THREAD_DEBUG_INFO& thread)
		: threadInfo{ thread }
	{}
	size_t threadId() const
	{
		return static_cast<size_t>(GetThreadId(threadInfo.hThread));
	}
};

struct ExceptionInfo
{
	const EXCEPTION_DEBUG_INFO& exceptionInfo;
	const EXCEPTION_RECORD& exceptionRecord;
	ExceptionInfo(const EXCEPTION_DEBUG_INFO& exception)
		: exceptionInfo{ exception }
		, exceptionRecord{ exception.ExceptionRecord }
	{}
	bool firstChance() const
	{
		return exceptionInfo.dwFirstChance != 0;
	}
	DWORD exceptionCode() const
	{
		return exceptionRecord.ExceptionCode;
	}
	bool continuableException() const
	{
		return exceptionRecord.ExceptionFlags != EXCEPTION_NONCONTINUABLE;
	}
	void* exceptionAddress() const
	{
		return exceptionRecord.ExceptionAddress;
	}
	std::string toString() const
	{
		std::stringstream stream;
		stream << std::hex << exceptionCode();
		if (continuableException())
		{
			stream << " continuable";
		}
		else
		{
			stream << " non-continuable";
		}
		stream << " exception at 0x" << exceptionAddress();
	}
};

DebugEventListener::DebugEventListener(Logger& logger)
	: logger{ logger }
{}

DWORD DebugEventListener::onCreateProcess(const CREATE_PROCESS_DEBUG_INFO& processInfo)
{
	const ProcInfo info{ processInfo };
	std::wstringstream stream;
	stream << L"Started Process " << info.imageName();
	logger.log(stream.str());

	return DBG_EXCEPTION_NOT_HANDLED;
}
DWORD DebugEventListener::onCreateThread(const CREATE_THREAD_DEBUG_INFO& threadInfo)
{
	const ThreadInfo info{ threadInfo };
	std::wstringstream stream;
	stream << L"Started Thread " << info.threadId();
	logger.log(stream.str());

	return DBG_EXCEPTION_NOT_HANDLED;
}
DWORD DebugEventListener::onException(const EXCEPTION_DEBUG_INFO& exceptionInfo)
{
	ExceptionInfo info{ exceptionInfo };
	logger.log(info.toString());
	return DBG_EXCEPTION_NOT_HANDLED;
}
DWORD DebugEventListener::onExitProcess(const EXIT_PROCESS_DEBUG_INFO& processInfo)
{
	logger.log(L"Processes exited with ", processInfo.dwExitCode);
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventListener::onExitThread(const EXIT_THREAD_DEBUG_INFO& threadInfo)
{
	logger.log(L"Thread exited with ", threadInfo.dwExitCode);
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventListener::onLoadDll(const LOAD_DLL_DEBUG_INFO& dllInfo)
{
	DllInfo dll{ dllInfo };
	logger.log("Loaded ", dll.imageName());
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventListener::onOutputDebugString(const OUTPUT_DEBUG_STRING_INFO& stringInfo)
{
	if (stringInfo.fUnicode)
	{
		std::wstring_view msg(reinterpret_cast<const wchar_t*>(stringInfo.lpDebugStringData), stringInfo.nDebugStringLength);
		logger.log(msg);
	}
	else
	{
		std::string_view msg(reinterpret_cast<const char*>(stringInfo.lpDebugStringData), stringInfo.nDebugStringLength);
		logger.log(msg);
	}
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventListener::onRip(const RIP_INFO& ripInfo)
{
	logger.log("RIP exception ", ripInfo.dwError, " of type ", ripInfo.dwType);
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventListener::onUnloadDll(const UNLOAD_DLL_DEBUG_INFO& dllInfo)
{
	//TODO: store the baseptr from the load so the unload module name can be logged.
	return DBG_EXCEPTION_NOT_HANDLED;
};