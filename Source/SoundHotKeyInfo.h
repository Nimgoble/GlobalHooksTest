/*
  ==============================================================================

    SoundHotKeyInfo.h
    Created: 15 Oct 2015 11:25:09am
    Author:  Nimgoble

  ==============================================================================
*/

#ifndef SOUNDHOTKEYINFO_H_INCLUDED
#define SOUNDHOTKEYINFO_H_INCLUDED

#include "JuceHeader.h"

class SoundHotKeyInfo
{
    //What do we need?  We need...    
public:
	SoundHotKeyInfo()
	{
		Name = "";
		SourceFile = "";
	}

	~SoundHotKeyInfo()
	{
		masterReference.clear();
	}

	SoundHotKeyInfo(var json)
	{
		DynamicObject* obj = json.getDynamicObject();
		if (obj == nullptr)
			return;

		Name = obj->getProperty("Name").toString();
		SourceFile = obj->getProperty("SourceFile").toString();
		var keyPresses = obj->getProperty("KeyPresses");
		if (keyPresses.isArray())
		{
			for (int i = 0; i < keyPresses.size(); ++i)
			{
				var jsonKeyPress(keyPresses[i]);
				if (jsonKeyPress.isVoid())
					continue;

				DynamicObject* jsonKeyPressObj = jsonKeyPress.getDynamicObject();
				if (jsonKeyPressObj == nullptr)
					continue;

				int keyCode = (int)jsonKeyPressObj->getProperty("KeyCode");
				int modifierFlags = (int)jsonKeyPressObj->getProperty("ModifierFlags");
				juce::juce_wchar textCharacter = (juce_wchar)((int)jsonKeyPressObj->getProperty("TextCharacter"));
				ModifierKeys modifierKeys;
				modifierKeys = modifierKeys.withFlags(modifierFlags);
				KeyPress keyPress(keyCode, modifierKeys, textCharacter);
				KeyPresses.add(keyPress);
			}
		}
	}

	var toJSON()
	{
		DynamicObject *root = new DynamicObject();
		root->setProperty("Name", Name);
		root->setProperty("SourceFile", SourceFile);

		Array<var> keyPressObjects;
		for (int i = 0; i < KeyPresses.size(); ++i)
		{
			const KeyPress &keyPress = KeyPresses.getUnchecked(i);
			DynamicObject *keyPressObject = new DynamicObject();
			keyPressObject->setProperty("KeyCode", keyPress.getKeyCode());
			keyPressObject->setProperty("ModifierFlags", keyPress.getModifiers().getRawFlags());
			keyPressObject->setProperty("TextCharacter", (int)keyPress.getTextCharacter());
			keyPressObjects.add(var(keyPressObject));
		}

		root->setProperty("KeyPresses", keyPressObjects);

		return var(root);
	}

	ApplicationCommandInfo getApplicationCommandInfo()
	{
		ApplicationCommandInfo commandInfo(CommandID);
		commandInfo.setInfo(Name, juce::String::empty, juce::String::empty, 0);
		if (KeyPresses.size() > 0)
		{
			const KeyPress &defaultKeyPress = KeyPresses.getUnchecked(0);
			commandInfo.addDefaultKeypress(defaultKeyPress.getKeyCode(), defaultKeyPress.getModifiers());
		}

		return commandInfo;
	}

	juce::CommandID CommandID;
    //A name for this particular file/keypress set
    juce::String Name;
    //The location of the sound file to play
    juce::String SourceFile;
    //Hotkey mappings
    Array<KeyPress> KeyPresses;

private:
	WeakReference<SoundHotKeyInfo>::Master masterReference;
	friend class WeakReference<SoundHotKeyInfo>;

	JUCE_LEAK_DETECTOR(SoundHotKeyInfo)
};

#endif  // SOUNDHOTKEYINFO_H_INCLUDED
