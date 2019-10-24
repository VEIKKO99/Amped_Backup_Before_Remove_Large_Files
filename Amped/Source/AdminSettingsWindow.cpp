/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "AmpedAudioProcessorBase.h"
//[/Headers]

#include "AdminSettingsWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AdminSettingsWindow::AdminSettingsWindow ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    preTube1Settings.reset (new UITubeSettings());
    preTube2Settings.reset (new UITubeSettings());
    powerAmpTubeSettings.reset (new UITubeSettings());

    preTube1Settings->setBounds (0, 80, preTube1Settings->getWidth(), preTube1Settings->getHeight());
    preTube2Settings->setBounds (0, 10 + 80 + preTube2Settings->getHeight(), preTube2Settings->getWidth(), preTube2Settings->getHeight());
    powerAmpTubeSettings->setBounds (0, 20 + 80 + preTube2Settings->getHeight() * 2, powerAmpTubeSettings->getWidth(), powerAmpTubeSettings->getHeight());

    addAndMakeVisible(preTube1Settings.get());
    addAndMakeVisible(preTube2Settings.get());
    addAndMakeVisible(powerAmpTubeSettings.get());

    //[/Constructor_pre]

    preInputType.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (preInputType.get());
    preInputType->setEditableText (false);
    preInputType->setJustificationType (Justification::centredLeft);
    preInputType->setTextWhenNothingSelected (String());
    preInputType->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    preInputType->addItem (TRANS("\t\tkGuitarKit"), 1);
    preInputType->addItem (TRANS("\t\tkFender"), 2);
    preInputType->addItem (TRANS("\t\tkMarshall"), 3);
    preInputType->addItem (TRANS("\t\tkMesa"), 4);
    preInputType->addListener (this);

    preInputType->setBounds (8, 32, 150, 24);

    label.reset (new Label ("new label",
                            TRANS("PRE Input Type\n")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (0, 0, 150, 24);

    updateButton.reset (new TextButton ("new button"));
    addAndMakeVisible (updateButton.get());
    updateButton->setButtonText (TRANS("Update"));
    updateButton->addListener (this);

    updateButton->setBounds (840, 16, 150, 24);

    label3.reset (new Label ("new label",
                             TRANS("Input Max / Min")));
    addAndMakeVisible (label3.get());
    label3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label3->setBounds (808, 72, 150, 24);

    label2.reset (new Label ("new label",
                             TRANS("NOT USED!")));
    addAndMakeVisible (label2.get());
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label2->setBounds (808, 136, 150, 24);

    label4.reset (new Label ("new label",
                             TRANS("Output Max / Min")));
    addAndMakeVisible (label4.get());
    label4->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label4->setBounds (808, 200, 150, 24);

    inMin.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (inMin.get());
    inMin->setMultiLine (false);
    inMin->setReturnKeyStartsNewLine (false);
    inMin->setReadOnly (false);
    inMin->setScrollbarsShown (true);
    inMin->setCaretVisible (true);
    inMin->setPopupMenuEnabled (true);
    inMin->setText (String());

    inMin->setBounds (816, 104, 47, 24);

    inMax.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (inMax.get());
    inMax->setMultiLine (false);
    inMax->setReturnKeyStartsNewLine (false);
    inMax->setReadOnly (false);
    inMax->setScrollbarsShown (true);
    inMax->setCaretVisible (true);
    inMax->setPopupMenuEnabled (true);
    inMax->setText (String());

    inMax->setBounds (872, 104, 47, 24);

    dMin.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (dMin.get());
    dMin->setMultiLine (false);
    dMin->setReturnKeyStartsNewLine (false);
    dMin->setReadOnly (false);
    dMin->setScrollbarsShown (true);
    dMin->setCaretVisible (true);
    dMin->setPopupMenuEnabled (true);
    dMin->setText (String());

    dMin->setBounds (816, 168, 47, 24);

    dMax.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (dMax.get());
    dMax->setMultiLine (false);
    dMax->setReturnKeyStartsNewLine (false);
    dMax->setReadOnly (false);
    dMax->setScrollbarsShown (true);
    dMax->setCaretVisible (true);
    dMax->setPopupMenuEnabled (true);
    dMax->setText (String());

    dMax->setBounds (872, 168, 47, 24);

    mMin.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (mMin.get());
    mMin->setMultiLine (false);
    mMin->setReturnKeyStartsNewLine (false);
    mMin->setReadOnly (false);
    mMin->setScrollbarsShown (true);
    mMin->setCaretVisible (true);
    mMin->setPopupMenuEnabled (true);
    mMin->setText (String());

    mMin->setBounds (816, 232, 47, 24);

    mMax.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (mMax.get());
    mMax->setMultiLine (false);
    mMax->setReturnKeyStartsNewLine (false);
    mMax->setReadOnly (false);
    mMax->setScrollbarsShown (true);
    mMax->setCaretVisible (true);
    mMax->setPopupMenuEnabled (true);
    mMax->setText (String());

    mMax->setBounds (872, 232, 47, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1000, 800);


    //[Constructor] You can add your own custom stuff here..

    //[/Constructor]
}

AdminSettingsWindow::~AdminSettingsWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    changeInterface = nullptr;
    //[/Destructor_pre]

    preInputType = nullptr;
    label = nullptr;
    updateButton = nullptr;
    label3 = nullptr;
    label2 = nullptr;
    label4 = nullptr;
    inMin = nullptr;
    inMax = nullptr;
    dMin = nullptr;
    dMax = nullptr;
    mMin = nullptr;
    mMax = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AdminSettingsWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AdminSettingsWindow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void AdminSettingsWindow::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == preInputType.get())
    {
        //[UserComboBoxCode_preInputType] -- add your combo box handling code here..
        //[/UserComboBoxCode_preInputType]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void AdminSettingsWindow::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == updateButton.get())
    {
        //[UserButtonCode_updateButton] -- add your button handler code here..
        if (changeInterface != nullptr) {
            updateSettings();
            changeInterface->settingChanged();
        }
        //[/UserButtonCode_updateButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void AdminSettingsWindow::updateSettings() {
    auto settings = changeInterface->getCurrentSettings();
    settings->ampSettings.inputType = static_cast<PreAmp::EInputType>(preInputType->getSelectedItemIndex());
    preTube1Settings->updateSettings(settings->ampSettings.preAmpTubes[0]);
    preTube2Settings->updateSettings(settings->ampSettings.preAmpTubes[1]);
    powerAmpTubeSettings->updateSettings(settings->ampSettings.powerAmpTube);

    settings->gainSettings[GainProcessorId::InputGain].min = inMin->getText().getFloatValue();
    settings->gainSettings[GainProcessorId::InputGain].max = inMax->getText().getFloatValue();
    settings->gainSettings[GainProcessorId::OutputGain].max = mMax->getText().getFloatValue();
    settings->gainSettings[GainProcessorId::OutputGain].min = mMin->getText().getFloatValue();
    settings->gainSettings[GainProcessorId::DriveGain].min = inMin->getText().getFloatValue();
    settings->gainSettings[GainProcessorId::DriveGain].max = inMax->getText().getFloatValue();


    //   settings->ampSettings.preAmpTubes[0].tubeType = static_cast<PreAmp::EInputType>(preTube1->getSelectedItemIndex());

}

AdminSettingsWindow::AdminSettingsWindow (ISoundSettingsChanged* changed) : AdminSettingsWindow()
{
    changeInterface = changed;
    setupUI();
}

void AdminSettingsWindow::setupUI(){
    auto settings = changeInterface->getCurrentSettings();
    this->preInputType.get()->setSelectedItemIndex(settings->ampSettings.inputType);
    this->mMin->setText(String(settings->gainSettings[GainProcessorId::OutputGain].min),dontSendNotification);
    this->mMax->setText(String(settings->gainSettings[GainProcessorId::OutputGain].max), dontSendNotification);
    this->dMin->setText(String(settings->gainSettings[GainProcessorId::DriveGain].min), dontSendNotification);
    this->dMax->setText(String(settings->gainSettings[GainProcessorId::DriveGain].max), dontSendNotification);
    this->inMin->setText(String(settings->gainSettings[GainProcessorId::InputGain].min), dontSendNotification);
    this->inMax->setText(String(settings->gainSettings[GainProcessorId::InputGain].max), dontSendNotification);

    this->preTube1Settings->setupUI(settings->ampSettings.preAmpTubes[0],"Pre Amp Tube 1");
    this->preTube2Settings->setupUI(settings->ampSettings.preAmpTubes[1],"Pre Amp Tube 2");
    this->powerAmpTubeSettings->setupUI(settings->ampSettings.powerAmpTube, "Power Amp Tube");
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AdminSettingsWindow" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="1000" initialHeight="800">
  <BACKGROUND backgroundColour="ff323e44"/>
  <COMBOBOX name="new combo box" id="c0d7bac554763e1" memberName="preInputType"
            virtualName="" explicitFocusOrder="0" pos="8 32 150 24" editable="0"
            layout="33" items="&#9;&#9;kGuitarKit&#10;&#9;&#9;kFender&#10;&#9;&#9;kMarshall&#10;&#9;&#9;kMesa"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="7cdf1ec38d0da7b3" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 0 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="PRE Input Type&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="3518e4a88f598a7" memberName="updateButton"
              virtualName="" explicitFocusOrder="0" pos="840 16 150 24" buttonText="Update"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="7237a071422d3973" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="808 72 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Max / Min" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="9e5c6ee92a31ff20" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="808 136 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="NOT USED!" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="ea8a683340dc7a41" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="808 200 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Max / Min" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="8e867a582e3c87dd" memberName="inMin"
              virtualName="" explicitFocusOrder="0" pos="816 104 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="bf18a407ae51f5ef" memberName="inMax"
              virtualName="" explicitFocusOrder="0" pos="872 104 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="2345afe3a1dc68e1" memberName="dMin"
              virtualName="" explicitFocusOrder="0" pos="816 168 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="cebb191ed9ac93f9" memberName="dMax"
              virtualName="" explicitFocusOrder="0" pos="872 168 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="46143fb20b12f67" memberName="mMin"
              virtualName="" explicitFocusOrder="0" pos="816 232 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="ea4f7edcb1f0a4f1" memberName="mMax"
              virtualName="" explicitFocusOrder="0" pos="872 232 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

