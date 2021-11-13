#include "Debugger.h"

Debugger::Debugger(Logger& logger, PID process)
	: _debugee{process}
	, logger{logger}
{
}

void Debugger::attach()
{
	const auto debugging{ static_cast<bool>(DebugActiveProcess(_debugee)) };
	if (!debugging)
	{
		const auto error{ GetLastError() };
		const auto msg{ concat("could not attach to process ", _debugee, ", error=", error) };
		throw std::runtime_error{ msg };
	}
}

void Debugger::setEventHandler(const DebugEventHandler& newhandler)
{
	handler = newhandler;
}

Debugger::Attached Debugger::processEvents(Milliseconds timeout)
{
	DEBUG_EVENT event{};
	const auto result{ static_cast<bool>(WaitForDebugEvent(&event, timeout)) };
	if (!result)
	{
		const auto error{ GetLastError() };
		const auto msg{ concat("WaitForDebugEvent failed with ", error) };
		throw std::runtime_error{ msg };
	}

	DWORD continueStatus{ DBG_EXCEPTION_NOT_HANDLED };

	switch (event.dwDebugEventCode)
	{
	case CREATE_PROCESS_DEBUG_EVENT:
		continueStatus = handler.onCreateProcess(event.u.CreateProcessInfo);
		break;
	case CREATE_THREAD_DEBUG_EVENT:
		continueStatus = handler.onCreateThread(event.u.CreateThread);
		break;
	case EXCEPTION_DEBUG_EVENT:
		continueStatus = handler.onException(event.u.Exception);
		break;
	case EXIT_PROCESS_DEBUG_EVENT:
		continueStatus = handler.onExitProcess(event.u.ExitProcess);
		break;
	case EXIT_THREAD_DEBUG_EVENT:
		continueStatus = handler.onExitThread(event.u.ExitThread);
		break;
	case LOAD_DLL_DEBUG_EVENT:
		continueStatus = handler.onLoadDll(event.u.LoadDll);
		break;
	case OUTPUT_DEBUG_STRING_EVENT:
		continueStatus = handler.onOutputDebugString(event.u.DebugString);
		break;
	case RIP_EVENT:
		continueStatus = handler.onRip(event.u.RipInfo);
		break;
	case UNLOAD_DLL_DEBUG_EVENT:
		continueStatus = handler.onUnloadDll(event.u.UnloadDll);
		break;
	default:
		continueStatus = DBG_EXCEPTION_NOT_HANDLED;
		logger.log("Unknown debug event ", event.dwDebugEventCode);
	}
	logger.log("Had a ", event.dwDebugEventCode, " event.");
	return ContinueDebugEvent(event.dwProcessId, event.dwThreadId, continueStatus);
}
