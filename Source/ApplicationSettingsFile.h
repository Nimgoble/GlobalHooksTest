/*
  ==============================================================================

    ApplicationSettingsFile.h
    Created: 29 Oct 2015 2:32:14pm
    Author:  johnathan

  ==============================================================================
*/

#ifndef APPLICATIONSETTINGSFILE_H_INCLUDED
#define APPLICATIONSETTINGSFILE_H_INCLUDED

#include "..\JuceLibraryCode\JuceHeader.h"

enum SoundPlayType
{
	StopAndPlay = 0,
	Restart
};

class ApplicationSettingsFile
{

private:
	bool useGlobalHooks;
	Array<KeyPress> stopAllSoundsKeys;
	SoundPlayType playType;
};

#endif  // APPLICATIONSETTINGSFILE_H_INCLUDED
