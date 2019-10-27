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
#include "UITubeSettings.h"
#include "UIIRSettings.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class AdminSettingsWindow  : public Component,
                             public ComboBox::Listener,
                             public Button::Listener
{
public:
    //==============================================================================
    AdminSettingsWindow ();
    ~AdminSettingsWindow();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    AdminSettingsWindow (ISoundSettingsChanged* changed);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ISoundSettingsChanged* changeInterface;
    void updateSettings();
    void setupUI();
    std::unique_ptr<UITubeSettings> preTube1Settings;
    std::unique_ptr<UITubeSettings> preTube2Settings;
    std::unique_ptr<UITubeSettings> powerAmpTubeSettings;

    std::unique_ptr<UIIRSettings> cabIrUi;
    std::unique_ptr<UIIRSettings> ampIrUi;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ComboBox> preInputType;
    std::unique_ptr<Label> label;
    std::unique_ptr<TextButton> updateButton;
    std::unique_ptr<Label> label3;
    std::unique_ptr<Label> label2;
    std::unique_ptr<Label> label4;
    std::unique_ptr<TextEditor> inMin;
    std::unique_ptr<TextEditor> inMax;
    std::unique_ptr<TextEditor> dMin;
    std::unique_ptr<TextEditor> dMax;
    std::unique_ptr<TextEditor> mMin;
    std::unique_ptr<TextEditor> mMax;
    std::unique_ptr<Label> label5;
    std::unique_ptr<TextEditor> eqGain;
    std::unique_ptr<Label> label6;
    std::unique_ptr<Label> label7;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdminSettingsWindow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

