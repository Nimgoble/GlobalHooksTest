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

#ifndef LOWORD
#define LOWORD(l)           ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#endif

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
			globalHooksThread = new GlobalHooksThread(&GlobalHooksHooker::GlobalHooksRunResult, eventTypeToHook);
		}
	}

	static void Shutdown()
	{
		if (!IsHookRunning())
			return;

		int result = 0;
		bool threadResult = false;
		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);
			if (globalHooksThread != nullptr)
			{
				result = globalHooksThread->StopHook();
				threadResult = globalHooksThread->waitForThreadToExit(10000);
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
		//Do this outside of the lock, since the hook's cleanup depends on it.
		if (event->type != eventTypeToHook)
			return;

		{
			GlobalHooksLock lock(GlobalHooksHooker::HookMutex);	

			const juce_wchar textCharacter = event->data.keyboard.keychar;

			int key = event->data.keyboard.keychar;
			int virtualScanCode = event->data.keyboard.keycode;

			if (key >= '0' && key <= '9')
			{
				switch (virtualScanCode)  // check for a numeric keypad scan-code
				{
				case 0x52:
				case 0x4f:
				case 0x50:
				case 0x51:
				case 0x4b:
				case 0x4c:
				case 0x4d:
				case 0x47:
				case 0x48:
				case 0x49:
					key = (key - '0') + KeyPress::numberPad0;
					break;
				default:
					break;
				}
			}

			const juce::KeyPress keyInfo
			(
				key,
				GetJUCEModifierKeysFromEvent(event),
				textCharacter
			);

			for (int i = HooksListeners.size(); --i >= 0;)
			{
				GlobalHooksDispatchListener *listener = HooksListeners.getUnchecked(i);
				if (listener->WantsMessage(event))
					listener->KeyPressed(keyInfo);
			}
				
		}
	}

	static juce::ModifierKeys GetJUCEModifierKeysFromEvent(uiohook_event * const event)
	{
		int flags = 0;
		juce::ModifierKeys keys;
		if ((event->mask & MASK_SHIFT_L) || (event->mask & MASK_SHIFT_R))
			flags |= juce::ModifierKeys::shiftModifier;

		if
		(
			((event->mask & MASK_CTRL_L) || (event->mask & MASK_CTRL_R)) &&
			((event->mask & MASK_ALT_L) || (event->mask & MASK_ALT_R))
		)
			flags |= juce::ModifierKeys::ctrlAltCommandModifiers;
		else
		{
			if ((event->mask & MASK_CTRL_L) || (event->mask & MASK_CTRL_R))
				flags |= juce::ModifierKeys::ctrlModifier;
			if ((event->mask & MASK_ALT_L) || (event->mask & MASK_ALT_R))
				flags |= juce::ModifierKeys::altModifier;
		}

		return keys.withFlags(flags);
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

	static event_type GetEventTypeToHook(){ return eventTypeToHook; }
private:
	static juce::Array<GlobalHooksDispatchListener *, CriticalSection> HooksListeners;
	static CriticalSection HookMutex;
	static bool isHookInitialized;
	static bool isHookRunning;
	static event_type eventTypeToHook;

	static juce::ScopedPointer<GlobalHooksThread> globalHooksThread;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GlobalHooksHooker)
};

#endif  // GLOBALHOOKSHOOKER_H_INCLUDED
