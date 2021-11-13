#pragma once
#include <Windows.h>

class DebugEventHandler
{
public:
	virtual DWORD onCreateProcess(const CREATE_PROCESS_DEBUG_INFO& processInfo);
	virtual DWORD onCreateThread(const CREATE_THREAD_DEBUG_INFO& threadInfo);
	virtual DWORD onException(const EXCEPTION_DEBUG_INFO& exceptionInfo);
	virtual DWORD onExitProcess(const EXIT_PROCESS_DEBUG_INFO& processInfo);
	virtual DWORD onExitThread(const EXIT_THREAD_DEBUG_INFO& threadInfo);
	virtual DWORD onLoadDll(const LOAD_DLL_DEBUG_INFO& dllInfo);
	virtual DWORD onOutputDebugString(const OUTPUT_DEBUG_STRING_INFO& stringInfo);
	virtual DWORD onRip(const RIP_INFO& ripInfo);
	virtual DWORD onUnloadDll(const UNLOAD_DLL_DEBUG_INFO& dllInfo);
};