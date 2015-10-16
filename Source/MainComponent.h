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

#ifndef __JUCE_HEADER_9002020A4DD09B20__
#define __JUCE_HEADER_9002020A4DD09B20__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "SoundHotKeyInfo.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  : public Component,
                       public ApplicationCommandTarget,
                       public ListBoxModel,
                       public ChangeBroadcaster,
					   public MenuBarModel
{
public:
    //==============================================================================
    MainComponent ();
    ~MainComponent();

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

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	//juce::KeyMappingEditorComponent keyMappingEditor;
	ScopedPointer<MenuBarComponent> menuBar;

	juce::StringArray songs;

	enum CommandIDs
	{
		cLoadSoundHotKeyFile = 0x2100,
		cSaveSoundHotkeyFile = 0x2101
	};

	void Command_LoadSoundHotKeyFile();
	void LoadSoundHotKeyFile(File &file);
	void Command_SaveSoundHotKeyFile();
	void SaveSoundHotKeyFile(File &file);

	SoundHotKeyInfo *GetSoundHotKeyByCommandID(CommandID id);

	ApplicationCommandTarget* getNextCommandTarget() override;

	void getAllCommands(Array<CommandID>& commands) override;

	void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;

	bool perform(const InvocationInfo& info) override;

	juce::OwnedArray<SoundHotKeyInfo> soundHotKeys;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ListBox> SoundHotKeyListBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_9002020A4DD09B20__
