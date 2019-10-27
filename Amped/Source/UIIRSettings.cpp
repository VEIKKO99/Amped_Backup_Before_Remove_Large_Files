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

#include "UIIRSettings.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
UIIRSettings::UIIRSettings ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    irBtn.reset (new TextButton ("new button"));
    addAndMakeVisible (irBtn.get());
    irBtn->setButtonText (TRANS("Cab Ir"));
    irBtn->addListener (this);

    irBtn->setBounds (0, 0, 80, 24);

    cabIrLabel.reset (new Label ("new label",
                                 TRANS("Default (from memory)\n")));
    addAndMakeVisible (cabIrLabel.get());
    cabIrLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    cabIrLabel->setJustificationType (Justification::centredLeft);
    cabIrLabel->setEditable (false, false, false);
    cabIrLabel->setColour (TextEditor::textColourId, Colours::black);
    cabIrLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    cabIrLabel->setBounds (153, 0, 200, 24);

    irGain.reset (new TextEditor ("cabSimGain"));
    addAndMakeVisible (irGain.get());
    irGain->setMultiLine (false);
    irGain->setReturnKeyStartsNewLine (false);
    irGain->setReadOnly (false);
    irGain->setScrollbarsShown (true);
    irGain->setCaretVisible (true);
    irGain->setPopupMenuEnabled (true);
    irGain->setText (String());

    irGain->setBounds (96, 0, 47, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (360, 40);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

UIIRSettings::~UIIRSettings()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    irBtn = nullptr;
    cabIrLabel = nullptr;
    irGain = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void UIIRSettings::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void UIIRSettings::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void UIIRSettings::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == irBtn.get())
    {
        //[UserButtonCode_irBtn] -- add your button handler code here..
        //[/UserButtonCode_irBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="UIIRSettings" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="360" initialHeight="40">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="new button" id="9efe025fec7486c4" memberName="irBtn" virtualName=""
              explicitFocusOrder="0" pos="0 0 80 24" buttonText="Cab Ir" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="new label" id="119f4b72245d948e" memberName="cabIrLabel"
         virtualName="" explicitFocusOrder="0" pos="153 0 200 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Default (from memory)&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="cabSimGain" id="bdf3c9eff0364d86" memberName="irGain" virtualName=""
              explicitFocusOrder="0" pos="96 0 47 24" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

