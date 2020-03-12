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

    licenceCodeLabel.reset (new Label ("new label",
                                       TRANS("THIS-ISNO-TVAL-IDRE-QUES-TKEY-ATAL-LLLL\n")));
    addAndMakeVisible (licenceCodeLabel.get());
    licenceCodeLabel->setFont (Font (13.00f, Font::plain).withTypefaceStyle ("Regular"));
    licenceCodeLabel->setJustificationType (Justification::centred);
    licenceCodeLabel->setEditable (false, false, false);
    licenceCodeLabel->setColour (Label::textColourId, Colour (0xfff2f2f2));
    licenceCodeLabel->setColour (TextEditor::textColourId, Colours::black);
    licenceCodeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    licenceCodeLabel->setBounds (384, 473, 336, 24);

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

    licenceCodeEditor->setBounds (376, 575, 336, 17);

    copyKeyBtn.reset (new TextButton ("new button"));
    addAndMakeVisible (copyKeyBtn.get());
    copyKeyBtn->setButtonText (TRANS("COPY REQUEST KEY"));
    copyKeyBtn->addListener (this);
    copyKeyBtn->setColour (TextButton::buttonColourId, Colour (0xff111111));
    copyKeyBtn->setColour (TextButton::textColourOffId, Colour (0xf2f2f2f2));

    copyKeyBtn->setBounds (728, 456, 160, 32);

    pasteLicenceBtn.reset (new TextButton ("new button"));
    addAndMakeVisible (pasteLicenceBtn.get());
    pasteLicenceBtn->setButtonText (TRANS("PASTE LICENCE KEY"));
    pasteLicenceBtn->addListener (this);
    pasteLicenceBtn->setColour (TextButton::buttonColourId, Colour (0xff111111));

    pasteLicenceBtn->setBounds (728, 552, 160, 32);

    buyLicenseBtn.reset (new TextButton ("new button"));
    addAndMakeVisible (buyLicenseBtn.get());
    buyLicenseBtn->setButtonText (TRANS("BUY LICENSE"));
    buyLicenseBtn->addListener (this);
    buyLicenseBtn->setColour (TextButton::buttonColourId, Colour (0xff111111));
    buyLicenseBtn->setColour (TextButton::textColourOffId, Colour (0xf2f2f2f2));

    buyLicenseBtn->setBounds (728, 504, 160, 32);

    hyperlinkButton.reset (new HyperlinkButton (TRANS("WWW:ML-SOUND-LAB.COM"),
                                                URL ("https://ml-sound-lab.com/")));
    addAndMakeVisible (hyperlinkButton.get());
    hyperlinkButton->setTooltip (TRANS("https://ml-sound-lab.com/"));
    hyperlinkButton->setButtonText (TRANS("WWW:ML-SOUND-LAB.COM"));
    hyperlinkButton->setColour (HyperlinkButton::textColourId, Colour (0xfff2f2f2));

    hyperlinkButton->setBounds (376, 525, 320, 20);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (1200, 600);


    //[Constructor] You can add your own custom stuff here..
    auto challenge = papupata::licensing::Challenge(true).toString();

    licenceCodeLabel->setText(challenge, dontSendNotification);
    licenceCodeEditor->onTextChange = [this] {licenceCodeTextChanged();};

    //[/Constructor]
}

LicenceDialog::~LicenceDialog()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    licenceCodeLabel = nullptr;
    licenceCodeEditor = nullptr;
    copyKeyBtn = nullptr;
    pasteLicenceBtn = nullptr;
    buyLicenseBtn = nullptr;
    hyperlinkButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LicenceDialog::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    Image background = ImageCache::getFromMemory (BinaryData::amped_license_background_png, BinaryData::amped_license_background_pngSize);
    g.drawImageAt (background, 0, 0);
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
    else if (buttonThatWasClicked == buyLicenseBtn.get())
    {
        //[UserButtonCode_buyLicenseBtn] -- add your button handler code here..
        URL("https://ml-sound-lab.com/").launchInDefaultBrowser();
        //[/UserButtonCode_buyLicenseBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void LicenceDialog::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    juce::Logger::getCurrentLogger()->writeToLog("Mouse Up");
    if (e.getPosition().getX() < 300 || e.getPosition().getX() > 900) {
        setVisible(false);
    }

    //[/UserCode_mouseUp]
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

void LicenceDialog::showLicenseValidDialog(String email, Component* parent) {
    NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "Thanks a lot!", "This product is licensed for " + email,
            parent);
}

void LicenceDialog::licenceCodeTextChanged()
{
    String enteredText = licenceCodeEditor->getText().trim();

    auto valid = LicenceTools::getInstance()->installLicense(enteredText);
    if (valid == true) {
        juce::Logger::getCurrentLogger()->writeToLog("Licence valid");
        auto licence = LicenceTools::getInstance()->getLicence();
        showLicenseValidDialog(licence->getUserEmail(), this);
        //NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "Thanks a lot!", "This product is licenced for " + licence->getUserEmail(),
         //       this);
        juce::Logger::getCurrentLogger()->writeToLog(licence->getUserEmail());
        juce::Logger::getCurrentLogger()->writeToLog(licence->getUserName());
        setVisible(false);
    }
    else {
        juce::Logger::getCurrentLogger()->writeToLog("Licence NOT valid");
        NativeMessageBox::showMessageBoxAsync(AlertWindow::InfoIcon, "Error", "Provided licence is not valid!",
                this);
    }

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
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="1200"
                 initialHeight="600">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="1a1a1a"/>
  <LABEL name="new label" id="4b4c2f291b8c77c9" memberName="licenceCodeLabel"
         virtualName="" explicitFocusOrder="0" pos="384 473 336 24" textCol="fff2f2f2"
         edTextCol="ff000000" edBkgCol="0" labelText="THIS-ISNO-TVAL-IDRE-QUES-TKEY-ATAL-LLLL&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="13.0" kerning="0.0" bold="0"
         italic="0" justification="36"/>
  <TEXTEDITOR name="new text editor" id="78ea782f5152046d" memberName="licenceCodeEditor"
              virtualName="" explicitFocusOrder="0" pos="376 575 336 17" tooltip="Paste your licence key here"
              textcol="fff2f2f2" bkgcol="495358" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="1" scrollbars="1" caret="0" popupmenu="1"/>
  <TEXTBUTTON name="new button" id="d4ece8f5f05b072" memberName="copyKeyBtn"
              virtualName="" explicitFocusOrder="0" pos="728 456 160 32" bgColOff="ff111111"
              textCol="f2f2f2f2" buttonText="COPY REQUEST KEY" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="473c5e2a3ec66319" memberName="pasteLicenceBtn"
              virtualName="" explicitFocusOrder="0" pos="728 552 160 32" bgColOff="ff111111"
              buttonText="PASTE LICENCE KEY" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="7e598643d2278332" memberName="buyLicenseBtn"
              virtualName="" explicitFocusOrder="0" pos="728 504 160 32" bgColOff="ff111111"
              textCol="f2f2f2f2" buttonText="BUY LICENSE" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <HYPERLINKBUTTON name="new hyperlink" id="90b7a907a43a1c13" memberName="hyperlinkButton"
                   virtualName="" explicitFocusOrder="0" pos="376 525 320 20" tooltip="https://ml-sound-lab.com/"
                   textCol="fff2f2f2" buttonText="WWW:ML-SOUND-LAB.COM" connectedEdges="0"
                   needsCallback="0" radioGroupId="0" url="https://ml-sound-lab.com/"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

