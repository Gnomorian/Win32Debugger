#include "DebugEventHandler.h"

DWORD DebugEventHandler::onCreateProcess(const CREATE_PROCESS_DEBUG_INFO& processInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
}
DWORD DebugEventHandler::onCreateThread(const CREATE_THREAD_DEBUG_INFO& threadInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
}
DWORD DebugEventHandler::onException(const EXCEPTION_DEBUG_INFO& exceptionInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
}
DWORD DebugEventHandler::onExitProcess(const EXIT_PROCESS_DEBUG_INFO& processInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventHandler::onExitThread(const EXIT_THREAD_DEBUG_INFO& threadInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventHandler::onLoadDll(const LOAD_DLL_DEBUG_INFO& dllInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventHandler::onOutputDebugString(const OUTPUT_DEBUG_STRING_INFO& stringInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventHandler::onRip(const RIP_INFO& ripInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};
DWORD DebugEventHandler::onUnloadDll(const UNLOAD_DLL_DEBUG_INFO& dllInfo)
{
	return DBG_EXCEPTION_NOT_HANDLED;
};