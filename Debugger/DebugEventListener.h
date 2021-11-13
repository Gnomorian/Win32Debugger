#pragma once
#include "DebugEventHandler.h"
#include <logger.h>

/// <summary>
/// a DebugEventHandler that just logs to file events that occour and their parameters.
/// fatal exceptions are logged but ignored.
/// </summary>
class DebugEventListener : public DebugEventHandler
{
	Logger& logger;
public:
	DebugEventListener(Logger& logger);
	virtual DWORD onCreateProcess(const CREATE_PROCESS_DEBUG_INFO& processInfo) override;
	virtual DWORD onCreateThread(const CREATE_THREAD_DEBUG_INFO& threadInfo) override;
	virtual DWORD onException(const EXCEPTION_DEBUG_INFO& exceptionInfo) override;
	virtual DWORD onExitProcess(const EXIT_PROCESS_DEBUG_INFO& processInfo) override;
	virtual DWORD onExitThread(const EXIT_THREAD_DEBUG_INFO& threadInfo) override;
	virtual DWORD onLoadDll(const LOAD_DLL_DEBUG_INFO& dllInfo) override;
	virtual DWORD onOutputDebugString(const OUTPUT_DEBUG_STRING_INFO& stringInfo) override;
	virtual DWORD onRip(const RIP_INFO& ripInfo) override;
	virtual DWORD onUnloadDll(const UNLOAD_DLL_DEBUG_INFO& dllInfo) override;
};