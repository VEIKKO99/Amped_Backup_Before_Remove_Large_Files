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

    preTube1->setBounds (8, 112, 150, 24);

    label2.reset (new Label ("new label",
                             TRANS("Pre Tube 1\n")));
    addAndMakeVisible (label2.get());
    label2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label2->setBounds (0, 80, 150, 24);

    preTube1RK.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (preTube1RK.get());
    preTube1RK->setMultiLine (false);
    preTube1RK->setReturnKeyStartsNewLine (false);
    preTube1RK->setReadOnly (false);
    preTube1RK->setScrollbarsShown (true);
    preTube1RK->setCaretVisible (true);
    preTube1RK->setPopupMenuEnabled (true);
    preTube1RK->setText (String());

    preTube1RK->setBounds (176, 112, 150, 24);

    label3.reset (new Label ("new label",
                             TRANS("RK\n")));
    addAndMakeVisible (label3.get());
    label3->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label3->setBounds (168, 80, 150, 24);

    preTube1RP.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (preTube1RP.get());
    preTube1RP->setMultiLine (false);
    preTube1RP->setReturnKeyStartsNewLine (false);
    preTube1RP->setReadOnly (false);
    preTube1RP->setScrollbarsShown (true);
    preTube1RP->setCaretVisible (true);
    preTube1RP->setPopupMenuEnabled (true);
    preTube1RP->setText (String());

    preTube1RP->setBounds (344, 112, 150, 24);

    label4.reset (new Label ("new label",
                             TRANS("RP\n")));
    addAndMakeVisible (label4.get());
    label4->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label4->setBounds (336, 80, 150, 24);

    preTube1VK0.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (preTube1VK0.get());
    preTube1VK0->setMultiLine (false);
    preTube1VK0->setReturnKeyStartsNewLine (false);
    preTube1VK0->setReadOnly (false);
    preTube1VK0->setScrollbarsShown (true);
    preTube1VK0->setCaretVisible (true);
    preTube1VK0->setPopupMenuEnabled (true);
    preTube1VK0->setText (String());

    preTube1VK0->setBounds (512, 112, 150, 24);

    label5.reset (new Label ("new label",
                             TRANS("VK0\n")));
    addAndMakeVisible (label5.get());
    label5->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label5->setBounds (504, 80, 150, 24);

    preTube1LowPassFbk.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (preTube1LowPassFbk.get());
    preTube1LowPassFbk->setMultiLine (false);
    preTube1LowPassFbk->setReturnKeyStartsNewLine (false);
    preTube1LowPassFbk->setReadOnly (false);
    preTube1LowPassFbk->setScrollbarsShown (true);
    preTube1LowPassFbk->setCaretVisible (true);
    preTube1LowPassFbk->setPopupMenuEnabled (true);
    preTube1LowPassFbk->setText (String());

    preTube1LowPassFbk->setBounds (176, 184, 150, 24);

    label6.reset (new Label ("new label",
                             TRANS("LowPassFbk\n")));
    addAndMakeVisible (label6.get());
    label6->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label6->setBounds (168, 152, 150, 24);

    preTube1OutHpFreq.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (preTube1OutHpFreq.get());
    preTube1OutHpFreq->setMultiLine (false);
    preTube1OutHpFreq->setReturnKeyStartsNewLine (false);
    preTube1OutHpFreq->setReadOnly (false);
    preTube1OutHpFreq->setScrollbarsShown (true);
    preTube1OutHpFreq->setCaretVisible (true);
    preTube1OutHpFreq->setPopupMenuEnabled (true);
    preTube1OutHpFreq->setText (String());

    preTube1OutHpFreq->setBounds (344, 184, 150, 24);

    label7.reset (new Label ("new label",
                             TRANS("OutHpFreq\n")));
    addAndMakeVisible (label7.get());
    label7->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label7->setBounds (336, 152, 150, 24);

    preTube1VPlus.reset (new TextEditor ("new text editor"));
    addAndMakeVisible (preTube1VPlus.get());
    preTube1VPlus->setMultiLine (false);
    preTube1VPlus->setReturnKeyStartsNewLine (false);
    preTube1VPlus->setReadOnly (false);
    preTube1VPlus->setScrollbarsShown (true);
    preTube1VPlus->setCaretVisible (true);
    preTube1VPlus->setPopupMenuEnabled (true);
    preTube1VPlus->setText (String());

    preTube1VPlus->setBounds (512, 184, 150, 24);

    label8.reset (new Label ("new label",
                             TRANS("VPlus\n")));
    addAndMakeVisible (label8.get());
    label8->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label8->setBounds (504, 152, 150, 24);

    updateButton.reset (new TextButton ("new button"));
    addAndMakeVisible (updateButton.get());
    updateButton->setButtonText (TRANS("Update"));
    updateButton->addListener (this);

    updateButton->setBounds (344, 240, 150, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (800, 600);


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
    preTube1 = nullptr;
    label2 = nullptr;
    preTube1RK = nullptr;
    label3 = nullptr;
    preTube1RP = nullptr;
    label4 = nullptr;
    preTube1VK0 = nullptr;
    label5 = nullptr;
    preTube1LowPassFbk = nullptr;
    label6 = nullptr;
    preTube1OutHpFreq = nullptr;
    label7 = nullptr;
    preTube1VPlus = nullptr;
    label8 = nullptr;
    updateButton = nullptr;


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
    else if (comboBoxThatHasChanged == preTube1.get())
    {
        //[UserComboBoxCode_preTube1] -- add your combo box handling code here..
        //[/UserComboBoxCode_preTube1]
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
    settings->ampSettings.preAmpTubes[0].tubeType = static_cast<PreAmp::EInputType>(preTube1->getSelectedItemIndex());

}

AdminSettingsWindow::AdminSettingsWindow (ISoundSettingsChanged* changed) : AdminSettingsWindow()
{
    changeInterface = changed;
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
                 fixedSize="0" initialWidth="800" initialHeight="600">
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
  <COMBOBOX name="new combo box" id="abb9cc2618c65899" memberName="preTube1"
            virtualName="" explicitFocusOrder="0" pos="8 112 150 24" editable="0"
            layout="33" items="12AX7_68k&#10;12AX7_250k&#10;12AY7_68k&#10;12AY7_250k&#10;12AT7_68k&#10;12AT7_250k&#10;ECC83_68k&#10;ECC83_250k&#10;ECC81_68k&#10;ECC81_250k&#10;7025_68k&#10;7025_250k&#10;6L6CG_68k&#10;6L6CG_250k&#10;EL34_68k&#10;EL34_250k&#10;EL84_68k&#10;EL84_250k&#10;6550_68k&#10;6550_250k&#10;KT88_68k&#10;KT88_250k&#10;KT66_68k&#10;KT66_250k"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="887c35adcf1dd222" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="0 80 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pre Tube 1&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="391ed3dcef9b05f" memberName="preTube1RK"
              virtualName="" explicitFocusOrder="0" pos="176 112 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="ff9a0c8caa693e63" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="168 80 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="RK&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="e2feaed7310a4598" memberName="preTube1RP"
              virtualName="" explicitFocusOrder="0" pos="344 112 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="2880963b095d9a70" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="336 80 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="RP&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="28b0c483c6d7f12d" memberName="preTube1VK0"
              virtualName="" explicitFocusOrder="0" pos="512 112 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="87d87c9690b2d345" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="504 80 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="VK0&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="fb5c672d97952e8" memberName="preTube1LowPassFbk"
              virtualName="" explicitFocusOrder="0" pos="176 184 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="4ac2cbf6e58b540a" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="168 152 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="LowPassFbk&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="5c5f2d3c229bb0e8" memberName="preTube1OutHpFreq"
              virtualName="" explicitFocusOrder="0" pos="344 184 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="79ad8375733cea38" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="336 152 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="OutHpFreq&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="new text editor" id="2dabbcc509be5690" memberName="preTube1VPlus"
              virtualName="" explicitFocusOrder="0" pos="512 184 150 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="new label" id="547aa1b4a7b34978" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="504 152 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="VPlus&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="3518e4a88f598a7" memberName="updateButton"
              virtualName="" explicitFocusOrder="0" pos="344 240 150 24" buttonText="Update"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

