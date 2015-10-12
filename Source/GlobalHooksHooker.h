/*
  ==============================================================================

    GlobalHooksHooker.h
    Created: 11 Oct 2015 4:36:10pm
    Author:  Nimgoble

  ==============================================================================
*/

#ifndef GLOBALHOOKSHOOKER_H_INCLUDED
#define GLOBALHOOKSHOOKER_H_INCLUDED

#include "..\JuceLibraryCode\JuceHeader.h"
#include "GlobalHooksListener.h"
#include "GlobalHooksThread.h"

typedef GenericScopedLock<CriticalSection> GlobalHooksLock;
class GlobalHooksHooker
{
public:

	static void Init()
	{
		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);
			if (!isHookInitialized)
			{
				hook_set_dispatch_proc(&GlobalHooksHooker::StaticDispatchProcedure);
				isHookInitialized = true;
			}
		}
	}

	static void Run()
	{
		if (IsHookRunning())
			return;

		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);
			isHookRunning = true;
			globalHooksThread = new GlobalHooksThread(&GlobalHooksHooker::GlobalHooksRunResult);
		}
	}

	static void Shutdown()
	{
		if (!IsHookRunning())
			return;

		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);
			if (globalHooksThread != nullptr)
			{
				int result = globalHooksThread->StopHook();
				bool threadResult = globalHooksThread->waitForThreadToExit(2000);
				globalHooksThread = nullptr;
			}
			HooksListeners.clear();
		}
	}

	static void AddListener(GlobalHooksDispatchListener *listener)
	{
		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);
			HooksListeners.addIfNotAlreadyThere(listener);
		}
	}

	static void RemoveListener(GlobalHooksDispatchListener *listener)
	{
		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);
			HooksListeners.removeFirstMatchingValue(listener);
		}
	}

	static void StaticDispatchProcedure(uiohook_event * const event)
	{
		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);

			const juce_wchar textCharacter = event->data.keyboard.keychar;
			const juce::KeyPress keyInfo
			(
				event->data.keyboard.rawcode,
				juce::ModifierKeys::getCurrentModifiers().withoutMouseButtons(),
				textCharacter
			);

			for (int i = HooksListeners.size(); --i >= 0;)
			{
				GlobalHooksDispatchListener *listener = HooksListeners.getUnchecked(i);
				if (listener->WantsMessage(event))
					listener->OnMessageReceived(event);
			}
				
		}
	}

	static void GlobalHooksRunResult(int result)
	{
		SetHookRunning((result == UIOHOOK_SUCCESS));
	}

	static bool IsHookInitialized()
	{
		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);
			return isHookInitialized;
		}
	}

	static void SetHookInitialized(bool initialized)
	{
		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);
			isHookInitialized = initialized;
		}
	}

	static bool IsHookRunning()
	{
		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);
			return isHookRunning;
		}
	}

	static void SetHookRunning(bool running)
	{
		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);
			isHookRunning = running;
		}
	}
private:
	static juce::Array<GlobalHooksDispatchListener *, CriticalSection> HooksListeners;
	static CriticalSection HookMutex;
	static bool isHookInitialized;
	static bool isHookRunning;

	static juce::ScopedPointer<GlobalHooksThread> globalHooksThread;
};

#endif  // GLOBALHOOKSHOOKER_H_INCLUDED
