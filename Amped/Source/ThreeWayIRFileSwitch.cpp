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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "ThreeWayIRFileSwitch.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//==============================================================================

/*
struct IRFileSwitchAttachment::Pimpl  : private AttachedControlBase,
                                                                private Button::Listener
{
    Pimpl (AudioProcessorValueTreeState& s, const String& p, Button& b)
            : AttachedControlBase (s, p), button (b), ignoreCallbacks (false)
    {
        sendInitialUpdate();
        button.addListener (this);
    }

    ~Pimpl() override
    {
        button.removeListener (this);
        removeListener();
    }

    void setValue (float newValue) override
    {
        const ScopedLock selfCallbackLock (selfCallbackMutex);

        {
            ScopedValueSetter<bool> svs (ignoreCallbacks, true);
            button.setToggleState (newValue >= 0.5f, sendNotificationSync);
        }
    }

    void buttonClicked (Button* b) override
    {
        const ScopedLock selfCallbackLock (selfCallbackMutex);

        if (! ignoreCallbacks)
        {
            beginParameterChange();
            setNewDenormalisedValue (b->getToggleState() ? 1.0f : 0.0f);
            endParameterChange();
        }
    }

    Button& button;
    bool ignoreCallbacks;
    CriticalSection selfCallbackMutex;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pimpl)
};

AudioProcessorValueTreeState::ButtonAttachment::ButtonAttachment (AudioProcessorValueTreeState& s, const String& p, Button& b)
        : pimpl (new Pimpl (s, p, b))
{
}

AudioProcessorValueTreeState::ButtonAttachment::~ButtonAttachment() {}
*/
//[/MiscUserDefs]

//==============================================================================
ThreeWayIRFileSwitch::ThreeWayIRFileSwitch ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    drawableButtonOff = Drawable::createFromImageData (BinaryData::archon_big3way_up_png, BinaryData::archon_big3way_up_pngSize);
    drawableButtonMiddle = Drawable::createFromImageData (BinaryData::archon_big3way_middle_png, BinaryData::archon_big3way_middle_pngSize);
    drawableButtonOn = Drawable::createFromImageData (BinaryData::archon_big3way_down_png, BinaryData::archon_big3way_down_pngSize);

    PropertiesFile::Options options;

    options.applicationName     = JucePlugin_Name;
    options.filenameSuffix      = ".settings";
    options.osxLibrarySubFolder = "Application Support";
#if JUCE_LINUX
    options.folderName          = "~/.config";
#else
    options.folderName          = "";
#endif
    appProperties.setStorageParameters(options);

    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (90, 60);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ThreeWayIRFileSwitch::~ThreeWayIRFileSwitch()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ThreeWayIRFileSwitch::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    auto drawable = drawableButtonOff.get();
    if (currentStatus == IRDefault)
        drawable = drawableButtonOn.get();
    else if (currentStatus == IRCustomUserFile)
        drawable = drawableButtonMiddle.get();

    drawable->drawAt(g, 0, 0, 1.0f);
    //[/UserPrePaint]

    {
        int x = 1, y = 0, width = 60, height = 60;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ThreeWayIRFileSwitch::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ThreeWayIRFileSwitch::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    auto mousePos = e.getPosition();
    if (mousePos.getX() < 40) {
        toggleSwitch();
    }
    else {
        openIRFileSelection();
    }
    repaint();
    //[/UserCode_mouseDown]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ThreeWayIRFileSwitch::toggleSwitch() {
    if (currentStatus == IROff) {
        setCurrentStatus(IRDefault);
    }
    else if (currentStatus == IRCustomUserFile) {
        setCurrentStatus(IRDefault);
    }
    else if (currentStatus == IRDefault) {
        setCurrentStatus(IROff);
    }
}

const String &ThreeWayIRFileSwitch::getCustomIrFilePath() const {
    return customIrFilePath;
}

ThreeWayIRFileSwitch::SwitchStatus ThreeWayIRFileSwitch::getCurrentStatus() const {
    return currentStatus;
}

void ThreeWayIRFileSwitch::setCurrentStatus(ThreeWayIRFileSwitch::SwitchStatus newStatus, bool sendUpdate) {
    // We need to send the update if the status has been changed or custom user file changed.
    if ( ThreeWayIRFileSwitch::currentStatus != newStatus || newStatus == IRCustomUserFile)
    {
        ThreeWayIRFileSwitch::currentStatus = newStatus;
        Component::BailOutChecker checker (this);
        if (sendUpdate)
        {
            switchListeners.callChecked (checker, [this] (Listener& l) { l.stateChanged (this); });
        }
    }
}

File ThreeWayIRFileSwitch::getLastFile()
{
    File f;
    auto settings = appProperties.getUserSettings();

    if (settings != nullptr)
        f = File (settings->getValue ("ampedLastIRFile"));

    if (f == File())
        f = File::getSpecialLocation (File::userMusicDirectory);

    return f;
}

void ThreeWayIRFileSwitch::setLastFile (const FileChooser& fc)
{
    auto settings = appProperties.getUserSettings();

    if (settings != nullptr)
        settings->setValue ("ampedLastIRFile", fc.getResult().getFullPathName());
}

void ThreeWayIRFileSwitch::openIRFileSelection()
{
    FileChooser myChooser ("Please select the IR file.",
            getLastFile(),
            "*.wav");
    if (myChooser.browseForFileToOpen())
    {
#ifdef JUCE_MAC
        // On os x we only allow ir files from music folder.
        String musicDirectoryPath = File::getSpecialLocation(File::userMusicDirectory).getFullPathName();
        auto result = myChooser.getResult().getFullPathName();

        if (myChooser.getResult().getFullPathName().contains(String("Music"))) {
            ; // No op
        }
        else {
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Unupported File Location",
                    "Due to Apple's file security policies this version of Amped supports impulse file loading only from your user account's Music folder or its subfolders\n\nSuch as: /Users/yourUserName/Music/IRs/my_awesome_cab.wav", "OK", nullptr);
            return;
        }
#endif
        setLastFile(myChooser);
        AudioFormatManager audioFormatManager;
        audioFormatManager.registerFormat(new WavAudioFormat(), true);
        File irFile (myChooser.getResult());
        ScopedPointer<AudioFormatReader> reader = audioFormatManager.createReaderFor(irFile);

        double maxLengthInSecs = 0.6;

        if ((reader->bitsPerSample == 16 || reader->bitsPerSample == 24) && // Bit deptg
                (reader->sampleRate == 44100 || reader->sampleRate == 48000 || reader->sampleRate == 96000) && // Samplerate
                (reader->lengthInSamples <= reader->sampleRate * maxLengthInSecs)) // Max length
        {
            customIrFilePath = irFile.getFullPathName();
            setCurrentStatus(IRCustomUserFile);
        }
        else
        {
            AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon, "Not supported file format", "Supported file format: Wav file, 16/24 bits, 44.1khz, 48khz, 96khz. Max length of sample 0.6seconds.", "OK", nullptr);
        }


        //   irFileNameLabel->setText(irFile.getFileName(), dontSendNotification);
     //   selectedFileName = irFile.getFullPathName();
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ThreeWayIRFileSwitch" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="90" initialHeight="60">
  <METHODS>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="323e44">
    <IMAGE pos="1 0 60 60" resource="" opacity="1.0" mode="0"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

