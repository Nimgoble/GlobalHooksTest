/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_2D44EA27B4F31DEA__
#define __JUCE_HEADER_2D44EA27B4F31DEA__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "SoundHotKeyInfo.h"
#include "SoundFileDragAndDropTarget.h"
#include "SoundInfoOperationsListener.h"
#include "SoundHotKeyConfigFile.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SongsTabComponent  : public Component,
                           public ListBoxModel,
                           public ChangeBroadcaster,
                           public MenuBarModel,
                           public SoundInfoOperationsListener
{
public:
    //==============================================================================
    SongsTabComponent (AudioDeviceManager &_audioDeviceManager);
    ~SongsTabComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	int getNumRows() override;
	void paintListBoxItem(int rowNumber,
		Graphics& g,
		int width, int height,
		bool rowIsSelected) override;

	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component*) override;

	StringArray getMenuBarNames() override;
	PopupMenu getMenuForIndex(int menuIndex, const String& /*menuName*/) override;
	void menuItemSelected(int menuItemID, int /*topLevelMenuIndex*/) override;


	void CreateInfoFromFile(const String &file) override;
	void RemoveInfo(CommandID id) override;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	AudioDeviceManager &audioDeviceManager;
	ScopedPointer<MenuBarComponent> menuBar;
	ScopedPointer<SoundHotKeyConfigFile> currentConfigFile;

	enum CommandIDs
	{
		cLoadSoundHotKeyFile = 0x2100,
		cSaveSoundHotkeyFile = 0x2101
	};

	void Command_LoadSoundHotKeyFile();
	void LoadSoundHotKeyFile(File &file);
	void Command_SaveSoundHotKeyFile();
	void SaveSoundHotKeyFile(File &file);
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ListBox> SoundHotKeyListBox;
    ScopedPointer<SoundFileDragAndDropTarget> soundFileDragAndDropTarget;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SongsTabComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_2D44EA27B4F31DEA__
