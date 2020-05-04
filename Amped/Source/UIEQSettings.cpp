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

#include "UIEQSettings.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
UIEQSettings::UIEQSettings ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    lowPotBtn.reset (new TextButton ("new button"));
    addAndMakeVisible (lowPotBtn.get());
    lowPotBtn->setButtonText (TRANS("Low Pot IR"));
    lowPotBtn->addListener (this);

    lowPotBtn->setBounds (80, 0, 80, 24);

    lowPotIrNameLabel.reset (new Label ("new label",
                                        TRANS("Default (from memory)\n")));
    addAndMakeVisible (lowPotIrNameLabel.get());
    lowPotIrNameLabel->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    lowPotIrNameLabel->setJustificationType (Justification::centredLeft);
    lowPotIrNameLabel->setEditable (false, false, false);
    lowPotIrNameLabel->setColour (TextEditor::textColourId, Colours::black);
    lowPotIrNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lowPotIrNameLabel->setBounds (168, 0, 124, 24);

    irGain.reset (new TextEditor ("cabSimGain"));
    addAndMakeVisible (irGain.get());
    irGain->setMultiLine (false);
    irGain->setReturnKeyStartsNewLine (false);
    irGain->setReadOnly (false);
    irGain->setScrollbarsShown (true);
    irGain->setCaretVisible (true);
    irGain->setPopupMenuEnabled (true);
    irGain->setText (String());

    irGain->setBounds (584, 0, 47, 24);

    eqName.reset (new Label ("new label",
                             TRANS("EQ Name")));
    addAndMakeVisible (eqName.get());
    eqName->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    eqName->setJustificationType (Justification::centredLeft);
    eqName->setEditable (false, false, false);
    eqName->setColour (TextEditor::textColourId, Colours::black);
    eqName->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    eqName->setBounds (0, 0, 80, 24);

    highPotBtn.reset (new TextButton ("new button"));
    addAndMakeVisible (highPotBtn.get());
    highPotBtn->setButtonText (TRANS("High Pot IR"));
    highPotBtn->addListener (this);

    highPotBtn->setBounds (296, 0, 88, 24);

    highPotIrNameLabel.reset (new Label ("new label",
                                         TRANS("Default (from memory)\n")));
    addAndMakeVisible (highPotIrNameLabel.get());
    highPotIrNameLabel->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    highPotIrNameLabel->setJustificationType (Justification::centredLeft);
    highPotIrNameLabel->setEditable (false, false, false);
    highPotIrNameLabel->setColour (TextEditor::textColourId, Colours::black);
    highPotIrNameLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    highPotIrNameLabel->setBounds (392, 0, 146, 24);

    irgainLabel.reset (new Label ("new label",
                                  TRANS("IR\n"
                                  "Gain")));
    addAndMakeVisible (irgainLabel.get());
    irgainLabel->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    irgainLabel->setJustificationType (Justification::centredRight);
    irgainLabel->setEditable (false, false, false);
    irgainLabel->setColour (TextEditor::textColourId, Colours::black);
    irgainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    irgainLabel->setBounds (544, 0, 36, 24);

    realisticGain.reset (new TextEditor ("cabSimGain"));
    addAndMakeVisible (realisticGain.get());
    realisticGain->setMultiLine (false);
    realisticGain->setReturnKeyStartsNewLine (false);
    realisticGain->setReadOnly (false);
    realisticGain->setScrollbarsShown (true);
    realisticGain->setCaretVisible (true);
    realisticGain->setPopupMenuEnabled (true);
    realisticGain->setText (String());

    realisticGain->setBounds (696, 0, 63, 24);

    irgainLabel2.reset (new Label ("new label",
                                   TRANS("Realistic\n"
                                   "Gain")));
    addAndMakeVisible (irgainLabel2.get());
    irgainLabel2->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    irgainLabel2->setJustificationType (Justification::centredRight);
    irgainLabel2->setEditable (false, false, false);
    irgainLabel2->setColour (TextEditor::textColourId, Colours::black);
    irgainLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    irgainLabel2->setBounds (640, 0, 56, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 40);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

UIEQSettings::~UIEQSettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    lowPotBtn = nullptr;
    lowPotIrNameLabel = nullptr;
    irGain = nullptr;
    eqName = nullptr;
    highPotBtn = nullptr;
    highPotIrNameLabel = nullptr;
    irgainLabel = nullptr;
    realisticGain = nullptr;
    irgainLabel2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UIEQSettings::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UIEQSettings::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void UIEQSettings::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == lowPotBtn.get())
    {
        //[UserButtonCode_lowPotBtn] -- add your button handler code here..
        FileChooser myChooser ("Please select the IR file.",
                File::getSpecialLocation (File::userHomeDirectory),
                "*.wav");
        if (myChooser.browseForFileToOpen())
        {
            File irFile (myChooser.getResult());
            lowPotIrNameLabel->setText(irFile.getFileName(), dontSendNotification);
            selectedLowIRFileName = irFile.getFullPathName();
        }
        //[/UserButtonCode_lowPotBtn]
    }
    else if (buttonThatWasClicked == highPotBtn.get())
    {
        //[UserButtonCode_highPotBtn] -- add your button handler code here..
        FileChooser myChooser ("Please select the IR file.",
                File::getSpecialLocation (File::userHomeDirectory),
                "*.wav");
        if (myChooser.browseForFileToOpen())
        {
            File irFile (myChooser.getResult());
            highPotIrNameLabel->setText(irFile.getFileName(), dontSendNotification);
            selectedHighIRFileName = irFile.getFullPathName();
        }
        //[/UserButtonCode_highPotBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void UIEQSettings::setupUI(EQSettings& settings, String tubeName) {
    eqName->setText(tubeName, dontSendNotification);
    irGain->setText(String(settings.gain), false);
    realisticGain->setText(String(settings.realisticGain), false);
    if (settings.lowIrFileName.length() > 0) {
        lowPotIrNameLabel->setText(settings.lowIrFileName, dontSendNotification);
    }
    if (settings.highIrFileName.length() > 0) {
        highPotIrNameLabel->setText(settings.highIrFileName, dontSendNotification);
    }
}

void UIEQSettings::updateSettings(EQSettings& settings) {
    if (selectedHighIRFileName.length() > 0) {
        settings.highIrFileName = selectedHighIRFileName;
    }
    if (selectedLowIRFileName.length() > 0) {
        settings.lowIrFileName = selectedLowIRFileName;
    }
    settings.realisticGain = realisticGain->getText().getFloatValue();
    settings.gain = irGain->getText().getFloatValue();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UIEQSettings" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="800" initialHeight="40">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="new button" id="9efe025fec7486c4" memberName="lowPotBtn"
              virtualName="" explicitFocusOrder="0" pos="80 0 80 24" buttonText="Low Pot IR"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="119f4b72245d948e" memberName="lowPotIrNameLabel"
         virtualName="" explicitFocusOrder="0" pos="168 0 124 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Default (from memory)&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="cabSimGain" id="bdf3c9eff0364d86" memberName="irGain" virtualName=""
              explicitFocusOrder="0" pos="584 0 47 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
  <LABEL name="new label" id="974a79e2ee9f8dfa" memberName="eqName" virtualName=""
         explicitFocusOrder="0" pos="0 0 80 24" edTextCol="ff000000" edBkgCol="0"
         labelText="EQ Name" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="8357a76bc6329f0d" memberName="highPotBtn"
              virtualName="" explicitFocusOrder="0" pos="296 0 88 24" buttonText="High Pot IR"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="4ffb3b8afe79c15a" memberName="highPotIrNameLabel"
         virtualName="" explicitFocusOrder="0" pos="392 0 146 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Default (from memory)&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a983b873cea0c0c2" memberName="irgainLabel"
         virtualName="" explicitFocusOrder="0" pos="544 0 36 24" edTextCol="ff000000"
         edBkgCol="0" labelText="IR&#10;Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12.0" kerning="0.0" bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="cabSimGain" id="d12b9578ab38b2d2" memberName="realisticGain"
              virtualName="" explicitFocusOrder="0" pos="696 0 63 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="dd6b90d246f00224" memberName="irgainLabel2"
         virtualName="" explicitFocusOrder="0" pos="640 0 56 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Realistic&#10;Gain" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="12.0" kerning="0.0" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

