/*
  ==============================================================================

    SoundHotKeyInfoContainer.h
    Created: 19 Oct 2015 10:56:21am
    Author:  johnathan

	What this class does:
	-Takes the SoundHotKeyInfo
	-Verifies that the SoundSource exists.
	-Loads the sound file and plays/stops it.

  ==============================================================================
*/

#ifndef SOUNDHOTKEYINFOCONTAINER_H_INCLUDED
#define SOUNDHOTKEYINFOCONTAINER_H_INCLUDED

#include "JuceHeader.h"
#include "SoundHotKeyInfo.h"

class SoundHotKeyInfoContainer
{
public:
	SoundHotKeyInfoContainer(ApplicationCommandManager& _commandManager, AudioDeviceManager &_audioDeviceManager, SoundHotKeyInfo _info);
	~SoundHotKeyInfoContainer();

	SoundHotKeyInfo &GetSoundHotKeyInfo() { return info; }

	void PlayOrStop();

	bool DoesSourceFileExist() { return sourceFileExists; }

	CommandID getCommandID(){ return info.CommandID; }

	void AddKeyPress(const KeyPress &newKeyPress);
	void RemoveKeyPress(const KeyPress &keyPress);

	double getPercentageDone();
	bool isPlaying(){ return transportSource.isPlaying(); }

private:
	ApplicationCommandManager& commandManager;
	AudioDeviceManager &audioDeviceManager;
	AudioFormatManager formatManager;
	AudioSourcePlayer audioSourcePlayer;
	AudioTransportSource transportSource;
	ScopedPointer<AudioFormatReaderSource> currentAudioFileSource;
	TimeSliceThread thread; //Background thread used for reading ahead.

	SoundHotKeyInfo info;

	bool sourceFileExists;

	WeakReference<SoundHotKeyInfoContainer>::Master masterReference;
	friend class WeakReference<SoundHotKeyInfoContainer>;

	void LoadTransportSource(const File& audioFile);
	void UnloadTransportSource();
};



#endif  // SOUNDHOTKEYINFOCONTAINER_H_INCLUDED
