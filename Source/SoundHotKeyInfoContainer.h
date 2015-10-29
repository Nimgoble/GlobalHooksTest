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
#include "IKeyPressCollectionContainer.h"

class SoundHotKeyInfoContainer : public IKeyPressCollectionContainer
{
public:
	SoundHotKeyInfoContainer(ApplicationCommandManager& _commandManager, AudioDeviceManager &_audioDeviceManager, SoundHotKeyInfo _info);
	~SoundHotKeyInfoContainer();

	SoundHotKeyInfo &GetSoundHotKeyInfo() { return info; }

	void PlayOrStop();

	bool DoesSourceFileExist() { return sourceFileExists; }

	CommandID getCommandID(){ return info.CommandID; }

	double getPercentageDone();
	bool isPlaying(){ return transportSource.isPlaying(); }

	virtual int OnKeyAdded(const KeyPress &newKeyPress);
	virtual void OnKeyRemoved(const KeyPress &keyPress);
	virtual void OnKeyChanged(const KeyPress &oldKeyPress, const KeyPress &newKeyPress);
	virtual int NumberOfKeyPresses();
	virtual const KeyPress &GetKeyPressByIndex(int index);

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
