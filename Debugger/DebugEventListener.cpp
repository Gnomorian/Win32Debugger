#include "DebugEventListener.h"

DebugEventListener::DebugEventListener(Logger& logger)
	: logger{ logger }
{}

DWORD DebugEventListener::onCreateProcess(const CREATE_PROCESS_DEBUG_INFO& processInfo)
{
	std::stringstream stream;
	return DBG_EXCEPTION_NOT_HANDLED;
}
DWORD DebugEventListener::onCreateThread(const CREATE_THREAD_DEBUG_INFO& threadInfo)
{
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