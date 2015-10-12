/*
  ==============================================================================

    GlobalHooksThread.h
    Created: 11 Oct 2015 3:34:51pm
    Author:  Nimgoble

  ==============================================================================
*/

#ifndef GLOBALHOOKSTHREAD_H_INCLUDED
#define GLOBALHOOKSTHREAD_H_INCLUDED

#include "..\JuceLibraryCode\JuceHeader.h"
#include "..\libuiohook\uiohook.h"
#include "GlobalHooksListener.h"

class GlobalHooksThread : public Thread
{
public:
	GlobalHooksThread(GlobalHooksResultsCallback _threadListener);
	~GlobalHooksThread();

	void run() override;

	int StopHook();

private:
	GlobalHooksResultsCallback threadListener;
};



#endif  // GLOBALHOOKSTHREAD_H_INCLUDED
