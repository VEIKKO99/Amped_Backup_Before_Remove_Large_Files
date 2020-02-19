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

#include <LicenceTools.h>
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
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (24, 8, 392, 80);

    label3.reset (new Label ("new label",
                             TRANS("THANKS FOR YOUR SUPPORT\n")));
    addAndMakeVisible (label3.get());
    label3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
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
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label4->setBounds (16, 144, 408, 48);

    licenceCodeLabel.reset (new Label ("new label",
                                       TRANS("THIS-ISNO-TVAL-IDRE-QUES-TKEY-ATAL-LLLL\n")));
    addAndMakeVisible (licenceCodeLabel.get());
    licenceCodeLabel->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    licenceCodeLabel->setJustificationType (Justification::centred);
    licenceCodeLabel->setEditable (false, false, false);
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
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label6->setBounds (16, 240, 408, 24);

    licenceCodeEditor.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (licenceCodeEditor.get());
    licenceCodeEditor->setMultiLine (false);
    licenceCodeEditor->setReturnKeyStartsNewLine (false);
    licenceCodeEditor->setReadOnly (false);
    licenceCodeEditor->setScrollbarsShown (true);
    licenceCodeEditor->setCaretVisible (true);
    licenceCodeEditor->setPopupMenuEnabled (true);
    licenceCodeEditor->setColour (TextEditor::backgroundColourId, Colour (0x00495358));
    licenceCodeEditor->setText (String());

    licenceCodeEditor->setBounds (16, 280, 408, 24);

    underline.reset (new Component());
    addAndMakeVisible (underline.get());
    underline->setName ("new component");

    underline->setBounds (8, 312, 416, 8);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (440, 600);


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

    label = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    licenceCodeLabel = nullptr;
    label5 = nullptr;
    label6 = nullptr;
    licenceCodeEditor = nullptr;
    underline = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LicenceDialog::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff111111));

    //[UserPaint] Add your own custom painting code here..

    g.setColour (Colours::white);

    g.fillRect (8, 312, 416, 4);

    //[/UserPaint]
}

void LicenceDialog::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void LicenceDialog::licenceCodeTextChanged()
{
    String enteredText = licenceCodeEditor->getText().trim();

    if (enteredText.length() == 39)
    {
        auto valid = LicenceTools::getInstance()->installLicense(enteredText);
        if (valid == true) {
            juce::Logger::getCurrentLogger()->writeToLog("Licence valid");
        }
        else {
            juce::Logger::getCurrentLogger()->writeToLog("Licence NOT valid");
        }
    }
    else {

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
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="440" initialHeight="600">
  <BACKGROUND backgroundColour="ff111111"/>
  <LABEL name="new label" id="246a4482c6a6df88" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="24 8 392 80" edTextCol="ff000000"
         edBkgCol="0" labelText="TO USE ALL AMPS YOU NEED TO LICENCE THIS PRODUCT ON ML SOUND LAB WEBSITE&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="36"/>
  <LABEL name="new label" id="a3b2c2af07986b11" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="16 88 408 24" edTextCol="ff000000"
         edBkgCol="0" labelText="THANKS FOR YOUR SUPPORT&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="bfeffc6138a9bb71" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="16 144 408 48" edTextCol="ff000000"
         edBkgCol="0" labelText="You need to copy the following request key &#10;and use it on ML Sound Lab Website.&#10;&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="36"/>
  <LABEL name="new label" id="4b4c2f291b8c77c9" memberName="licenceCodeLabel"
         virtualName="" explicitFocusOrder="0" pos="16 200 408 24" edTextCol="ff000000"
         edBkgCol="0" labelText="THIS-ISNO-TVAL-IDRE-QUES-TKEY-ATAL-LLLL&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="16.0" kerning="0.0" bold="0"
         italic="0" justification="36"/>
  <LABEL name="new label" id="8018b035e57f7b68" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="16 240 408 24" edTextCol="ff000000"
         edBkgCol="0" labelText="LICENCE KEY:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="937d91f38fdb0f13" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="16 240 408 24" edTextCol="ff000000"
         edBkgCol="0" labelText="LICENCE KEY:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <TEXTEDITOR name="new text editor" id="78ea782f5152046d" memberName="licenceCodeEditor"
              virtualName="" explicitFocusOrder="0" pos="16 280 408 24" bkgcol="495358"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="1" caret="1" popupmenu="1"/>
  <GENERICCOMPONENT name="new component" id="392d61405af05a04" memberName="underline"
                    virtualName="" explicitFocusOrder="0" pos="8 312 416 8" class="Component"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

