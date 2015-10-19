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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
#include "MainWindow.h"
#include "SoundHotKeyView.h"
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	addAndMakeVisible(menuBar = new MenuBarComponent(this));
	audioDeviceManager = new AudioDeviceManager();
	audioDeviceManager->initialise(2, 2, 0, true, String::empty, 0);//TODO: device options.
	currentConfigFile = new SoundHotKeyConfigFile(*audioDeviceManager, MainWindow::getApplicationCommandManager());
    //[/Constructor_pre]

    addAndMakeVisible (SoundHotKeyListBox = new ListBox());
    SoundHotKeyListBox->setName ("SoundHotKey ListBox");

    addAndMakeVisible (soundFileDragAndDropTarget = new SoundFileDragAndDropTarget (this));
    soundFileDragAndDropTarget->setName ("Sound File DragAndDrop Target");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	setApplicationCommandManagerToWatch(&MainWindow::getApplicationCommandManager());
	//Command_LoadSoundHotKeyFile();
	SoundHotKeyListBox->setModel(this);
	SoundHotKeyListBox->setRowHeight(75);
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	currentConfigFile->Unload();
	currentConfigFile = nullptr;
    //[/Destructor_pre]

    SoundHotKeyListBox = nullptr;
    soundFileDragAndDropTarget = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    SoundHotKeyListBox->setBounds (0, 80, 376, 288);
    soundFileDragAndDropTarget->setBounds (0, 0, 376, 80);
    //[UserResized] Add your own custom resize handling here..
	Rectangle<int> area(getLocalBounds());
	int menuBarHeight = LookAndFeel::getDefaultLookAndFeel().getDefaultMenuBarHeight();
	menuBar->setBounds(area.removeFromTop(menuBarHeight));
	soundFileDragAndDropTarget->setBounds(area.removeFromTop(80));
	SoundHotKeyListBox->setBounds(area.reduced(4));
	soundFileDragAndDropTarget->repaint();
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

int MainComponent::getNumRows() { return (currentConfigFile == nullptr) ? 0 : currentConfigFile->NumberOfSoundHotKeyEntries(); }

void MainComponent::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{

}

Component* MainComponent::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
	jassert(existingComponentToUpdate == nullptr || dynamic_cast<SoundHotKeyView *> (existingComponentToUpdate) != nullptr);

	SoundHotKeyView* comp = static_cast<SoundHotKeyView *> (existingComponentToUpdate);

	int totalSounds = currentConfigFile->NumberOfSoundHotKeyEntries();
	if (rowNumber < 0 || rowNumber >= totalSounds)
	{
		if (existingComponentToUpdate != nullptr)
		{
			delete existingComponentToUpdate;
			existingComponentToUpdate = nullptr;
		}
		return nullptr;
	}

	SoundHotKeyInfoContainer *container = currentConfigFile->GetContainerByIndex(rowNumber);
	if (comp == nullptr)
		comp = new SoundHotKeyView(this, container);
	else if (container != comp->getSoundHotKeyInfoContainer())
	{
		//This is goofy.  We can can an existing component that wasn't made for this particular row.
		//Just scrub it and make a new one.
		if (existingComponentToUpdate != nullptr)
		{
			delete existingComponentToUpdate;
			existingComponentToUpdate = nullptr;
		}
		comp = new SoundHotKeyView(this, container);
	}
	else
		comp->update(isRowSelected);

	return comp;
}

StringArray MainComponent::getMenuBarNames()
{
	const char *const names[] = { "File", nullptr };
	return StringArray(names);
}

PopupMenu MainComponent::getMenuForIndex(int menuIndex, const String& /*menuName*/)
{
	ApplicationCommandManager* commandManager = &MainWindow::getApplicationCommandManager();
	PopupMenu menu;
	menu.addCommandItem(commandManager, CommandIDs::cLoadSoundHotKeyFile, "Load File");
	menu.addCommandItem(commandManager, CommandIDs::cSaveSoundHotkeyFile, "Save File");

	return menu;
}

void MainComponent::menuItemSelected(int menuItemID, int /*topLevelMenuIndex*/)
{

}

void MainComponent::CreateInfoFromFile(const String &file)
{
	int index = currentConfigFile->AddSoundHotKey(file);
	SoundHotKeyListBox->updateContent();
	SoundHotKeyListBox->scrollToEnsureRowIsOnscreen(index);
}

void MainComponent::RemoveInfo(CommandID id)
{
	currentConfigFile->RemoveSoundHotKey(id);
	SoundHotKeyListBox->updateContent();
}

void MainComponent::Command_LoadSoundHotKeyFile()
{
	FileChooser fc("Choose a file to open...", File::getCurrentWorkingDirectory(), "*.json", false);

	if (fc.browseForFileToOpen())
	{
		File fileToLoad = fc.getResult();
		LoadSoundHotKeyFile(fileToLoad);
	}
}
void MainComponent::LoadSoundHotKeyFile(File &file)
{
	if (currentConfigFile != nullptr)
	{
		currentConfigFile->Unload();
		currentConfigFile = nullptr;
	}

	currentConfigFile = new SoundHotKeyConfigFile(*audioDeviceManager, MainWindow::getApplicationCommandManager());
	if (!currentConfigFile->LoadFile(file))
	{
		//Unload and load a blank config file.
		currentConfigFile = nullptr;
		currentConfigFile = new SoundHotKeyConfigFile(*audioDeviceManager, MainWindow::getApplicationCommandManager());
	}	
		
	SoundHotKeyListBox->updateContent();
}
void MainComponent::Command_SaveSoundHotKeyFile()
{
	FileChooser fc("Choose a file to save...", File::getCurrentWorkingDirectory(), "*.json", false);

	if (fc.browseForFileToSave(true))
	{
		File chosenFile = fc.getResult();
		SaveSoundHotKeyFile(chosenFile);
	}
}

void MainComponent::SaveSoundHotKeyFile(File &file)
{
	currentConfigFile->SaveFileAs(file);
}

ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
	// this will return the next parent component that is an ApplicationCommandTarget (in this
	// case, there probably isn't one, but it's best to use this method in your own apps).
	return findFirstTargetParentComponent();
}

void MainComponent::getAllCommands(Array<CommandID>& commands)
{
	commands.add(CommandID(CommandIDs::cLoadSoundHotKeyFile));
	commands.add(CommandID(CommandIDs::cSaveSoundHotkeyFile));
	// this returns the set of all commands that this target can perform..
	for (int i = 0; i < currentConfigFile->NumberOfSoundHotKeyEntries(); ++i)
	{
		commands.add(currentConfigFile->GetContainerByIndex(i)->getCommandID());
	}
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
	switch (commandID)
	{
	case CommandIDs::cLoadSoundHotKeyFile:
		result.setInfo("Load File", "Load a Sound Hotkey File", juce::String::empty, 0);
		result.addDefaultKeypress('L', juce::ModifierKeys::ctrlModifier);
		break;
	case CommandIDs::cSaveSoundHotkeyFile:
		result.setInfo("Save File", "Save the current configuration to a file.", juce::String::empty, 0);
		result.addDefaultKeypress('S', juce::ModifierKeys::ctrlModifier);
		break;
	default:
		SoundHotKeyInfoContainer *container = currentConfigFile->GetContainerByCommandID(commandID);
		if (container == nullptr)
			return;

		result = container->GetSoundHotKeyInfo().getApplicationCommandInfo();
	}
}

bool MainComponent::perform(const InvocationInfo& info)
{
	switch (info.commandID)
	{
	case CommandIDs::cLoadSoundHotKeyFile:
		Command_LoadSoundHotKeyFile();
		break;
	case CommandIDs::cSaveSoundHotkeyFile:
		Command_SaveSoundHotKeyFile();
		break;
	default:
		SoundHotKeyInfoContainer *container = currentConfigFile->GetContainerByCommandID(info.commandID);
		if (container == nullptr)
			return false;

		container->PlayOrStop();
		//Play sound here.
	}

	return true;
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component, public ApplicationCommandTarget, public ListBoxModel, public ChangeBroadcaster, public MenuBarModel, public SoundInfoOperationsListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="SoundHotKey ListBox" id="9551b420e40a1074" memberName="SoundHotKeyListBox"
                    virtualName="" explicitFocusOrder="0" pos="0 80 376 288" class="ListBox"
                    params=""/>
  <GENERICCOMPONENT name="Sound File DragAndDrop Target" id="1bec592c5b8f0acb" memberName="soundFileDragAndDropTarget"
                    virtualName="" explicitFocusOrder="0" pos="0 0 376 80" class="SoundFileDragAndDropTarget"
                    params="this"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
