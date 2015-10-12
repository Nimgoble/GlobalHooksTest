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
#include "MainWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent () :
	keyMappingEditor(*MainWindow::getApplicationCommandManager().getKeyMappings(), true)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	addAndMakeVisible(&keyMappingEditor);
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



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

    //[UserResized] Add your own custom resize handling here..
	keyMappingEditor.setBounds(getLocalBounds().reduced(4));
    //[/UserResized]
}

void MainComponent::minimisationStateChanged(bool isNowMinimised)
{
	bool areWe = isNowMinimised;
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
	// this will return the next parent component that is an ApplicationCommandTarget (in this
	// case, there probably isn't one, but it's best to use this method in your own apps).
	return findFirstTargetParentComponent();
}

void MainComponent::getAllCommands(Array<CommandID>& commands)
{
	// this returns the set of all commands that this target can perform..
	const CommandID ids[] =
	{
		MainComponent::CommandIDs::Command1,
		MainComponent::CommandIDs::Command2
	};

	commands.addArray(ids, numElementsInArray(ids));
}

void MainComponent::getCommandInfo(CommandID commandID, ApplicationCommandInfo& result)
{
	const String testCommandsCategory("Test Commands");

	switch (commandID)
	{
	case MainComponent::CommandIDs::Command1:
		result.setInfo("Command 1", "Test Command 1", testCommandsCategory, 0);
		result.addDefaultKeypress('-', ModifierKeys::commandModifier);
		break;

	case MainComponent::CommandIDs::Command2:
		result.setInfo("Command 2", "Test Command 2", testCommandsCategory, 0);
		result.addDefaultKeypress('=', ModifierKeys::commandModifier);
		break;
	default:
		break;
	}
}

bool MainComponent::perform(const InvocationInfo& info)
{
	MainWindow* mainWindow = MainWindow::getMainWindow();

	if (mainWindow == nullptr)
		return true;

	int debugMe = 0;
	switch (info.commandID)
	{
		case MainComponent::CommandIDs::Command1:
		{
			debugMe = 1;
		}
		break;
		case MainComponent::CommandIDs::Command2:
		{
			debugMe = 2;
		}
		break;
		default:
			return false;
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
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
