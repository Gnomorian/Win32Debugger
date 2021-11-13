#pragma once
#include <Windows.h>
#include <logger.h>
#include "DebugEventHandler.h"

class Debugger
{
	DebugEventHandler handler;
public:
	using Attached = bool;
	using PID = DWORD;
	using Milliseconds = DWORD;

	Debugger(Logger& logger, PID process);
	virtual void attach();
	virtual void setEventHandler(const DebugEventHandler& newhandler);
	virtual Attached processEvents(Milliseconds timeout = INFINITE);
private:
	PID _debugee;
	Logger& logger;
};