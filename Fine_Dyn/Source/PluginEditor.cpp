/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "DSP/Parameters.h"
#include "GUI/GridResident.h"
#include "GUI/LookAndFeels/CustomLookAndFeel.h"

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
    auto residents = m_controlManager.GetAllGridResidents();
    for (GUI::GridResident* gridResident : residents)
    {
        // set the component's value to the parameter's value
        int paramID = gridResident->m_parameterID;

        // add this as a listener to the component
        if (juce::Button* buttonPtr = gridResident->GetAsButtonPtr())
        {
            const BoolParamDirectory& params = DSP::Parameters::GetBoolParams();
            AudioParameterBool* param = DSP::Parameters::GetBoolParams().at(paramID);
            
            buttonPtr->addListener(this);
			buttonPtr->setToggleState(*param, juce::dontSendNotification);
            addAndMakeVisible(*buttonPtr);
        }
        else if (juce::Slider* sliderPtr = gridResident->GetAsSliderPtr())
        {
            const FloatParamDirectory& params = DSP::Parameters::GetSliderParams();
            AudioParameterFloat* param = DSP::Parameters::GetSliderParams().at(paramID);

			sliderPtr->addListener(this);
			sliderPtr->setValue(*param, juce::dontSendNotification);
            addAndMakeVisible(*sliderPtr);
		}
        else if (juce::Label* labelPtr = gridResident->GetAsLabelPtr())
        {
            addAndMakeVisible(*labelPtr);
        }
        else
        {
			throw new exception("GridResident is not a handled type");
		}
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
    auto gridResidents = m_controlManager.GetAllGridResidents();
    for (auto resident : gridResidents)
    {
        juce::ParameterID buttonID = resident->m_parameterID;

        // Get the slider's value
        float sliderValue = slider->getValue();

        // Update the processor
        for (pair<juce::ParameterID, juce::AudioParameterFloat*> param : DSP::Parameters::GetSliderParams())
        {
            if (param.first.getParamID() == buttonID.getParamID())
            {
                juce::AudioParameterFloat* paramFloat = param.second;
                *paramFloat = (float)sliderValue;
                return;
            }
        }
	}

    

    throw new exception("Slider ID not found in processor");
}

void Fine_DynAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    // Get the button's ID
    auto residents = m_controlManager.GetAllGridResidents();
    for (GUI::GridResident* res : residents)
    {
        juce::Button* resButton = res->GetAsButtonPtr();
        if (button == res->GetAsButtonPtr())
        {
			juce::ParameterID buttonID = res->m_parameterID;
    
            // Get the button's value
            bool buttonValue = button->getToggleState();

            // Update the processor
            for (pair<juce::ParameterID, juce::AudioParameterBool*> param : DSP::Parameters::GetBoolParams())
            {
                if (param.first.getParamID() == buttonID.getParamID())
                {
					param.second->setValueNotifyingHost(buttonValue);
					return;
				}
			}
		}
	}

    throw new exception("Button ID not found in processor");
}