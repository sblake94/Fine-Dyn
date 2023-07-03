/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "DSP/Parameters.h"
#include "GUI/LookAndFeels/CustomLookAndFeel.h"
#include "GUI/Controls/BaseTypes/CustomControlBase.h"

#include <stdlib.h>
#include <map>

//==============================================================================
Fine_DynAudioProcessorEditor::Fine_DynAudioProcessorEditor (Fine_DynAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , Slider::Listener()
    , Button::Listener()
    , audioProcessor (p)
    , m_background()
    , m_controlManager(m_windowWidth, m_windowHeight, new GUI::LookAndFeels::CustomLookAndFeel()) // Potential memory leak?
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(m_windowWidth, m_windowHeight);
    setResizable(false, false);

    // Make all controls visible
    // NOTE: Many for loops makes me sad, can we do this inside of a single for loop?
    for (BaseTypes::RotaryDial* dialPtr : m_controlManager.GetAllRotaryDials())
    {
        dialPtr->setValue(DSP::Parameters::GetSliderParams().at(dialPtr->m_id)->get(), juce::dontSendNotification);
        dialPtr->addListener(this);
        addAndMakeVisible(dynamic_cast<juce::Slider*>(dialPtr));
    }

    for (BaseTypes::LatchButton* buttonPtr : m_controlManager.GetAllLatchButtons())
    {
        buttonPtr->setToggleState(DSP::Parameters::GetBoolParams().at(buttonPtr->m_id)->get(), juce::dontSendNotification);
        buttonPtr->addListener(this);
        addAndMakeVisible(dynamic_cast<juce::ToggleButton*>(buttonPtr));
    }

    for (BaseTypes::CustomLabel* labelPtr : m_controlManager.GetAllCustomLabels())
    {
        addAndMakeVisible(dynamic_cast<juce::Label*>(labelPtr));
    }

    for (BaseTypes::LinearSlider* sliderPtr : m_controlManager.GetAllLinearSliders())
    {
        sliderPtr->setValue(DSP::Parameters::GetSliderParams().at(sliderPtr->m_id)->get(), juce::dontSendNotification);
        sliderPtr->addListener(this);
        addAndMakeVisible(dynamic_cast<juce::Slider*>(sliderPtr));
    }
}

Fine_DynAudioProcessorEditor::~Fine_DynAudioProcessorEditor()
{
}

//==============================================================================
void Fine_DynAudioProcessorEditor::paint (juce::Graphics& g)
{
    m_background.paint(g, m_windowWidth, m_windowHeight);
    m_controlManager.paint(g);
}

void Fine_DynAudioProcessorEditor::resized()
{
    // Get new window size
    m_windowWidth = getWidth();
    m_windowHeight = getHeight();

    // Resize Controls
    m_controlManager.resized(m_windowWidth, m_windowHeight);
}

/////////////////////////////////////////////////////////////////////////////////////
void Fine_DynAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // Get the slider's ID
    juce::ParameterID sliderID = dynamic_cast<GUI::Controls::BaseTypes::CustomControlBase*>(slider)->m_id;

    // Get the slider's value
    float sliderValue = slider->getValue();

    // Update the processor
    for (std::pair<juce::ParameterID, juce::AudioParameterFloat*> param : DSP::Parameters::GetSliderParams())
    {
        if (param.first.getParamID() == sliderID.getParamID())
        {
            juce::AudioParameterFloat* paramFloat = param.second;
            *paramFloat = (float)sliderValue;
            return;
        }
    }

    throw new std::exception("Slider ID not found in processor");
}

void Fine_DynAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    // Get the button's ID
    juce::ParameterID buttonID = dynamic_cast<GUI::Controls::BaseTypes::CustomControlBase*>(button)->m_id;

    // Get the button's value
    bool buttonValue = button->getToggleState();

    // Update the processor
    for (std::pair<juce::ParameterID, juce::AudioParameterBool*> param : DSP::Parameters::GetBoolParams())
    {
        if (param.first.getParamID() == buttonID.getParamID())
        {
            param.second->setValueNotifyingHost(buttonValue);
            return;
        }
    }

    throw new std::exception("Button ID not found in processor");
}