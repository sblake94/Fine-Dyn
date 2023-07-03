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
	class LevelSlider
		: public BaseTypes::LinearSlider
	{
	public: /////////////////////////////////////////////////////////////////////////////////////
	 	LevelSlider(
			const float _rangeMin,
			const float _rangeMax,
			const float _rangeInterval,
			const float _defaultValue,
			juce::String _labelText,
			const int _xPos,
			const int _yPos,
			const int _width,
			const int _height,
			const int _paramID,
			const bool _isVertical,
	 		juce::LookAndFeel* _lookAndFeel = nullptr);
	 	~LevelSlider();
	 
	 	void paint(juce::Graphics& _graphics) override;
	 
	private: /////////////////////////////////////////////////////////////////////////////////////
	 	juce::Colour m_backgroundColour;
	 	juce::Colour m_fillColour;
	 	juce::Colour m_outlineColour;
	 	juce::Colour m_textColour;
	};
}