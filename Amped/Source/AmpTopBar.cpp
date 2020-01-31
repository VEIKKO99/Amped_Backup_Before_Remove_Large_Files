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
    licenceManagerBtn->setColour (TextButton::buttonColourId, Colour (0xff111111));

    licenceManagerBtn->setBounds (984, 77, 201, 39);

    pedalBoardBtn.reset (new TextButton ("new button"));
    addAndMakeVisible (pedalBoardBtn.get());
    pedalBoardBtn->setButtonText (TRANS("PEDAL BOARD"));
    pedalBoardBtn->addListener (this);
    pedalBoardBtn->setColour (TextButton::buttonColourId, Colour (0xff111111));

    pedalBoardBtn->setBounds (752, 77, 201, 39);

    ampComboBox.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (ampComboBox.get());
    ampComboBox->setEditableText (false);
    ampComboBox->setJustificationType (Justification::centred);
    ampComboBox->setTextWhenNothingSelected (String());
    ampComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    ampComboBox->addItem (TRANS("EDVH 5034"), 1);
    ampComboBox->addItem (TRANS("RECTIFIED"), 2);
    ampComboBox->addItem (TRANS("MARS 2203"), 3);
    ampComboBox->addItem (TRANS("FREEMAN"), 4);
    ampComboBox->addItem (TRANS("FLUFFERSLAX"), 5);
    ampComboBox->addSeparator();
    ampComboBox->addSeparator();
    ampComboBox->addListener (this);

    ampComboBox->setBounds (8, 77, 200, 39);

    presetComboBox.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (presetComboBox.get());
    presetComboBox->setEditableText (false);
    presetComboBox->setJustificationType (Justification::centred);
    presetComboBox->setTextWhenNothingSelected (String());
    presetComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    presetComboBox->addItem (TRANS("DJENT RHYTH"), 1);
    presetComboBox->addSeparator();
    presetComboBox->addListener (this);

    presetComboBox->setBounds (240, 77, 200, 39);

    label.reset (new Label ("new label",
                            TRANS("AMP")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (8, 50, 200, 24);

    label2.reset (new Label ("new label",
                             TRANS("PRESET\n")));
    addAndMakeVisible (label2.get());
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centred);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label2->setBounds (240, 50, 200, 24);


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
    ampComboBox = nullptr;
    presetComboBox = nullptr;
    label = nullptr;
    label2 = nullptr;


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

    if (comboBoxThatHasChanged == ampComboBox.get())
    {
        //[UserComboBoxCode_ampComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_ampComboBox]
    }
    else if (comboBoxThatHasChanged == presetComboBox.get())
    {
        //[UserComboBoxCode_presetComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_presetComboBox]
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

void AmpTopBar::setProcessor(AmpedAudioProcessor* processor)
{
    this->processor = processor;
    // When the proessor is set we know that we can init amps UI & presets UI
    initAmps();
    initPresets();
}

void AmpTopBar::ampChanged()
{
    if (processor != nullptr)
    {
        processor->selectSettingWithId(ampComboBox->getSelectedItemIndex());
    }
}

void AmpTopBar::initAmps() {
    ampComboBox->clear(dontSendNotification);
    if (processor != nullptr)
    {
        auto settings = &processor->getSoundSettingsModel();
        for (int i = 0; i < settings->getSize(); i++)
        {
            ampComboBox->addItem(settings->getSettingsWithIndex(i)->name, i+1); // Combobox ids must start from 1.
        }
        ampComboBox->setSelectedItemIndex(settings->currentSettingIndex(), dontSendNotification);
        ampComboBox->onChange = [this] { ampChanged(); };
    }
}

void AmpTopBar::initPresets() {
    presetComboBox->clear(dontSendNotification);
    if (processor != nullptr)
    {
        auto presets = processor->getSoundSettingsModel().getCurrentSetting()->presetSettings;
        int index = 0;
        for (std::shared_ptr<PresetSetting> preset : presets)
        {
            presetComboBox->addItem(preset->name, index +1); // Combobox ids must start from 1.
            index++;
        }
      //  ampComboBox->setSelectedItemIndex( processor->getSoundSettingsModel().getCurrentSetting()->pre, dontSendNotification);
        ampComboBox->onChange = [this] { ampChanged(); };
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
              virtualName="" explicitFocusOrder="0" pos="984 77 201 39" bgColOff="ff111111"
              buttonText="LICENCE MANAGER" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="e9a6a188154bda9d" memberName="pedalBoardBtn"
              virtualName="" explicitFocusOrder="0" pos="752 77 201 39" bgColOff="ff111111"
              buttonText="PEDAL BOARD" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <COMBOBOX name="new combo box" id="902abde5edcf97b0" memberName="ampComboBox"
            virtualName="" explicitFocusOrder="0" pos="8 77 200 39" editable="0"
            layout="36" items="EDVH 5034&#10;RECTIFIED&#10;MARS 2203&#10;FREEMAN&#10;FLUFFERSLAX&#10;&#10;"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="62b875f834df3cde" memberName="presetComboBox"
            virtualName="" explicitFocusOrder="0" pos="240 77 200 39" editable="0"
            layout="36" items="DJENT RHYTH&#10;" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="346bc6bb8bfb147b" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 50 200 24" edTextCol="ff000000"
         edBkgCol="0" labelText="AMP" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="a41fe87fd2a1347e" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="240 50 200 24" edTextCol="ff000000"
         edBkgCol="0" labelText="PRESET&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

