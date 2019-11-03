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

    label4.reset (new Label ("new label",
                             TRANS("Output Max / Min")));
    addAndMakeVisible (label4.get());
    label4->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label4->setBounds (808, 136, 150, 24);

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

    mMin.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (mMin.get());
    mMin->setMultiLine (false);
    mMin->setReturnKeyStartsNewLine (false);
    mMin->setReadOnly (false);
    mMin->setScrollbarsShown (true);
    mMin->setCaretVisible (true);
    mMin->setPopupMenuEnabled (true);
    mMin->setText (String());

    mMin->setBounds (816, 168, 47, 24);

    mMax.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (mMax.get());
    mMax->setMultiLine (false);
    mMax->setReturnKeyStartsNewLine (false);
    mMax->setReadOnly (false);
    mMax->setScrollbarsShown (true);
    mMax->setCaretVisible (true);
    mMax->setPopupMenuEnabled (true);
    mMax->setText (String());

    mMax->setBounds (872, 168, 47, 24);

    label6.reset (new Label ("new label",
                             TRANS("\n"
                             "Gain")));
    addAndMakeVisible (label6.get());
    label6->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label6->setBounds (792, 415, 40, 24);

    fileNameLabel.reset (new Label ("new label",
                                    TRANS("Filename\n")));
    addAndMakeVisible (fileNameLabel.get());
    fileNameLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    fileNameLabel->setJustificationType (Justification::centredLeft);
    fileNameLabel->setEditable (false, false, false);
    fileNameLabel->setColour (TextEditor::textColourId, Colours::black);
    fileNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    fileNameLabel->setBounds (856, 415, 136, 24);

    cabIrUi.reset (new UIIRSettings());
    addAndMakeVisible (cabIrUi.get());
    cabIrUi->setBounds (696, 445, 300, 24);

    ampIrUi.reset (new UIIRSettings());
    addAndMakeVisible (ampIrUi.get());
    ampIrUi->setBounds (696, 485, 300, 24);

    preTube1Settings.reset (new UITubeSettings());
    addAndMakeVisible (preTube1Settings.get());
    preTube1Settings->setBounds (8, 72, 680, 144);

    preTube2Settings.reset (new UITubeSettings());
    addAndMakeVisible (preTube2Settings.get());
    preTube2Settings->setBounds (8, 221, 680, 144);

    powerAmpTubeSettings.reset (new UITubeSettings());
    addAndMakeVisible (powerAmpTubeSettings.get());
    powerAmpTubeSettings->setBounds (8, 376, 680, 144);

    knobTypeComboBox.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (knobTypeComboBox.get());
    knobTypeComboBox->setEditableText (false);
    knobTypeComboBox->setJustificationType (Justification::centredLeft);
    knobTypeComboBox->setTextWhenNothingSelected (String());
    knobTypeComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    knobTypeComboBox->addItem (TRANS("chkn"), 1);
    knobTypeComboBox->addItem (TRANS("chknb"), 2);
    knobTypeComboBox->addItem (TRANS("dizl"), 3);
    knobTypeComboBox->addItem (TRANS("frmn"), 4);
    knobTypeComboBox->addItem (TRANS("mars"), 5);
    knobTypeComboBox->addItem (TRANS("marss"), 6);
    knobTypeComboBox->addItem (TRANS("mega"), 7);
    knobTypeComboBox->addItem (TRANS("recto"), 8);
    knobTypeComboBox->addItem (TRANS("rectob"), 9);
    knobTypeComboBox->addListener (this);

    knobTypeComboBox->setBounds (184, 32, 150, 24);

    label7.reset (new Label ("new label",
                             TRANS("KNOB type\n")));
    addAndMakeVisible (label7.get());
    label7->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label7->setBounds (176, 0, 150, 24);

    bgButton.reset (new TextButton ("new button"));
    addAndMakeVisible (bgButton.get());
    bgButton->setButtonText (TRANS("Background image"));
    bgButton->addListener (this);

    bgButton->setBounds (352, 32, 128, 24);

    bgImageLabel.reset (new Label ("new label",
                                   TRANS("From memory")));
    addAndMakeVisible (bgImageLabel.get());
    bgImageLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    bgImageLabel->setJustificationType (Justification::centredLeft);
    bgImageLabel->setEditable (false, false, false);
    bgImageLabel->setColour (TextEditor::textColourId, Colours::black);
    bgImageLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    bgImageLabel->setBounds (488, 32, 192, 24);

    bassEq.reset (new UIEQSettings());
    addAndMakeVisible (bassEq.get());
    bassEq->setBounds (8, 535, 768, 40);

    middleEq.reset (new UIEQSettings());
    addAndMakeVisible (middleEq.get());
    middleEq->setBounds (8, 575, 768, 40);

    component3.reset (new UIEQSettings());
    addAndMakeVisible (component3.get());
    component3->setBounds (8, 614, 768, 40);

    trebleEq.reset (new UIEQSettings());
    addAndMakeVisible (trebleEq.get());
    trebleEq->setBounds (8, 614, 768, 40);

    label2.reset (new Label ("new label",
                             TRANS("Output Max / Min")));
    addAndMakeVisible (label2.get());
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label2->setBounds (808, 136, 150, 24);

    mMin2.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (mMin2.get());
    mMin2->setMultiLine (false);
    mMin2->setReturnKeyStartsNewLine (false);
    mMin2->setReadOnly (false);
    mMin2->setScrollbarsShown (true);
    mMin2->setCaretVisible (true);
    mMin2->setPopupMenuEnabled (true);
    mMin2->setText (String());

    mMin2->setBounds (816, 168, 47, 24);

    mMax2.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (mMax2.get());
    mMax2->setMultiLine (false);
    mMax2->setReturnKeyStartsNewLine (false);
    mMax2->setReadOnly (false);
    mMax2->setScrollbarsShown (true);
    mMax2->setCaretVisible (true);
    mMax2->setPopupMenuEnabled (true);
    mMax2->setText (String());

    mMax2->setBounds (872, 168, 47, 24);

    label5.reset (new Label ("new label",
                             TRANS("Hornet Drive (0.0 - 1.0)")));
    addAndMakeVisible (label5.get());
    label5->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label5->setBounds (808, 208, 168, 24);

    hornetDrive.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (hornetDrive.get());
    hornetDrive->setMultiLine (false);
    hornetDrive->setReturnKeyStartsNewLine (false);
    hornetDrive->setReadOnly (false);
    hornetDrive->setScrollbarsShown (true);
    hornetDrive->setCaretVisible (true);
    hornetDrive->setPopupMenuEnabled (true);
    hornetDrive->setText (String());

    hornetDrive->setBounds (816, 240, 47, 24);

    label8.reset (new Label ("new label",
                             TRANS("Hornet Presence (0.0 - 1.0)\n")));
    addAndMakeVisible (label8.get());
    label8->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label8->setBounds (808, 280, 184, 24);

    hornetPresence.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (hornetPresence.get());
    hornetPresence->setMultiLine (false);
    hornetPresence->setReturnKeyStartsNewLine (false);
    hornetPresence->setReadOnly (false);
    hornetPresence->setScrollbarsShown (true);
    hornetPresence->setCaretVisible (true);
    hornetPresence->setPopupMenuEnabled (true);
    hornetPresence->setText (String());

    hornetPresence->setBounds (816, 312, 47, 24);

    presenceEq.reset (new UIEQSettings());
    addAndMakeVisible (presenceEq.get());
    presenceEq->setBounds (8, 672, 768, 40);


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
    label4 = nullptr;
    inMin = nullptr;
    inMax = nullptr;
    mMin = nullptr;
    mMax = nullptr;
    label6 = nullptr;
    fileNameLabel = nullptr;
    cabIrUi = nullptr;
    ampIrUi = nullptr;
    preTube1Settings = nullptr;
    preTube2Settings = nullptr;
    powerAmpTubeSettings = nullptr;
    knobTypeComboBox = nullptr;
    label7 = nullptr;
    bgButton = nullptr;
    bgImageLabel = nullptr;
    bassEq = nullptr;
    middleEq = nullptr;
    component3 = nullptr;
    trebleEq = nullptr;
    label2 = nullptr;
    mMin2 = nullptr;
    mMax2 = nullptr;
    label5 = nullptr;
    hornetDrive = nullptr;
    label8 = nullptr;
    hornetPresence = nullptr;
    presenceEq = nullptr;


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
    else if (comboBoxThatHasChanged == knobTypeComboBox.get())
    {
        //[UserComboBoxCode_knobTypeComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_knobTypeComboBox]
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
    else if (buttonThatWasClicked == bgButton.get())
    {
        //[UserButtonCode_bgButton] -- add your button handler code here..
        chooseBGImageFile();
        //[/UserButtonCode_bgButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void AdminSettingsWindow::chooseBGImageFile() {
    auto settings = changeInterface->getCurrentSettings();

    FileChooser myChooser ("Please select the BG image file.",
            File::getSpecialLocation (File::userHomeDirectory),
            "*.png");
    if (myChooser.browseForFileToOpen())
    {
        File imgFile (myChooser.getResult());
        bgImageLabel->setText(imgFile.getFileName(), dontSendNotification);
        settings->uiSettings.mainBackgroundImageFileName = imgFile.getFullPathName();
    }
}

void AdminSettingsWindow::updateSettings() {
    auto settings = changeInterface->getCurrentSettings();
    settings->ampSettings.inputType = static_cast<PreAmp::EInputType>(preInputType->getSelectedItemIndex());
    preTube1Settings->updateSettings(settings->ampSettings.preAmpTubes[0]);
    preTube2Settings->updateSettings(settings->ampSettings.preAmpTubes[1]);
    powerAmpTubeSettings->updateSettings(settings->ampSettings.powerAmpTube);
    cabIrUi->updateSettings(settings->ampSettings.cabIr);
    ampIrUi->updateSettings(settings->ampSettings.ampIr);

    bassEq->updateSettings(settings->ampSettings.eqs[kBassEq]);
    middleEq->updateSettings(settings->ampSettings.eqs[kMiddleEq]);
    trebleEq->updateSettings(settings->ampSettings.eqs[kTrebleEq]);
    presenceEq->updateSettings(settings->ampSettings.eqs[kPresence]);

    settings->gainSettings[GainProcessorId::InputGain].min = inMin->getText().getFloatValue();
    settings->gainSettings[GainProcessorId::InputGain].max = inMax->getText().getFloatValue();
    settings->gainSettings[GainProcessorId::OutputGain].max = mMax->getText().getFloatValue();
    settings->gainSettings[GainProcessorId::OutputGain].min = mMin->getText().getFloatValue();
    settings->gainSettings[GainProcessorId::DriveGain].min = inMin->getText().getFloatValue();
    settings->gainSettings[GainProcessorId::DriveGain].max = inMax->getText().getFloatValue();

    settings->ampSettings.hornetPresence = hornetPresence->getText().getFloatValue();
    settings->ampSettings.hornetDrive = hornetDrive->getText().getFloatValue();


    //  settings->ampSettings.eqGain = eqGain->getText().getFloatValue();
    settings->uiSettings.selectedKnob = knobTypeComboBox->getSelectedItemIndex();



  //  settings->ampSettings.ampIr.gain = ampIrGain->getText().getFloatValue();
  //  settings->ampSettings.cabIr.gain = cabIrGain->getText().getFloatValue();


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
    this->inMin->setText(String(settings->gainSettings[GainProcessorId::InputGain].min), dontSendNotification);
    this->inMax->setText(String(settings->gainSettings[GainProcessorId::InputGain].max), dontSendNotification);

   // this->eqGain->setText(String(settings->ampSettings.eqGain));

    this->preTube1Settings->setupUI(settings->ampSettings.preAmpTubes[0],"Pre Amp Tube 1");
    this->preTube2Settings->setupUI(settings->ampSettings.preAmpTubes[1],"Pre Amp Tube 2");
    this->powerAmpTubeSettings->setupUI(settings->ampSettings.powerAmpTube, "Power Amp Tube");

    this->cabIrUi->setupUI(settings->ampSettings.cabIr,"Cab IR");
    this->ampIrUi->setupUI(settings->ampSettings.ampIr,"AMP IR");

    this->knobTypeComboBox->setSelectedItemIndex(settings->uiSettings.selectedKnob, dontSendNotification);
    this->bassEq->setupUI(settings->ampSettings.eqs[kBassEq], "Bass Eq");
    this->middleEq->setupUI(settings->ampSettings.eqs[kMiddleEq], "Middle Eq");
    this->trebleEq->setupUI(settings->ampSettings.eqs[kTrebleEq], "Treble Eq");
    this->presenceEq->setupUI(settings->ampSettings.eqs[kPresence], "Presence");

    this->hornetDrive->setText(String(settings->ampSettings.hornetDrive), dontSendNotification);
    this->hornetPresence->setText(String(settings->ampSettings.hornetPresence), dontSendNotification);


    //this->cabIrGain->setText(String(settings->ampSettings.cabIr.gain), dontSendNotification);
    //this->ampIrGain->setText(String(settings->ampSettings.ampIr.gain), dontSendNotification);
    //if (settings->ampSettings.ampIr.irFileName.length() > 0)
    //    ampIrLabel->setText(settings->ampSettings.ampIr.irFileName, dontSendNotification);
    //if (settings->ampSettings.cabIr.irFileName.length() > 0)
    //    cabIrLabel->setText(settings->ampSettings.cabIr.irFileName, dontSendNotification);

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
  <LABEL name="new label" id="ea8a683340dc7a41" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="808 136 150 24" edTextCol="ff000000"
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
  <TEXTEDITOR name="new text editor" id="46143fb20b12f67" memberName="mMin"
              virtualName="" explicitFocusOrder="0" pos="816 168 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="ea4f7edcb1f0a4f1" memberName="mMax"
              virtualName="" explicitFocusOrder="0" pos="872 168 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="78af7379fb9b0e54" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="792 415 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="&#10;Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a84735c2601cd71" memberName="fileNameLabel"
         virtualName="" explicitFocusOrder="0" pos="856 415 136 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Filename&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <JUCERCOMP name="" id="59790b7b05875a88" memberName="cabIrUi" virtualName=""
             explicitFocusOrder="0" pos="696 445 300 24" sourceFile="UIIRSettings.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="2f7b8b080201fa1b" memberName="ampIrUi" virtualName=""
             explicitFocusOrder="0" pos="696 485 300 24" sourceFile="UIIRSettings.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="efb8e0bb8dcbdbb" memberName="preTube1Settings" virtualName=""
             explicitFocusOrder="0" pos="8 72 680 144" sourceFile="UITubeSettings.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="32b5cf72e47c155d" memberName="preTube2Settings" virtualName=""
             explicitFocusOrder="0" pos="8 221 680 144" sourceFile="UITubeSettings.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="85421bade1ef9019" memberName="powerAmpTubeSettings"
             virtualName="" explicitFocusOrder="0" pos="8 376 680 144" sourceFile="UITubeSettings.cpp"
             constructorParams=""/>
  <COMBOBOX name="new combo box" id="392db2e92c1aaa72" memberName="knobTypeComboBox"
            virtualName="" explicitFocusOrder="0" pos="184 32 150 24" editable="0"
            layout="33" items="chkn&#10;chknb&#10;dizl&#10;frmn&#10;mars&#10;marss&#10;mega&#10;recto&#10;rectob"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="2b53012dc5be6d37" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="176 0 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="KNOB type&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="a7d6e983b84d83c6" memberName="bgButton"
              virtualName="" explicitFocusOrder="0" pos="352 32 128 24" buttonText="Background image"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="76b35b380f318eb6" memberName="bgImageLabel"
         virtualName="" explicitFocusOrder="0" pos="488 32 192 24" edTextCol="ff000000"
         edBkgCol="0" labelText="From memory" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <JUCERCOMP name="" id="f05f02aebf7cb86b" memberName="bassEq" virtualName=""
             explicitFocusOrder="0" pos="8 535 768 40" sourceFile="UIEQSettings.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="7a92c9ed75d11d77" memberName="middleEq" virtualName=""
             explicitFocusOrder="0" pos="8 575 768 40" sourceFile="UIEQSettings.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="bbe19eb4320544a" memberName="component3" virtualName=""
             explicitFocusOrder="0" pos="8 614 768 40" sourceFile="UIEQSettings.cpp"
             constructorParams=""/>
  <JUCERCOMP name="" id="c1dae00a7f289494" memberName="trebleEq" virtualName=""
             explicitFocusOrder="0" pos="8 614 768 40" sourceFile="UIEQSettings.cpp"
             constructorParams=""/>
  <LABEL name="new label" id="9d9e191e697d9e82" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="808 136 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Max / Min" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="6a8160b611c40b4e" memberName="mMin2"
              virtualName="" explicitFocusOrder="0" pos="816 168 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="d2a810c2e62996e8" memberName="mMax2"
              virtualName="" explicitFocusOrder="0" pos="872 168 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="3857fe40619377d4" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="808 208 168 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Hornet Drive (0.0 - 1.0)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="6da8bc166af565b8" memberName="hornetDrive"
              virtualName="" explicitFocusOrder="0" pos="816 240 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="e83a6ccb98be6e9a" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="808 280 184 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Hornet Presence (0.0 - 1.0)&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="924bcf4c8fd15167" memberName="hornetPresence"
              virtualName="" explicitFocusOrder="0" pos="816 312 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <JUCERCOMP name="" id="4d5ec1ea5b478aaf" memberName="trebleEq2" virtualName=""
             explicitFocusOrder="0" pos="8 672 768 40" sourceFile="UIEQSettings.cpp"
             constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

