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
#include "MainComponent.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class AmpTopBar  : public Component,
                   public Button::Listener,
                   public ComboBox::Listener
{
public:
    //==============================================================================
    AmpTopBar ();
    ~AmpTopBar();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    MainComponent* mainComponent = nullptr;
    void setProcessor(AmpedAudioProcessor* processor);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void togglePedalBoard();
    AmpedAudioProcessor* processor = nullptr;
    void initAmps();
    void ampChanged();
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> licenceManagerBtn;
    std::unique_ptr<TextButton> pedalBoardBtn;
    std::unique_ptr<ComboBox> ampComboBox;
    std::unique_ptr<ComboBox> presetComboBox;
    std::unique_ptr<Label> label;
    std::unique_ptr<Label> label2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AmpTopBar)

    void initPresets();
};

//[EndFile] You can add extra defines here...
//[/EndFile]

