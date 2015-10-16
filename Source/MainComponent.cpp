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

#define COMMANDS_BASE 0x2200
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	addAndMakeVisible(menuBar = new MenuBarComponent(this));
    //[/Constructor_pre]

    addAndMakeVisible (SoundHotKeyListBox = new ListBox());
    SoundHotKeyListBox->setName ("SoundHotKey ListBox");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	setApplicationCommandManagerToWatch(&MainWindow::getApplicationCommandManager());
	Command_LoadSoundHotKeyFile();
	SoundHotKeyListBox->setModel(this);
	SoundHotKeyListBox->setRowHeight(75);
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	soundHotKeys.clear(true);
    //[/Destructor_pre]

    SoundHotKeyListBox = nullptr;


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

    //SoundHotKeyListBox->setBounds (0, 0, 376, 288);
    //[UserResized] Add your own custom resize handling here..
	Rectangle<int> area(getLocalBounds());
	menuBar->setBounds(area.removeFromTop(LookAndFeel::getDefaultLookAndFeel().getDefaultMenuBarHeight()));
	/*area.removeFromTop(20);
	area = area.removeFromTop(33);*/
	SoundHotKeyListBox->setBounds(area.reduced(4));
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

int MainComponent::getNumRows() { return soundHotKeys.size(); }

void MainComponent::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{

}

Component* MainComponent::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
	jassert(existingComponentToUpdate == nullptr || dynamic_cast<SoundHotKeyView *> (existingComponentToUpdate) != nullptr);

	SoundHotKeyView* comp = static_cast<SoundHotKeyView *> (existingComponentToUpdate);

	int totalSounds = soundHotKeys.size();
	if (rowNumber < 0 || rowNumber >= totalSounds)
	{
		if (existingComponentToUpdate != nullptr)
		{
			delete existingComponentToUpdate;
			existingComponentToUpdate = nullptr;
		}
		return nullptr;
	}

	const SoundHotKeyInfo &info = *soundHotKeys.getUnchecked(rowNumber);
	if (comp == nullptr)
		comp = new SoundHotKeyView(info);
	else
		comp->update(info);

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
	//menu.addCommandItem(commandManager, )

	return menu;
}

void MainComponent::menuItemSelected(int menuItemID, int /*topLevelMenuIndex*/)
{

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
	soundHotKeys.clear(true);

	String jsonString = file.loadFileAsString();
	var json;
	Result result = JSON::parse(jsonString, json);
	if (result.ok())
	{
		if (json.isArray())
		{
			for (int i = 0; i < json.size(); ++i)
			{
				var& child(json[i]);
				if (child.isVoid())
					continue;

				SoundHotKeyInfo *info = new SoundHotKeyInfo(child);
				info->CommandID = CommandID(COMMANDS_BASE + i);
				soundHotKeys.add(info);
			}
		}
	}
	ApplicationCommandManager* commandManager = &MainWindow::getApplicationCommandManager();
	commandManager->commandStatusChanged();
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
	Array<var> children;
	for (int i = 0; i < soundHotKeys.size(); ++i)
	{
		var childJSON = soundHotKeys.getUnchecked(i)->toJSON();
		children.add(childJSON);
	}
	var root(children);
	FileOutputStream *outputStream = file.createOutputStream();
	JSON::writeToStream(*outputStream, root);
	outputStream->flush();
	delete outputStream;
	outputStream = nullptr;
}


ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
	// this will return the next parent component that is an ApplicationCommandTarget (in this
	// case, there probably isn't one, but it's best to use this method in your own apps).
	return findFirstTargetParentComponent();
}

void MainComponent::getAllCommands(Array<CommandID>& commands)
{
	// this returns the set of all commands that this target can perform..
	for (int i = 0; i < soundHotKeys.size(); ++i)
	{
		commands.add(CommandID(COMMANDS_BASE + i));
	}
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
	int id = ((int)commandID) - COMMANDS_BASE;
	int totalCommands = soundHotKeys.size();
	if (id < 0 || id >= totalCommands)
		return;

	SoundHotKeyInfo *info = soundHotKeys.getUnchecked(id);
	result.setInfo(info->Name, juce::String::empty, juce::String::empty, 0);
	if (info->KeyPresses.size() > 0)
	{
		const KeyPress &defaultKeyPress = info->KeyPresses.getUnchecked(0);
		result.addDefaultKeypress(defaultKeyPress.getKeyCode(), defaultKeyPress.getModifiers());
	}
}

bool MainComponent::perform(const InvocationInfo& info)
{
	int id = (int)info.commandID - COMMANDS_BASE;
	int totalCommands = soundHotKeys.size();
	if (id < 0 || id >= totalCommands)
		return false;

	SoundHotKeyInfo *shkinfo = soundHotKeys.getUnchecked(id);
	if (shkinfo != nullptr)
	{
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
                 parentClasses="public Component, public ApplicationCommandTarget, public ListBoxModel, public ChangeBroadcaster"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="SoundHotKey ListBox" id="9551b420e40a1074" memberName="SoundHotKeyListBox"
                    virtualName="" explicitFocusOrder="0" pos="0 0 376 288" class="ListBox"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
