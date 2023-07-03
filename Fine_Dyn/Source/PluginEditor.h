/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "GUI/Background.h"
#include "GUI/ControlManager.h"

//==============================================================================
/**
*/
class Fine_DynAudioProcessorEditor  
    : public juce::AudioProcessorEditor
    , public juce::Slider::Listener
    , public juce::Button::Listener
{
public:
    Fine_DynAudioProcessorEditor (Fine_DynAudioProcessor&);
    ~Fine_DynAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Fine_DynAudioProcessor& audioProcessor;

    GUI::Background m_background;
    GUI::ControlManager m_controlManager;

    const float m_aspectRatio = 16.0f / 9.0f;
    int m_windowWidth = 720;
    int m_windowHeight = m_windowWidth / m_aspectRatio;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Fine_DynAudioProcessorEditor)
};
