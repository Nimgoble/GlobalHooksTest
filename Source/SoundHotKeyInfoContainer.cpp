/*
  ==============================================================================

    SoundHotKeyInfoContainer.cpp
    Created: 19 Oct 2015 10:56:21am
    Author:  johnathan

  ==============================================================================
*/

#include "SoundHotKeyInfoContainer.h"

SoundHotKeyInfoContainer::SoundHotKeyInfoContainer(ApplicationCommandManager& _commandManager, AudioDeviceManager &_audioDeviceManager, SoundHotKeyInfo _info) :
	commandManager(_commandManager),
	audioDeviceManager(_audioDeviceManager),
	info(_info),
	thread("audio file preview")
{
	File audioFile = File(_info.SourceFile);
	sourceFileExists = audioFile.exists();
	thread.startThread(3);
	if (sourceFileExists)
	{
		formatManager.registerBasicFormats();
		audioDeviceManager.addAudioCallback(&audioSourcePlayer);
		audioSourcePlayer.setSource(&transportSource);
		LoadTransportSource(audioFile);
	}
}
SoundHotKeyInfoContainer::~SoundHotKeyInfoContainer()
{
	UnloadTransportSource();
	transportSource.setSource(nullptr);
	audioSourcePlayer.setSource(nullptr);
	audioDeviceManager.removeAudioCallback(&audioSourcePlayer);
	masterReference.clear();
}

void SoundHotKeyInfoContainer::PlayOrStop()
{
	if (!sourceFileExists)
		return;

	if (transportSource.isPlaying())
		transportSource.stop();
	/*else
	{
		
	}*/

	transportSource.setPosition(0);
	transportSource.start();
}

void SoundHotKeyInfoContainer::AddKeyPress(const KeyPress &newKeyPress)
{
	commandManager.getKeyMappings()->addKeyPress(info.CommandID, newKeyPress);
	info.KeyPresses.add(newKeyPress);
}
void SoundHotKeyInfoContainer::RemoveKeyPress(const KeyPress &keyPress)
{
	int keyIndex = commandManager.getKeyMappings()->getKeyPressesAssignedToCommand(info.CommandID).indexOf(keyPress);
	commandManager.getKeyMappings()->removeKeyPress(info.CommandID, keyIndex);
	info.KeyPresses.removeFirstMatchingValue(keyPress);
}

double SoundHotKeyInfoContainer::getPercentageDone()
{
	double rtn = 0.0f;
	if (transportSource.isPlaying())
	{
		double currentPosition = transportSource.getCurrentPosition();
		double totalLength = transportSource.getLengthInSeconds();
		rtn = currentPosition / totalLength;
	}
	return rtn;
}

void SoundHotKeyInfoContainer::LoadTransportSource(const File& audioFile)
{
	AudioFormatReader* reader = formatManager.createReaderFor(audioFile);

	if (reader != nullptr)
	{
		currentAudioFileSource = new AudioFormatReaderSource(reader, true);

		// ..and plug it into our transport source
		transportSource.setSource(currentAudioFileSource,
			32768,                   // tells it to buffer this many samples ahead
			&thread,                 // this is the background thread to use for reading-ahead
			reader->sampleRate);     // allows for sample rate correction
	}
}

void SoundHotKeyInfoContainer::UnloadTransportSource()
{
	if (!sourceFileExists)
		return;

	transportSource.stop();
	transportSource.setSource(nullptr);
	currentAudioFileSource = nullptr;
}
