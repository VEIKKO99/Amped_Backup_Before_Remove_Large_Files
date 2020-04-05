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
class ThreeWayIRFileSwitch  : public Component
{
public:
    //==============================================================================
    ThreeWayIRFileSwitch ();
    ~ThreeWayIRFileSwitch();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    class Listener
    {
    public:
        /** Destructor. */
        virtual ~Listener() = default;

        /** Called when the button's state changes. */
        virtual void stateChanged (ThreeWayIRFileSwitch*)  {}
    };

    enum SwitchStatus {
        IRDefault = 0,
        IRCustomUserFile = 1,
        IROff = 2
    };

    void addListener (Listener* l)      { switchListeners.add (l); }
    void removeListener (Listener* l)   { switchListeners.remove (l); }
    SwitchStatus getCurrentStatus() const;
    const String &getCustomIrFilePath() const;
    void setCurrentStatus(SwitchStatus currentStatus, bool sendUpdate = true);

    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseDown (const MouseEvent& e) override;

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ListenerList<Listener> switchListeners;
    void toggleSwitch();
    SwitchStatus currentStatus = SwitchStatus::IRDefault;

    void openIRFileSelection();
    std::unique_ptr<Drawable> drawableButtonOff;
    std::unique_ptr<Drawable> drawableButtonOn;
    std::unique_ptr<Drawable> drawableButtonMiddle;

    String customIrFilePath;

    ApplicationProperties appProperties;

    File getLastFile();
    void setLastFile (const FileChooser& fc);

    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThreeWayIRFileSwitch)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

