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
    std::unique_ptr<Label> label3;
    std::unique_ptr<TextEditor> preTube1RP;
    std::unique_ptr<Label> label4;
    std::unique_ptr<TextEditor> preTube1VK0;
    std::unique_ptr<Label> label5;
    std::unique_ptr<TextEditor> preTube1LowPassFbk;
    std::unique_ptr<Label> label6;
    std::unique_ptr<TextEditor> preTube1OutHpFreq;
    std::unique_ptr<Label> label7;
    std::unique_ptr<TextEditor> preTube1VPlus;
    std::unique_ptr<Label> label8;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UITubeSettings)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

