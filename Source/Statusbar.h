/*
 // Copyright (c) 2021-2022 Timothy Schoen.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/
#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "Utility/SettingsFile.h"
#include "Utility/ModifierKeyListener.h"

class Canvas;
class LevelMeter;
class MidiBlinker;
class PluginProcessor;
class OverlayDisplaySettings;
class SnapSettings;

class VolumeSlider : public Slider {
public:
    VolumeSlider();
    ~VolumeSlider() override = default;
    void paint(Graphics& g) override;
    void resized() override;

private:
    int margin = 18;
};

class StatusbarSource : public Timer {

public:
    struct Listener {
        virtual void midiReceivedChanged(bool midiReceived) {};
        virtual void midiSentChanged(bool midiSent) {};
        virtual void audioProcessedChanged(bool audioProcessed) {};
        virtual void audioLevelChanged(float newLevel[2], float newPeak[2]) {};
        virtual void timerCallback() {};
    };

    StatusbarSource();

    void processBlock(AudioBuffer<float> const& buffer, MidiBuffer& midiIn, MidiBuffer& midiOut, int outChannels);

    void setSampleRate(double sampleRate);

    void prepareToPlay(int numChannels);

    void timerCallback() override;

    void addListener(Listener* l);
    void removeListener(Listener* l);

private:
    std::atomic<int> lastMidiReceivedTime = 0;
    std::atomic<int> lastMidiSentTime = 0;
    std::atomic<int> lastAudioProcessedTime = 0;
    std::atomic<float> level[2] = { 0 };
    std::atomic<float> peakHold[2] = { 0 };

    int peakHoldDelay[2] = { 0 };

    int numChannels;

    double sampleRate = 44100;

    bool midiReceivedState = false;
    bool midiSentState = false;
    bool audioProcessedState = false;
    std::vector<Listener*> listeners;
};

class Statusbar : public Component
    , public SettingsFileListener
    , public StatusbarSource::Listener
    , public ModifierKeyListener {
    PluginProcessor* pd;

public:
    explicit Statusbar(PluginProcessor* processor);
    ~Statusbar() override;

    void paint(Graphics& g) override;

    void resized() override;

    void propertyChanged(String const& name, var const& value) override;

    void audioProcessedChanged(bool audioProcessed) override;

    bool wasLocked = false; // Make sure it doesn't re-lock after unlocking (because cmd is still down)

    LevelMeter* levelMeter;
    MidiBlinker* midiBlinker;

    TextButton powerButton, connectionStyleButton, connectionPathfind, centreButton, fitAllButton, protectButton;

    TextButton overlayButton, overlaySettingsButton;
    std::unique_ptr<OverlayDisplaySettings> overlayDisplaySettings;

    TextButton snapEnableButton, snapSettingsButton;
    std::unique_ptr<SnapSettings> snapSettings;

    TextButton oversampleSelector;

    Label zoomLabel;

    VolumeSlider volumeSlider;

    Value showDirection;

    static constexpr int statusbarHeight = 30;

    std::unique_ptr<ButtonParameterAttachment> enableAttachment;
    std::unique_ptr<SliderParameterAttachment> volumeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Statusbar)
};
