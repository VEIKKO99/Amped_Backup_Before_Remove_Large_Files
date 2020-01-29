/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "AmpTopBar.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AmpTopBar::AmpTopBar ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    licenceManagerBtn.reset (new TextButton ("new button"));
    addAndMakeVisible (licenceManagerBtn.get());
    licenceManagerBtn->setButtonText (TRANS("LICENCE MANAGER"));
    licenceManagerBtn->addListener (this);

    licenceManagerBtn->setBounds (984, 77, 201, 39);

    pedalBoardBtn.reset (new TextButton ("new button"));
    addAndMakeVisible (pedalBoardBtn.get());
    pedalBoardBtn->setButtonText (TRANS("PEDAL BOARD"));
    pedalBoardBtn->addListener (this);

    pedalBoardBtn->setBounds (752, 77, 201, 39);

    comboBox.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (comboBox.get());
    comboBox->setEditableText (false);
    comboBox->setJustificationType (Justification::centredLeft);
    comboBox->setTextWhenNothingSelected (String());
    comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox->addItem (TRANS("EDVH 5034"), 1);
    comboBox->addItem (TRANS("RECTIFIED"), 2);
    comboBox->addItem (TRANS("MARS 2203"), 3);
    comboBox->addItem (TRANS("FREEMAN"), 4);
    comboBox->addItem (TRANS("FLUFFERSLAX"), 5);
    comboBox->addSeparator();
    comboBox->addSeparator();
    comboBox->addListener (this);

    comboBox->setBounds (8, 77, 200, 39);

    comboBox2.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (comboBox2.get());
    comboBox2->setEditableText (false);
    comboBox2->setJustificationType (Justification::centredLeft);
    comboBox2->setTextWhenNothingSelected (String());
    comboBox2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox2->addItem (TRANS("DJENT RHYTH"), 1);
    comboBox2->addSeparator();
    comboBox2->addListener (this);

    comboBox2->setBounds (240, 77, 200, 39);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1200, 300);


    //[Constructor] You can add your own custom stuff here..

    pedalBoardBtn->onClick = [this] { togglePedalBoard(); };   // [8]

    //[/Constructor]
}

AmpTopBar::~AmpTopBar()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    licenceManagerBtn = nullptr;
    pedalBoardBtn = nullptr;
    comboBox = nullptr;
    comboBox2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AmpTopBar::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AmpTopBar::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void AmpTopBar::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == licenceManagerBtn.get())
    {
        //[UserButtonCode_licenceManagerBtn] -- add your button handler code here..
        //[/UserButtonCode_licenceManagerBtn]
    }
    else if (buttonThatWasClicked == pedalBoardBtn.get())
    {
        //[UserButtonCode_pedalBoardBtn] -- add your button handler code here..
        //[/UserButtonCode_pedalBoardBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void AmpTopBar::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox.get())
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox]
    }
    else if (comboBoxThatHasChanged == comboBox2.get())
    {
        //[UserComboBoxCode_comboBox2] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBox2]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void AmpTopBar::togglePedalBoard()
{
    if (mainComponent != nullptr)
    {
        mainComponent->toggleEffectsBar();
    }
}


//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AmpTopBar" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="1200" initialHeight="300">
  <BACKGROUND backgroundColour="323e44"/>
  <TEXTBUTTON name="new button" id="740067d4fd533d47" memberName="licenceManagerBtn"
              virtualName="" explicitFocusOrder="0" pos="984 77 201 39" buttonText="LICENCE MANAGER"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="e9a6a188154bda9d" memberName="pedalBoardBtn"
              virtualName="" explicitFocusOrder="0" pos="752 77 201 39" buttonText="PEDAL BOARD"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="902abde5edcf97b0" memberName="comboBox"
            virtualName="" explicitFocusOrder="0" pos="8 77 200 39" editable="0"
            layout="33" items="EDVH 5034&#10;RECTIFIED&#10;MARS 2203&#10;FREEMAN&#10;FLUFFERSLAX&#10;&#10;"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="62b875f834df3cde" memberName="comboBox2"
            virtualName="" explicitFocusOrder="0" pos="240 77 200 39" editable="0"
            layout="33" items="DJENT RHYTH&#10;" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

