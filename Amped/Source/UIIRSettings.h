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
class UIIRSettings  : public Component,
                      public Button::Listener
{
public:
    //==============================================================================
    UIIRSettings ();
    ~UIIRSettings();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setupUI (IRSettings& irSettings, String irName);
    void updateSettings(IRSettings& settings);
    void chooseIRFile();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    String selectedFileName = "";
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> irBtn;
    std::unique_ptr<Label> irFileNameLabel;
    std::unique_ptr<TextEditor> irGain;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UIIRSettings)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

