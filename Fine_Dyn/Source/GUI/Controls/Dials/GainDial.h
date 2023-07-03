/*
	==========================================================================================

	@Author : SBlake
	This class describes a Gain Slider with prebaked customizations for this project.

	==========================================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../BaseTypes/RotaryDial.h"

namespace GUI::Controls::Dials
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A custom dial for Gain-specific parameters.
	/// </summary>
	class GainDial
		: public BaseTypes::RotaryDial
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		GainDial(
			juce::String _labelText,
			const int _xPos,
			const int _yPos,
			const int _width,
			const int _height,
			const int _parameterID,
			const float _defaultValue,
			const float _rangeMin,
			const float _rangeMax,
			const float _rangeInterval,
			juce::LookAndFeel* _lookAndFeel = nullptr);

		~GainDial();

		void paint(juce::Graphics& g) override;

	private: /////////////////////////////////////////////////////////////////////////////////////////
		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainDial)
	};
}