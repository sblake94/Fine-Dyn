/*
	==========================================================================================

	@Author : SBlake
	This class describes a Frequency Slider with prebaked customizations for this project.

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../BaseTypes/CustomControlBase.h"
#include "../BaseTypes/RotaryDial.h"

namespace GUI::Controls::Dials
{	
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A custom dial for frequency parameters.
	/// </summary>
	class FrequencyDial
		: public BaseTypes::RotaryDial
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		FrequencyDial(
			juce::String _labelText,
			const int _xPos,
			const int _yPos,
			const int _width,
			const int _height,
			const int _parameterID,
			const float _defaultValue = 2000.0f,
			const float _rangeMin = 20.0f,
			const float _rangeMax = 20000.0f,
			const float _rangeInterval = 1.0f,
			juce::LookAndFeel* _lookAndFeel = nullptr);
		~FrequencyDial();
		
		void paint(juce::Graphics& g) override;
		
		juce::String m_labelText;
		int m_xPos, m_yPos;

	private: /////////////////////////////////////////////////////////////////////////////////////////
		void SetParameterID(const juce::ParameterID _parameterID);
		juce::ParameterID m_parameterID;

		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FrequencyDial);
	};
}