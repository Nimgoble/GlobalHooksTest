/*
  ==============================================================================

    GlobalHooksThread.cpp
    Created: 11 Oct 2015 3:35:05pm
    Author:  Nimgoble

  ==============================================================================
*/

#include "GlobalHooksThread.h"

GlobalHooksThread::GlobalHooksThread(GlobalHooksResultsCallback _threadListener) :
	Thread("Global Hooks Thread")
{	
	threadListener = _threadListener;
	startThread(10);
}

GlobalHooksThread::~GlobalHooksThread()
{
	threadListener = nullptr;
	signalThreadShouldExit();
	stopThread(2000);
}

void GlobalHooksThread::run()
{
	int result = hook_run();
	threadListener(result);
	if (result != UIOHOOK_SUCCESS)
		return;

	while (!threadShouldExit())
	{

	}

	hook_stop();
}

int GlobalHooksThread::StopHook()
{
	return hook_stop();
}

