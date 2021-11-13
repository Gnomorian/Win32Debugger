#include "DebugEventListener.h"
#include <conversion.h>

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
	return DBG_EXCEPTION_NOT_HANDLED;
}
DWORD DebugEventListener::onExitProcess(const EXIT_PROCESS_DEBUG_INFO& processInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventListener::onExitThread(const EXIT_THREAD_DEBUG_INFO& threadInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventListener::onLoadDll(const LOAD_DLL_DEBUG_INFO& dllInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventListener::onOutputDebugString(const OUTPUT_DEBUG_STRING_INFO& stringInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventListener::onRip(const RIP_INFO& ripInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventListener::onUnloadDll(const UNLOAD_DLL_DEBUG_INFO& dllInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};