/*
  ==============================================================================

    GlobalHooksHooker.cpp
    Created: 11 Oct 2015 4:36:20pm
    Author:  Nimgoble

  ==============================================================================
*/

#include "GlobalHooksHooker.h"
juce::Array<GlobalHooksDispatchListener *, CriticalSection> GlobalHooksHooker::HooksListeners = juce::Array<GlobalHooksDispatchListener *, CriticalSection>();
CriticalSection GlobalHooksHooker::HookMutex;
bool GlobalHooksHooker::isHookInitialized = false;
bool GlobalHooksHooker::isHookRunning = false;
juce::ScopedPointer<GlobalHooksThread> GlobalHooksHooker::globalHooksThread = nullptr;