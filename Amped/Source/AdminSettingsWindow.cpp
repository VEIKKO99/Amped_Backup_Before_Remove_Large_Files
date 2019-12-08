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

    updateButton->setBounds (824, 584, 150, 24);

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

    inMin->setBounds (816, 48, 47, 24);

    inMax.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (inMax.get());
    inMax->setMultiLine (false);
    inMax->setReturnKeyStartsNewLine (false);
    inMax->setReadOnly (false);
    inMax->setScrollbarsShown (true);
    inMax->setCaretVisible (true);
    inMax->setPopupMenuEnabled (true);
    inMax->setText (String());

    inMax->setBounds (872, 48, 47, 24);

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
    preTube1Settings->setBounds (8, 128, 680, 145);

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

    label5.reset (new Label ("new label",
                             TRANS("Hornet Drive (0.0 - 1.0)")));
    addAndMakeVisible (label5.get());
    label5->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label5->setBounds (816, 240, 168, 24);

    hornetDrive.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (hornetDrive.get());
    hornetDrive->setMultiLine (false);
    hornetDrive->setReturnKeyStartsNewLine (false);
    hornetDrive->setReadOnly (false);
    hornetDrive->setScrollbarsShown (true);
    hornetDrive->setCaretVisible (true);
    hornetDrive->setPopupMenuEnabled (true);
    hornetDrive->setText (String());

    hornetDrive->setBounds (824, 272, 47, 24);

    label8.reset (new Label ("new label",
                             TRANS("Hornet Presence (0.0 - 1.0)\n")));
    addAndMakeVisible (label8.get());
    label8->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label8->setBounds (816, 312, 184, 24);

    hornetPresence.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (hornetPresence.get());
    hornetPresence->setMultiLine (false);
    hornetPresence->setReturnKeyStartsNewLine (false);
    hornetPresence->setReadOnly (false);
    hornetPresence->setScrollbarsShown (true);
    hornetPresence->setCaretVisible (true);
    hornetPresence->setPopupMenuEnabled (true);
    hornetPresence->setText (String());

    hornetPresence->setBounds (824, 344, 47, 24);

    presenceEq.reset (new UIEQSettings());
    addAndMakeVisible (presenceEq.get());
    presenceEq->setBounds (8, 672, 768, 40);

    updateButton2.reset (new TextButton ("new button"));
    addAndMakeVisible (updateButton2.get());
    updateButton2->setButtonText (TRANS("Save"));
    updateButton2->addListener (this);

    updateButton2->setBounds (824, 616, 150, 24);

    loadButton.reset (new TextButton ("new button"));
    addAndMakeVisible (loadButton.get());
    loadButton->setButtonText (TRANS("Load"));
    loadButton->addListener (this);

    loadButton->setBounds (824, 648, 150, 24);

    label9.reset (new Label ("new label",
                             TRANS("Input Max / Min\n"
                             "Dont Touch!")));
    addAndMakeVisible (label9.get());
    label9->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label9->setBounds (808, 16, 150, 24);

    driveMin.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (driveMin.get());
    driveMin->setMultiLine (false);
    driveMin->setReturnKeyStartsNewLine (false);
    driveMin->setReadOnly (false);
    driveMin->setScrollbarsShown (true);
    driveMin->setCaretVisible (true);
    driveMin->setPopupMenuEnabled (true);
    driveMin->setText (String());

    driveMin->setBounds (816, 108, 47, 24);

    driveMax.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (driveMax.get());
    driveMax->setMultiLine (false);
    driveMax->setReturnKeyStartsNewLine (false);
    driveMax->setReadOnly (false);
    driveMax->setScrollbarsShown (true);
    driveMax->setCaretVisible (true);
    driveMax->setPopupMenuEnabled (true);
    driveMax->setText (String());

    driveMax->setBounds (872, 108, 47, 24);

    label10.reset (new Label ("new label",
                              TRANS("Drive Max / Min")));
    addAndMakeVisible (label10.get());
    label10->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label10->setBounds (808, 76, 150, 24);

    overSampleLabel.reset (new Label ("new label",
                                      CharPointer_UTF8 ("\xc3\x96vers\xc3\xa4mple (Not Saved)\n"
                                      "1 / 2 / 4 / 8 / 16\n")));
    addAndMakeVisible (overSampleLabel.get());
    overSampleLabel->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    overSampleLabel->setJustificationType (Justification::centredLeft);
    overSampleLabel->setEditable (false, false, false);
    overSampleLabel->setColour (TextEditor::textColourId, Colours::black);
    overSampleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    overSampleLabel->setBounds (608, 32, 144, 24);

    overSample.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (overSample.get());
    overSample->setMultiLine (false);
    overSample->setReturnKeyStartsNewLine (false);
    overSample->setReadOnly (false);
    overSample->setScrollbarsShown (true);
    overSample->setCaretVisible (true);
    overSample->setPopupMenuEnabled (true);
    overSample->setText (String());

    overSample->setBounds (616, 64, 47, 24);

    amtPreAmpTubesLabel.reset (new Label ("new label",
                                          TRANS("Amount of Preamp tubes (1-4)")));
    addAndMakeVisible (amtPreAmpTubesLabel.get());
    amtPreAmpTubesLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    amtPreAmpTubesLabel->setJustificationType (Justification::centredLeft);
    amtPreAmpTubesLabel->setEditable (false, false, false);
    amtPreAmpTubesLabel->setColour (TextEditor::textColourId, Colours::black);
    amtPreAmpTubesLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    amtPreAmpTubesLabel->setBounds (8, 64, 216, 24);

    amountOfPreampTubes.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (amountOfPreampTubes.get());
    amountOfPreampTubes->setMultiLine (false);
    amountOfPreampTubes->setReturnKeyStartsNewLine (false);
    amountOfPreampTubes->setReadOnly (false);
    amountOfPreampTubes->setScrollbarsShown (true);
    amountOfPreampTubes->setCaretVisible (true);
    amountOfPreampTubes->setPopupMenuEnabled (true);
    amountOfPreampTubes->setText (String());

    amountOfPreampTubes->setBounds (16, 95, 47, 24);


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
    powerAmpTubeSettings = nullptr;
    knobTypeComboBox = nullptr;
    label7 = nullptr;
    bgButton = nullptr;
    bgImageLabel = nullptr;
    bassEq = nullptr;
    middleEq = nullptr;
    component3 = nullptr;
    trebleEq = nullptr;
    label5 = nullptr;
    hornetDrive = nullptr;
    label8 = nullptr;
    hornetPresence = nullptr;
    presenceEq = nullptr;
    updateButton2 = nullptr;
    loadButton = nullptr;
    label9 = nullptr;
    driveMin = nullptr;
    driveMax = nullptr;
    label10 = nullptr;
    overSampleLabel = nullptr;
    overSample = nullptr;
    amtPreAmpTubesLabel = nullptr;
    amountOfPreampTubes = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AdminSettingsWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff324144));

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
    else if (buttonThatWasClicked == updateButton2.get())
    {
        //[UserButtonCode_updateButton2] -- add your button handler code here..
        saveSettings();

        //[/UserButtonCode_updateButton2]
    }
    else if (buttonThatWasClicked == loadButton.get())
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
        loadSettings();
        //[/UserButtonCode_loadButton]
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

    // All pre amp tubes should hold the same settings.
    settings->ampSettings.amountOfPreAmpTubes = amountOfPreampTubes->getText().getIntValue();
    for (int i = 0; i < settings->ampSettings.amountOfPreAmpTubes; i++)
    {
        preTube1Settings->updateSettings(settings->ampSettings.preAmpTubes[i]);
    }
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
    settings->gainSettings[GainProcessorId::DriveGain].min = driveMin->getText().getFloatValue();
    settings->gainSettings[GainProcessorId::DriveGain].max = driveMax->getText().getFloatValue();

    settings->ampSettings.hornetPresence = hornetPresence->getText().getFloatValue();
    settings->ampSettings.hornetDrive = hornetDrive->getText().getFloatValue();
    settings->ampSettings.overSample = overSample->getText().getIntValue();

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
    this->driveMax->setText(String(settings->gainSettings[GainProcessorId::DriveGain].max), dontSendNotification);
    this->driveMin->setText(String(settings->gainSettings[GainProcessorId::DriveGain].min), dontSendNotification);

    // this->eqGain->setText(String(settings->ampSettings.eqGain));

    this->preTube1Settings->setupUI(settings->ampSettings.preAmpTubes[0],"All preamp tube settings");
   // this->preTube2Settings->setupUI(settings->ampSettings.preAmpTubes[1],"Pre Amp Tube 2");
    this->powerAmpTubeSettings->setupUI(settings->ampSettings.powerAmpTube, "Power Amp Tube");
    this->amountOfPreampTubes->setText(String(settings->ampSettings.amountOfPreAmpTubes));
    this->cabIrUi->setupUI(settings->ampSettings.cabIr,"Cab IR");
    this->ampIrUi->setupUI(settings->ampSettings.ampIr,"AMP IR");

    this->knobTypeComboBox->setSelectedItemIndex(settings->uiSettings.selectedKnob, dontSendNotification);
    this->bassEq->setupUI(settings->ampSettings.eqs[kBassEq], "Bass Eq");
    this->middleEq->setupUI(settings->ampSettings.eqs[kMiddleEq], "Middle Eq");
    this->trebleEq->setupUI(settings->ampSettings.eqs[kTrebleEq], "Treble Eq");
    this->presenceEq->setupUI(settings->ampSettings.eqs[kPresence], "Presence");

    this->hornetDrive->setText(String(settings->ampSettings.hornetDrive), dontSendNotification);
    this->hornetPresence->setText(String(settings->ampSettings.hornetPresence), dontSendNotification);

    this->overSample->setText(String(settings->ampSettings.overSample));

    //this->cabIrGain->setText(String(settings->ampSettings.cabIr.gain), dontSendNotification);
    //this->ampIrGain->setText(String(settings->ampSettings.ampIr.gain), dontSendNotification);
    //if (settings->ampSettings.ampIr.irFileName.length() > 0)
    //    ampIrLabel->setText(settings->ampSettings.ampIr.irFileName, dontSendNotification);
    //if (settings->ampSettings.cabIr.irFileName.length() > 0)
    //    cabIrLabel->setText(settings->ampSettings.cabIr.irFileName, dontSendNotification);

}

void AdminSettingsWindow::saveSettings() {
    updateSettings();
    auto settings = changeInterface->getCurrentSettings();
    auto xml = settings->serializeToXml();
    Logger::getCurrentLogger()->writeToLog(xml->toString());

    FileChooser myChooser ("Save sound settings to empty directory.",
            File::getSpecialLocation (File::userHomeDirectory),
                "*.apd");
    if (myChooser.browseForFileToSave(true))
    {
        File saveFile (myChooser.getResult());
        xml->writeTo(saveFile);

        String filesDirectoryString = saveFile.getParentDirectory().getFullPathName() + File::getSeparatorString()  + "files";
        Logger::getCurrentLogger()->writeToLog(filesDirectoryString);

        String withTrailingSeparator = File::addTrailingSeparator(filesDirectoryString);
        Logger::getCurrentLogger()->writeToLog(withTrailingSeparator);

        File files(withTrailingSeparator);
        if (files.createDirectory().wasOk()) {
            settings->uiSettings.mainBackgroundImageFileName = copyFile(withTrailingSeparator, settings->uiSettings.mainBackgroundImageFileName);
            settings->ampSettings.cabIr.irFileName = copyFile(withTrailingSeparator, settings->ampSettings.cabIr.irFileName);
            settings->ampSettings.ampIr.irFileName = copyFile(withTrailingSeparator, settings->ampSettings.ampIr.irFileName);

            for (int i = 0; i < EQType::kEQSize; i++) {
                settings->ampSettings.eqs[i].lowIrFileName = copyFile(withTrailingSeparator,  settings->ampSettings.eqs[i].lowIrFileName);
                settings->ampSettings.eqs[i].highIrFileName = copyFile(withTrailingSeparator,  settings->ampSettings.eqs[i].highIrFileName);
            }
        }
        else {
            showAlert("Cannot create files directory");
        }
    }
}

void AdminSettingsWindow::loadSettings() {
    FileChooser myChooser ("Load sound settings .",
            File::getSpecialLocation (File::userHomeDirectory),
            "*.apd");

    if (myChooser.browseForFileToOpen()) {
        File settingsFile =  myChooser.getResult();

        XmlDocument xmlDocument(settingsFile);
        auto xmlElement = xmlDocument.getDocumentElement();
        auto settings = changeInterface->getCurrentSettings();
        settings->readFromXml(xmlElement.get(), settingsFile.getParentDirectory().getFullPathName() + File::getSeparatorString() + "files" +  File::getSeparatorString());
        setupUI();
        changeInterface->settingChanged();
    }
}

void AdminSettingsWindow::showAlert(String message) {
    NativeMessageBox::showMessageBox(AlertWindow::AlertIconType::WarningIcon,
            "Error", message, this);
}

String AdminSettingsWindow::copyFile(String destDirectory, String originalFile) {
    File original(originalFile);
    String destFullName = destDirectory + original.getFileName();
    File destination(destFullName);
    if (!original.copyFileTo(destination)){
        showAlert("Error copying file: " + original.getFileName());
    }
    return destFullName;
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
  <BACKGROUND backgroundColour="ff324144"/>
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
              virtualName="" explicitFocusOrder="0" pos="824 584 150 24" buttonText="Update"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="ea8a683340dc7a41" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="808 136 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Output Max / Min" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="8e867a582e3c87dd" memberName="inMin"
              virtualName="" explicitFocusOrder="0" pos="816 48 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="bf18a407ae51f5ef" memberName="inMax"
              virtualName="" explicitFocusOrder="0" pos="872 48 47 24" initialText=""
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
             explicitFocusOrder="0" pos="8 128 680 145" sourceFile="UITubeSettings.cpp"
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
  <LABEL name="new label" id="3857fe40619377d4" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="816 240 168 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Hornet Drive (0.0 - 1.0)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="6da8bc166af565b8" memberName="hornetDrive"
              virtualName="" explicitFocusOrder="0" pos="824 272 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="e83a6ccb98be6e9a" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="816 312 184 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Hornet Presence (0.0 - 1.0)&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="924bcf4c8fd15167" memberName="hornetPresence"
              virtualName="" explicitFocusOrder="0" pos="824 344 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <JUCERCOMP name="" id="4d5ec1ea5b478aaf" memberName="presenceEq" virtualName=""
             explicitFocusOrder="0" pos="8 672 768 40" sourceFile="UIEQSettings.cpp"
             constructorParams=""/>
  <TEXTBUTTON name="new button" id="54f521d0b77f3c71" memberName="updateButton2"
              virtualName="" explicitFocusOrder="0" pos="824 616 150 24" buttonText="Save"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="5f7cd414ef4bc0e9" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="824 648 150 24" buttonText="Load"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="ea33da321f3a70e2" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="808 16 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Max / Min&#10;Dont Touch!" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="3e8959223324712" memberName="driveMin"
              virtualName="" explicitFocusOrder="0" pos="816 108 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <TEXTEDITOR name="new text editor" id="6003f14ffc6e1178" memberName="driveMax"
              virtualName="" explicitFocusOrder="0" pos="872 108 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="3eec3084a6030705" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="808 76 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Drive Max / Min" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d7d196c447ee454c" memberName="overSampleLabel"
         virtualName="" explicitFocusOrder="0" pos="608 32 144 24" edTextCol="ff000000"
         edBkgCol="0" labelText="&#214;vers&#228;mple (Not Saved)&#10;1 / 2 / 4 / 8 / 16&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="7681e36da5ce556c" memberName="overSample"
              virtualName="" explicitFocusOrder="0" pos="616 64 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="4fcc49e204792f0a" memberName="amtPreAmpTubesLabel"
         virtualName="" explicitFocusOrder="0" pos="8 64 216 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amount of Preamp tubes (1-4)" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="550e03298bf4de1d" memberName="amountOfPreampTubes"
              virtualName="" explicitFocusOrder="0" pos="16 95 47 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

