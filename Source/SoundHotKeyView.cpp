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

#include "SoundHotKeyView.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SoundHotKeyView::SoundHotKeyView ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (lblSoundName = new Label ("Sound Name",
                                                 TRANS("Sound Name\n")));
    lblSoundName->setTooltip (TRANS("The name of the sound to be played\n"));
    lblSoundName->setFont (Font (15.00f, Font::plain));
    lblSoundName->setJustificationType (Justification::centredLeft);
    lblSoundName->setEditable (false, false, false);
    lblSoundName->setColour (TextEditor::textColourId, Colours::black);
    lblSoundName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Sound:\n")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Keys:\n")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lblHotKey = new Label ("Hot Key",
                                              TRANS("Hot Key")));
    lblHotKey->setTooltip (TRANS("The name of the sound to be played\n"));
    lblHotKey->setFont (Font (15.00f, Font::plain));
    lblHotKey->setJustificationType (Justification::centredLeft);
    lblHotKey->setEditable (false, false, false);
    lblHotKey->setColour (TextEditor::textColourId, Colours::black);
    lblHotKey->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 50);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SoundHotKeyView::~SoundHotKeyView()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lblSoundName = nullptr;
    label = nullptr;
    label2 = nullptr;
    lblHotKey = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SoundHotKeyView::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SoundHotKeyView::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    lblSoundName->setBounds (64, 0, 416, 24);
    label->setBounds (0, 0, 56, 24);
    label2->setBounds (0, 24, 56, 24);
    lblHotKey->setBounds (64, 24, 416, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SoundHotKeyView" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="600" initialHeight="50">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="Sound Name" id="86c88e3f451a529d" memberName="lblSoundName"
         virtualName="" explicitFocusOrder="0" pos="64 0 416 24" tooltip="The name of the sound to be played&#10;"
         edTextCol="ff000000" edBkgCol="0" labelText="Sound Name&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="77b34494e0b0f430" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 0 56 24" edTextCol="ff000000" edBkgCol="0"
         labelText="Sound:&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2f546040ef7989e3" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="0 24 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Keys:&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Hot Key" id="f76087d55d394f8c" memberName="lblHotKey" virtualName=""
         explicitFocusOrder="0" pos="64 24 416 24" tooltip="The name of the sound to be played&#10;"
         edTextCol="ff000000" edBkgCol="0" labelText="Hot Key" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
