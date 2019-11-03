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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "AdminSettingsUtil.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UIEQSettings  : public Component,
                      public Button::Listener
{
public:
    //==============================================================================
    UIEQSettings ();
    ~UIEQSettings();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setupUI(EQSettings& settings, String eqName);
    void updateSettings(EQSettings& settings);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    String selectedLowIRFileName = "";
    String selectedHighIRFileName = "";

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> lowPotBtn;
    std::unique_ptr<Label> lowPotIrNameLabel;
    std::unique_ptr<TextEditor> irGain;
    std::unique_ptr<Label> eqName;
    std::unique_ptr<TextButton> highPotBtn;
    std::unique_ptr<Label> highPotIrNameLabel;
    std::unique_ptr<Label> irgainLabel;
    std::unique_ptr<TextEditor> realisticGain;
    std::unique_ptr<Label> irgainLabel2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UIEQSettings)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

