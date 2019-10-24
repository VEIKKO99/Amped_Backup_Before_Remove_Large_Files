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

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class UITubeSettings  : public Component,
                        public ComboBox::Listener
{
public:
    //==============================================================================
    UITubeSettings ();
    ~UITubeSettings();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setupUI(TubeSettings& settings, String tubeName);
    void updateSettings(TubeSettings& settings);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ComboBox> preTube1;
    std::unique_ptr<Label> label2;
    std::unique_ptr<TextEditor> preTube1RK;
    std::unique_ptr<Label> rkLabel;
    std::unique_ptr<TextEditor> preTube1RP;
    std::unique_ptr<Label> rpLabel;
    std::unique_ptr<TextEditor> preTube1VK0;
    std::unique_ptr<Label> vK0Label;
    std::unique_ptr<TextEditor> preTube1LowPassFbk;
    std::unique_ptr<Label> lowPassLabel;
    std::unique_ptr<TextEditor> preTube1VPlus;
    std::unique_ptr<Label> vPlusLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UITubeSettings)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

