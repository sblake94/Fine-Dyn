/*
	==========================================================================================

	@Author : SBlake
	This class describes a Linear Gain Slider with prebaked customizations for this project.

	==========================================================================================
*/

#pragma once
#include <JuceHeader.h>

#include "../BaseTypes/LinearSlider.h"

namespace GUI::Controls::Sliders
{
	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///		This class describes a Linear Gain Slider with prebaked customizations for this project.
	/// </summary>
	class ThresholdSlider
		: public BaseTypes::LinearSlider
	{
	public: /////////////////////////////////////////////////////////////////////////////////////
	 	ThresholdSlider(
			const float _rangeMin,
			const float _rangeMax,
			const float _rangeInterval,
			const float _defaultValue,
			const bool _isVertical,
			juce::LookAndFeel* _lookAndFeel);
	 	~ThresholdSlider();
	 
	 	void paint(juce::Graphics& _graphics) override;
	 
	private: /////////////////////////////////////////////////////////////////////////////////////
	 	juce::Colour m_backgroundColour;
	 	juce::Colour m_fillColour;
	 	juce::Colour m_outlineColour;
	 	juce::Colour m_textColour;
	};
}