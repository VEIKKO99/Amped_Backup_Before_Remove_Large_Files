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
#include <LicenceTools.h>

//[/Headers]

#include "LicenceDialog.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
LicenceDialog::LicenceDialog ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    label.reset (new Label ("new label",
                            TRANS("TO USE ALL AMPS YOU NEED TO LICENCE THIS PRODUCT ON ML SOUND LAB WEBSITE\n")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (Label::textColourId, Colour (0xfff2f2f2));
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (24, 8, 392, 80);

    label3.reset (new Label ("new label",
                             TRANS("THANKS FOR YOUR SUPPORT\n")));
    addAndMakeVisible (label3.get());
    label3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colour (0xfff2f2f2));
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label3->setBounds (16, 88, 408, 24);

    label4.reset (new Label ("new label",
                             TRANS("You need to copy the following request key \n"
                             "and use it on ML Sound Lab Website.\n"
                             "\n")));
    addAndMakeVisible (label4.get());
    label4->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label4->setJustificationType (Justification::centred);
    label4->setEditable (false, false, false);
    label4->setColour (Label::textColourId, Colour (0xfff2f2f2));
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label4->setBounds (16, 144, 408, 48);

    licenceCodeLabel.reset (new Label ("new label",
                                       TRANS("THIS-ISNO-TVAL-IDRE-QUES-TKEY-ATAL-LLLL\n")));
    addAndMakeVisible (licenceCodeLabel.get());
    licenceCodeLabel->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    licenceCodeLabel->setJustificationType (Justification::centred);
    licenceCodeLabel->setEditable (false, false, false);
    licenceCodeLabel->setColour (Label::textColourId, Colour (0xfff2f2f2));
    licenceCodeLabel->setColour (TextEditor::textColourId, Colours::black);
    licenceCodeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    licenceCodeLabel->setBounds (16, 200, 408, 24);

    label5.reset (new Label ("new label",
                             TRANS("LICENCE KEY:\n")));
    addAndMakeVisible (label5.get());
    label5->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    label5->setJustificationType (Justification::centred);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label5->setBounds (16, 240, 408, 24);

    label6.reset (new Label ("new label",
                             TRANS("LICENCE KEY:\n")));
    addAndMakeVisible (label6.get());
    label6->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    label6->setJustificationType (Justification::centred);
    label6->setEditable (false, false, false);
    label6->setColour (Label::textColourId, Colour (0xfff2f2f2));
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label6->setBounds (16, 240, 408, 24);

    licenceCodeEditor.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (licenceCodeEditor.get());
    licenceCodeEditor->setTooltip (TRANS("Paste your licence key here"));
    licenceCodeEditor->setMultiLine (false);
    licenceCodeEditor->setReturnKeyStartsNewLine (false);
    licenceCodeEditor->setReadOnly (true);
    licenceCodeEditor->setScrollbarsShown (true);
    licenceCodeEditor->setCaretVisible (false);
    licenceCodeEditor->setPopupMenuEnabled (true);
    licenceCodeEditor->setColour (TextEditor::textColourId, Colour (0xfff2f2f2));
    licenceCodeEditor->setColour (TextEditor::backgroundColourId, Colour (0x00495358));
    licenceCodeEditor->setText (String());

    licenceCodeEditor->setBounds (16, 280, 408, 24);

    copyKeyBtn.reset (new TextButton ("new button"));
    addAndMakeVisible (copyKeyBtn.get());
    copyKeyBtn->setButtonText (TRANS("COPY REQUEST KEY"));
    copyKeyBtn->addListener (this);
    copyKeyBtn->setColour (TextButton::buttonColourId, Colour (0xff111111));
    copyKeyBtn->setColour (TextButton::textColourOffId, Colour (0xf2f2f2f2));

    copyKeyBtn->setBounds (56, 320, 140, 35);

    pasteLicenceBtn.reset (new TextButton ("new button"));
    addAndMakeVisible (pasteLicenceBtn.get());
    pasteLicenceBtn->setButtonText (TRANS("PASTE LICENCE KEY"));
    pasteLicenceBtn->addListener (this);
    pasteLicenceBtn->setColour (TextButton::buttonColourId, Colour (0xff111111));

    pasteLicenceBtn->setBounds (232, 320, 140, 35);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (440, 600);


    //[Constructor] You can add your own custom stuff here..
    auto challenge = papupata::licensing::Challenge(true).toString();
    juce::Logger::getCurrentLogger()->writeToLog("challenge1:" + challenge);

    auto challenge2 = papupata::licensing::Challenge(true).toString();
    juce::Logger::getCurrentLogger()->writeToLog("challenge2:" + challenge2);

    auto challenge3 = papupata::licensing::Challenge(true).toString();
    juce::Logger::getCurrentLogger()->writeToLog("challenge3:" + challenge3);

    licenceCodeLabel->setText(challenge, dontSendNotification);
    licenceCodeEditor->onTextChange = [this] {licenceCodeTextChanged();};

    auto challenge4 = papupata::licensing::Challenge(true).toString();
    juce::Logger::getCurrentLogger()->writeToLog("challenge4:" + challenge4);

    Component::SafePointer<LicenceDialog> dialog(this);
    Timer::callAfterDelay(3000, [dialog, this]()
    {
        if (dialog != nullptr)
        {
            auto challenge5 = papupata::licensing::Challenge(true).toString();
            juce::Logger::getCurrentLogger()->writeToLog("After Timer: challenge5:" + challenge5);
        };
    });
    //[/Constructor]
}

LicenceDialog::~LicenceDialog()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    licenceCodeLabel = nullptr;
    label5 = nullptr;
    label6 = nullptr;
    licenceCodeEditor = nullptr;
    copyKeyBtn = nullptr;
    pasteLicenceBtn = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LicenceDialog::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1a1a1a));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void LicenceDialog::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LicenceDialog::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == copyKeyBtn.get())
    {
        //[UserButtonCode_copyKeyBtn] -- add your button handler code here..
        SystemClipboard::copyTextToClipboard(papupata::licensing::Challenge(true).toString());
        //[/UserButtonCode_copyKeyBtn]
    }
    else if (buttonThatWasClicked == pasteLicenceBtn.get())
    {
        //[UserButtonCode_pasteLicenceBtn] -- add your button handler code here..
        auto licenceCode = SystemClipboard::getTextFromClipboard();
        licenceCodeEditor->setText(licenceCode, true);
        //[/UserButtonCode_pasteLicenceBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

bool LicenceDialog::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    juce::Logger::getCurrentLogger()->writeToLog("Key Pressed");

    if (key.getKeyCode() == key.escapeKey) {
        this->setVisible(false);
        return true;
    }
    return false;
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void LicenceDialog::modalStateFinished(int returnValue) {
    setVisible(false);
}

void LicenceDialog::licenceCodeTextChanged()
{
    String enteredText = licenceCodeEditor->getText().trim();

    //if (enteredText.length() == 39)
    {
        auto valid = LicenceTools::getInstance()->installLicense(enteredText);
        if (valid == true) {
            juce::Logger::getCurrentLogger()->writeToLog("Licence valid");
            auto licence = LicenceTools::getInstance()->getLicence();
            NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "Thanks a lot!", "This product is licenced for " + licence->getUserEmail(),
                    this);
            juce::Logger::getCurrentLogger()->writeToLog(licence->getUserEmail());
            juce::Logger::getCurrentLogger()->writeToLog(licence->getUserName());
            setVisible(false);
        }
        else {
            juce::Logger::getCurrentLogger()->writeToLog("Licence NOT valid");
        }
    }
    //else {

    //}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="LicenceDialog" componentName=""
                 parentClasses="public Component, ModalComponentManager::Callback"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="440"
                 initialHeight="600">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ff1a1a1a"/>
  <LABEL name="new label" id="246a4482c6a6df88" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="24 8 392 80" textCol="fff2f2f2" edTextCol="ff000000"
         edBkgCol="0" labelText="TO USE ALL AMPS YOU NEED TO LICENCE THIS PRODUCT ON ML SOUND LAB WEBSITE&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="36"/>
  <LABEL name="new label" id="a3b2c2af07986b11" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="16 88 408 24" textCol="fff2f2f2"
         edTextCol="ff000000" edBkgCol="0" labelText="THANKS FOR YOUR SUPPORT&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="36"/>
  <LABEL name="new label" id="bfeffc6138a9bb71" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="16 144 408 48" textCol="fff2f2f2"
         edTextCol="ff000000" edBkgCol="0" labelText="You need to copy the following request key &#10;and use it on ML Sound Lab Website.&#10;&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="36"/>
  <LABEL name="new label" id="4b4c2f291b8c77c9" memberName="licenceCodeLabel"
         virtualName="" explicitFocusOrder="0" pos="16 200 408 24" textCol="fff2f2f2"
         edTextCol="ff000000" edBkgCol="0" labelText="THIS-ISNO-TVAL-IDRE-QUES-TKEY-ATAL-LLLL&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="16.0" kerning="0.0" bold="0"
         italic="0" justification="36"/>
  <LABEL name="new label" id="8018b035e57f7b68" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="16 240 408 24" edTextCol="ff000000"
         edBkgCol="0" labelText="LICENCE KEY:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="937d91f38fdb0f13" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="16 240 408 24" textCol="fff2f2f2"
         edTextCol="ff000000" edBkgCol="0" labelText="LICENCE KEY:&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="16.0" kerning="0.0" bold="0"
         italic="0" justification="36"/>
  <TEXTEDITOR name="new text editor" id="78ea782f5152046d" memberName="licenceCodeEditor"
              virtualName="" explicitFocusOrder="0" pos="16 280 408 24" tooltip="Paste your licence key here"
              textcol="fff2f2f2" bkgcol="495358" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="d4ece8f5f05b072" memberName="copyKeyBtn"
              virtualName="" explicitFocusOrder="0" pos="56 320 140 35" bgColOff="ff111111"
              textCol="f2f2f2f2" buttonText="COPY REQUEST KEY" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="473c5e2a3ec66319" memberName="pasteLicenceBtn"
              virtualName="" explicitFocusOrder="0" pos="232 320 140 35" bgColOff="ff111111"
              buttonText="PASTE LICENCE KEY" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

