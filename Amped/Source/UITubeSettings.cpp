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
#include "AdminSettingsUtil.h"
//[/Headers]

#include "UITubeSettings.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
UITubeSettings::UITubeSettings ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    preTube1.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (preTube1.get());
    preTube1->setEditableText (false);
    preTube1->setJustificationType (Justification::centredLeft);
    preTube1->setTextWhenNothingSelected (String());
    preTube1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    preTube1->addItem (TRANS("12AX7_68k"), 1);
    preTube1->addItem (TRANS("12AX7_250k"), 2);
    preTube1->addItem (TRANS("12AY7_68k"), 3);
    preTube1->addItem (TRANS("12AY7_250k"), 4);
    preTube1->addItem (TRANS("12AT7_68k"), 5);
    preTube1->addItem (TRANS("12AT7_250k"), 6);
    preTube1->addItem (TRANS("ECC83_68k"), 7);
    preTube1->addItem (TRANS("ECC83_250k"), 8);
    preTube1->addItem (TRANS("ECC81_68k"), 9);
    preTube1->addItem (TRANS("ECC81_250k"), 10);
    preTube1->addItem (TRANS("7025_68k"), 11);
    preTube1->addItem (TRANS("7025_250k"), 12);
    preTube1->addItem (TRANS("6L6CG_68k"), 13);
    preTube1->addItem (TRANS("6L6CG_250k"), 14);
    preTube1->addItem (TRANS("EL34_68k"), 15);
    preTube1->addItem (TRANS("EL34_250k"), 16);
    preTube1->addItem (TRANS("EL84_68k"), 17);
    preTube1->addItem (TRANS("EL84_250k"), 18);
    preTube1->addItem (TRANS("6550_68k"), 19);
    preTube1->addItem (TRANS("6550_250k"), 20);
    preTube1->addItem (TRANS("KT88_68k"), 21);
    preTube1->addItem (TRANS("KT88_250k"), 22);
    preTube1->addItem (TRANS("KT66_68k"), 23);
    preTube1->addItem (TRANS("KT66_250k"), 24);
    preTube1->addListener (this);

    preTube1->setBounds (8, 32, 150, 24);

    label2.reset (new Label ("new label",
                             TRANS("Pre Tube 1\n")));
    addAndMakeVisible (label2.get());
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label2->setBounds (0, 0, 150, 24);

    preTube1RK.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (preTube1RK.get());
    preTube1RK->setMultiLine (false);
    preTube1RK->setReturnKeyStartsNewLine (false);
    preTube1RK->setReadOnly (false);
    preTube1RK->setScrollbarsShown (true);
    preTube1RK->setCaretVisible (true);
    preTube1RK->setPopupMenuEnabled (true);
    preTube1RK->setText (String());

    preTube1RK->setBounds (176, 32, 150, 24);

    rkLabel.reset (new Label ("new label",
                              TRANS("RK\n")));
    addAndMakeVisible (rkLabel.get());
    rkLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    rkLabel->setJustificationType (Justification::centredLeft);
    rkLabel->setEditable (false, false, false);
    rkLabel->setColour (TextEditor::textColourId, Colours::black);
    rkLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    rkLabel->setBounds (168, 0, 150, 24);

    preTube1RP.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (preTube1RP.get());
    preTube1RP->setMultiLine (false);
    preTube1RP->setReturnKeyStartsNewLine (false);
    preTube1RP->setReadOnly (false);
    preTube1RP->setScrollbarsShown (true);
    preTube1RP->setCaretVisible (true);
    preTube1RP->setPopupMenuEnabled (true);
    preTube1RP->setText (String());

    preTube1RP->setBounds (344, 32, 150, 24);

    rpLabel.reset (new Label ("new label",
                              TRANS("RP\n")));
    addAndMakeVisible (rpLabel.get());
    rpLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    rpLabel->setJustificationType (Justification::centredLeft);
    rpLabel->setEditable (false, false, false);
    rpLabel->setColour (TextEditor::textColourId, Colours::black);
    rpLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    rpLabel->setBounds (336, 0, 150, 24);

    preTube1VK0.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (preTube1VK0.get());
    preTube1VK0->setMultiLine (false);
    preTube1VK0->setReturnKeyStartsNewLine (false);
    preTube1VK0->setReadOnly (false);
    preTube1VK0->setScrollbarsShown (true);
    preTube1VK0->setCaretVisible (true);
    preTube1VK0->setPopupMenuEnabled (true);
    preTube1VK0->setText (String());

    preTube1VK0->setBounds (512, 32, 150, 24);

    vK0Label.reset (new Label ("new label",
                               TRANS("VK0\n")));
    addAndMakeVisible (vK0Label.get());
    vK0Label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    vK0Label->setJustificationType (Justification::centredLeft);
    vK0Label->setEditable (false, false, false);
    vK0Label->setColour (TextEditor::textColourId, Colours::black);
    vK0Label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    vK0Label->setBounds (504, 0, 150, 24);

    preTube1LowPassFbk.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (preTube1LowPassFbk.get());
    preTube1LowPassFbk->setMultiLine (false);
    preTube1LowPassFbk->setReturnKeyStartsNewLine (false);
    preTube1LowPassFbk->setReadOnly (false);
    preTube1LowPassFbk->setScrollbarsShown (true);
    preTube1LowPassFbk->setCaretVisible (true);
    preTube1LowPassFbk->setPopupMenuEnabled (true);
    preTube1LowPassFbk->setText (String());

    preTube1LowPassFbk->setBounds (176, 104, 150, 24);

    lowPassLabel.reset (new Label ("new label",
                                   TRANS("LowPassFbk\n")));
    addAndMakeVisible (lowPassLabel.get());
    lowPassLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lowPassLabel->setJustificationType (Justification::centredLeft);
    lowPassLabel->setEditable (false, false, false);
    lowPassLabel->setColour (TextEditor::textColourId, Colours::black);
    lowPassLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    lowPassLabel->setBounds (168, 72, 150, 24);

    preTube1VPlus.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (preTube1VPlus.get());
    preTube1VPlus->setMultiLine (false);
    preTube1VPlus->setReturnKeyStartsNewLine (false);
    preTube1VPlus->setReadOnly (false);
    preTube1VPlus->setScrollbarsShown (true);
    preTube1VPlus->setCaretVisible (true);
    preTube1VPlus->setPopupMenuEnabled (true);
    preTube1VPlus->setText (String());

    preTube1VPlus->setBounds (344, 104, 150, 24);

    vPlusLabel.reset (new Label ("new label",
                                 TRANS("VPlus\n")));
    addAndMakeVisible (vPlusLabel.get());
    vPlusLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    vPlusLabel->setJustificationType (Justification::centredLeft);
    vPlusLabel->setEditable (false, false, false);
    vPlusLabel->setColour (TextEditor::textColourId, Colours::black);
    vPlusLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    vPlusLabel->setBounds (336, 72, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (680, 140);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

UITubeSettings::~UITubeSettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    preTube1 = nullptr;
    label2 = nullptr;
    preTube1RK = nullptr;
    rkLabel = nullptr;
    preTube1RP = nullptr;
    rpLabel = nullptr;
    preTube1VK0 = nullptr;
    vK0Label = nullptr;
    preTube1LowPassFbk = nullptr;
    lowPassLabel = nullptr;
    preTube1VPlus = nullptr;
    vPlusLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UITubeSettings::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UITubeSettings::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void UITubeSettings::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == preTube1.get())
    {
        //[UserComboBoxCode_preTube1] -- add your combo box handling code here..
        //[/UserComboBoxCode_preTube1]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void UITubeSettings::setupUI(TubeSettings& settings, String tubeName) {
    label2->setText(tubeName, dontSendNotification);
    preTube1->setSelectedItemIndex(settings.tubeType, dontSendNotification);
    preTube1RK->setText(String(settings.rk), false);
    preTube1RP->setText(String(settings.rp), false);
    preTube1VK0->setText(String(settings.vk0), false);
    preTube1VPlus->setText(String(settings.vPlus), false);
    preTube1LowPassFbk->setText(String(settings.lowPassFbk), false);
}

void UITubeSettings::updateSettings(TubeSettings& settings) {
    settings.tubeType = this->preTube1->getSelectedItemIndex();
    settings.rp = this->preTube1RP->getText().getDoubleValue();
    settings.rk = this->preTube1RK->getText().getDoubleValue();
    settings.vPlus = this->preTube1VPlus->getText().getDoubleValue();
    settings.vk0 = this->preTube1VK0->getText().getDoubleValue();
    settings.lowPassFbk = this->preTube1LowPassFbk->getText().getDoubleValue();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UITubeSettings" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="680" initialHeight="140">
  <BACKGROUND backgroundColour="ff323e44"/>
  <COMBOBOX name="new combo box" id="abb9cc2618c65899" memberName="preTube1"
            virtualName="" explicitFocusOrder="0" pos="8 32 150 24" editable="0"
            layout="33" items="12AX7_68k&#10;12AX7_250k&#10;12AY7_68k&#10;12AY7_250k&#10;12AT7_68k&#10;12AT7_250k&#10;ECC83_68k&#10;ECC83_250k&#10;ECC81_68k&#10;ECC81_250k&#10;7025_68k&#10;7025_250k&#10;6L6CG_68k&#10;6L6CG_250k&#10;EL34_68k&#10;EL34_250k&#10;EL84_68k&#10;EL84_250k&#10;6550_68k&#10;6550_250k&#10;KT88_68k&#10;KT88_250k&#10;KT66_68k&#10;KT66_250k"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="887c35adcf1dd222" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="0 0 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pre Tube 1&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="391ed3dcef9b05f" memberName="preTube1RK"
              virtualName="" explicitFocusOrder="0" pos="176 32 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="ff9a0c8caa693e63" memberName="rkLabel" virtualName=""
         explicitFocusOrder="0" pos="168 0 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="RK&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="e2feaed7310a4598" memberName="preTube1RP"
              virtualName="" explicitFocusOrder="0" pos="344 32 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="2880963b095d9a70" memberName="rpLabel" virtualName=""
         explicitFocusOrder="0" pos="336 0 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="RP&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="28b0c483c6d7f12d" memberName="preTube1VK0"
              virtualName="" explicitFocusOrder="0" pos="512 32 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="87d87c9690b2d345" memberName="vK0Label"
         virtualName="" explicitFocusOrder="0" pos="504 0 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="VK0&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="fb5c672d97952e8" memberName="preTube1LowPassFbk"
              virtualName="" explicitFocusOrder="0" pos="176 104 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="4ac2cbf6e58b540a" memberName="lowPassLabel"
         virtualName="" explicitFocusOrder="0" pos="168 72 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="LowPassFbk&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="2dabbcc509be5690" memberName="preTube1VPlus"
              virtualName="" explicitFocusOrder="0" pos="344 104 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="547aa1b4a7b34978" memberName="vPlusLabel"
         virtualName="" explicitFocusOrder="0" pos="336 72 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="VPlus&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

