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
#include <PluginProcessor.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "AdminSettingsUtil.h"
#include "UITubeSettings.h"
#include "UIIRSettings.h"
//[/Headers]

#include "UIIRSettings.h"
#include "UIIRSettings.h"
#include "UITubeSettings.h"
#include "UITubeSettings.h"
#include "UIEQSettings.h"
#include "UIEQSettings.h"
#include "UIEQSettings.h"
#include "UIEQSettings.h"
#include "UIEQSettings.h"


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
    AdminSettingsWindow(ISoundSettingsChanged* changed, AudioProcessorValueTreeState* state);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ISoundSettingsChanged* changeInterface;
    AudioProcessorValueTreeState* valueTreeState;
    void updateSettings();
    void setupUI();
    void chooseBGImageFile();
    void saveSettings();
    String copyFile(String destDirectory, String originalFile);
    void showAlert(String message);
    void loadSettings();
    void addNewPresetBtnPressed();
    void prevPresetBtnPressed();
    void nextPresetBtnPressed();
    void updatePresetUI();
    void savePresetBtnPressed();
    void deletePresetBtnPressed();
    void encryptFile();
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ComboBox> preInputType;
    std::unique_ptr<Label> label;
    std::unique_ptr<TextButton> updateButton;
    std::unique_ptr<Label> label4;
    std::unique_ptr<TextEditor> inMin;
    std::unique_ptr<TextEditor> inMax;
    std::unique_ptr<TextEditor> mMin;
    std::unique_ptr<TextEditor> mMax;
    std::unique_ptr<Label> label6;
    std::unique_ptr<Label> fileNameLabel;
    std::unique_ptr<UIIRSettings> cabIrUi;
    std::unique_ptr<UIIRSettings> ampIrUi;
    std::unique_ptr<UITubeSettings> preTube1Settings;
    std::unique_ptr<UITubeSettings> powerAmpTubeSettings;
    std::unique_ptr<ComboBox> knobTypeComboBox;
    std::unique_ptr<Label> label7;
    std::unique_ptr<TextButton> bgButton;
    std::unique_ptr<Label> bgImageLabel;
    std::unique_ptr<UIEQSettings> bassEq;
    std::unique_ptr<UIEQSettings> middleEq;
    std::unique_ptr<UIEQSettings> component3;
    std::unique_ptr<UIEQSettings> trebleEq;
    std::unique_ptr<Label> label5;
    std::unique_ptr<TextEditor> hornetDrive;
    std::unique_ptr<Label> label8;
    std::unique_ptr<TextEditor> hornetPresence;
    std::unique_ptr<UIEQSettings> presenceEq;
    std::unique_ptr<TextButton> updateButton2;
    std::unique_ptr<TextButton> loadButton;
    std::unique_ptr<Label> label9;
    std::unique_ptr<TextEditor> driveMin;
    std::unique_ptr<TextEditor> driveMax;
    std::unique_ptr<Label> label10;
    std::unique_ptr<Label> overSampleLabel;
    std::unique_ptr<TextEditor> overSample;
    std::unique_ptr<Label> amtPreAmpTubesLabel;
    std::unique_ptr<TextEditor> amountOfPreampTubes;
    std::unique_ptr<Label> label3;
    std::unique_ptr<Label> label11;
    std::unique_ptr<Label> presetNumber;
    std::unique_ptr<TextEditor> presetNameEditor;
    std::unique_ptr<Label> label13;
    std::unique_ptr<TextButton> addNewPresetBtn;
    std::unique_ptr<TextButton> savePresetBtn2;
    std::unique_ptr<TextButton> prevPresetBtn;
    std::unique_ptr<TextButton> nextPresetBtn;
    std::unique_ptr<TextButton> deletePresetBtn;
    std::unique_ptr<TextEditor> presetsInfoTextView;
    std::unique_ptr<TextButton> encryptFileBtn;
    std::unique_ptr<Label> label12;
    std::unique_ptr<TextEditor> masterMultiplierOff;
    std::unique_ptr<TextEditor> masterMultiplier025;
    std::unique_ptr<TextEditor> masterMultiplier050;
    std::unique_ptr<TextEditor> masterMultiplier075;
    std::unique_ptr<TextEditor> masterMultiplier100;
    std::unique_ptr<Label> label14;
    std::unique_ptr<Label> label15;
    std::unique_ptr<Label> label16;
    std::unique_ptr<Label> label17;
    std::unique_ptr<Label> label18;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdminSettingsWindow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

