/*
  ==============================================================================

    KeyMappingList.cpp
    Created: 16 Oct 2015 10:57:28am
    Author:  johnathan

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "KeyMappingList.h"
#include "SoundHotKeyInfo.h"

//==============================================================================

KeyMappingList::KeyMappingList(ApplicationCommandManager& _commandManager, SoundHotKeyInfo *_info)
	: commandManager(_commandManager), info(_info)
{
	setInterceptsMouseClicks(false, true);

	update();

	if (info != nullptr)
	{
		for (int i = 0; i < info->KeyPresses.size(); ++i)
			addKeyPressButton(i, info->KeyPresses.getReference(i), false);
	}
	addKeyButton = nullptr;
	addKeyPressButton(-1, KeyPress(-1), false);
}

KeyMappingList::~KeyMappingList()
{
	addKeyButton = nullptr;
	keyChangeButtons.clear(true);
	info = nullptr;
}

void KeyMappingList::addKeyPressButton(int keyNum, const KeyPress &keyPress, const bool isReadOnly)
{
	ChangeKeyButton* b = nullptr;
	if (keyNum < 0)
	{
		if (addKeyButton != nullptr)
			return;

		addKeyButton = new ChangeKeyButton(this, keyPress, keyNum);
		b = addKeyButton;
	}
	else
	{
		b = new ChangeKeyButton(this, keyPress, keyNum);
		keyChangeButtons.add(b);
	}

	b->setEnabled(!isReadOnly);
	b->setVisible(keyChangeButtons.size() <= (int)maxNumAssignments);
	addChildComponent(b);
	update();
}

void KeyMappingList::paint(Graphics& g)
{
	g.setFont(getHeight() * 0.7f);
	g.setColour(findColour(KeyMappingEditorComponent::textColourId));

	/*g.drawFittedText(TRANS(commandManager.getNameOfCommand(commandID)),
		4, 0, jmax(40, getChildComponent(0)->getX() - 5), getHeight(),
		Justification::centredLeft, true);*/
}

void KeyMappingList::resized()
{
	update();
}

void KeyMappingList::update()
{
	int x = getWidth() - 4;
	int height = getHeight() - 2;
	if (x <= 0 || height <= 0)
		return;

	ChangeKeyButton* b = addKeyButton;
	int i = 0;
	do
	{
		b->fitToContent(height);
		b->setTopRightPosition(x, 1);
		x = b->getX() - 5;
		b = (i >= keyChangeButtons.size()) ? nullptr : keyChangeButtons.getUnchecked(i);
		++i;
	} 
	while (b != nullptr);
}

void KeyMappingList::OnKeyAdded(const KeyPress &newKeyPress, int keyIndex)
{
	if (info == nullptr)
		return;

	commandManager.getKeyMappings()->addKeyPress(info->CommandID, newKeyPress, keyIndex);
	info->KeyPresses.add(newKeyPress);
	addKeyPressButton(info->KeyPresses.indexOf(newKeyPress), newKeyPress, false);
	
}
void KeyMappingList::OnKeyRemoved(ChangeKeyButton *button, const KeyPress &keyPress, int keyIndex)
{
	if (info == nullptr)
		return;

	commandManager.getKeyMappings()->removeKeyPress(info->CommandID, keyPress.getKeyCode());
	info->KeyPresses.removeFirstMatchingValue(keyPress);
	removeChildComponent(button);
	keyChangeButtons.removeObject(button, true);
}

void KeyMappingList::OnKeyChanged(const KeyPress &oldKeyPress, const KeyPress &newKeyPress, int keyIndex)
{
	if (info == nullptr)
		return;

	const CommandID previousCommand = commandManager.getKeyMappings()->findCommandForKeyPress(newKeyPress);

	if (previousCommand == 0)
	{
		commandManager.getKeyMappings()->removeKeyPress(newKeyPress);

		commandManager.getKeyMappings()->removeKeyPress(info->CommandID, oldKeyPress.getKeyCode());
		info->KeyPresses.removeFirstMatchingValue(oldKeyPress);
		commandManager.getKeyMappings()->addKeyPress(info->CommandID, newKeyPress, keyIndex);
		info->KeyPresses.add(newKeyPress);
	}
	else
	{
		/*AlertWindow::showOkCancelBox(AlertWindow::WarningIcon,
			TRANS("Change key-mapping"),
			TRANS("This key is already assigned to the command \"CMDN\"")
			.replace("CMDN", commandManager.getNameOfCommand(previousCommand))
			+ "\n\n"
			+ TRANS("Do you want to re-assign it to this new command instead?"),
			TRANS("Re-assign"),
			TRANS("Cancel"),
			this,
			ModalCallbackFunction::forComponent(assignNewKeyCallback,
			this, KeyPress(newKey)));*/
	}
}

CommandID KeyMappingList::GetCommandIDForKeyPress(const KeyPress &keyPress)
{
	return commandManager.getKeyMappings()->findCommandForKeyPress(keyPress);
}

String KeyMappingList::GetCommandName(CommandID id)
{
	return commandManager.getNameOfCommand(id);
}

//ChangeKeyButton *KeyMappingList::GetChangeKeyButtonByKeyCode(int keyCode)
//{
//	for (int i = 0; i < keyChangeButtons.size(); ++i)
//	{
//		ChangeKeyButton *b = keyChangeButtons.getUnchecked(i);
//		if (b == nullptr)
//			return nullptr;
//
//		if (b->getKeyCode() == keyCode)
//			return b;
//	}
//
//	return nullptr;
//}
