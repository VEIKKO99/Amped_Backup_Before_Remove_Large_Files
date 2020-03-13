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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class LicenceDialog  : public Component,
                       ModalComponentManager::Callback,
                       public Button::Listener
{
public:
    //==============================================================================
    LicenceDialog ();
    ~LicenceDialog();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    static void showLicenseValidDialog(String email, Component* parent);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void mouseUp (const MouseEvent& e) override;
    bool keyPressed (const KeyPress& key) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void licenceCodeTextChanged();
    void modalStateFinished (int returnValue) override;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> licenceCodeLabel;
    std::unique_ptr<TextEditor> licenceCodeEditor;
    std::unique_ptr<TextButton> copyKeyBtn;
    std::unique_ptr<TextButton> pasteLicenceBtn;
    std::unique_ptr<TextButton> buyLicenseBtn;
    std::unique_ptr<HyperlinkButton> hyperlinkButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LicenceDialog)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

