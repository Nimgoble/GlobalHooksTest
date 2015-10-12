/*
  ==============================================================================

    GlobalHooksThread.cpp
    Created: 11 Oct 2015 3:35:05pm
    Author:  Nimgoble

  ==============================================================================
*/

#include "GlobalHooksThread.h"

GlobalHooksThread::GlobalHooksThread(GlobalHooksResultsCallback _threadListener, event_type _eventTypeToHook) :
	Thread("Global Hooks Thread")
{	
	threadListener = _threadListener;
	eventTypeToHook = _eventTypeToHook;
	startThread(8);
}

GlobalHooksThread::~GlobalHooksThread()
{
	threadListener = nullptr;
	signalThreadShouldExit();
	stopThread(2000);
}

void GlobalHooksThread::run()
{
	int result = hook_run(eventTypeToHook);
	/*threadListener(result);
	if (result != UIOHOOK_SUCCESS)
		return;

	while (!threadShouldExit())
	{

	}

	hook_stop();*/
}

int GlobalHooksThread::StopHook()
{
	return hook_stop();
}

