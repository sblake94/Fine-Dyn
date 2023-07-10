#pragma once

#include <JuceHeader.h>

namespace GUI::Controls::BaseTypes
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A base class for all rotary dials
	/// </summary>
	class RotaryDial
		: public juce::Slider
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		RotaryDial(
			juce::String _labelText,
			juce::String _unitSuffix,
			const float _rangeMin,
			const float _rangeMax,
			const float _rangeInterval,
			const float _defaultValue,
			juce::LookAndFeel* _lookAndFeel);
		~RotaryDial();

		virtual void paint(juce::Graphics& _graphics) override;

	private://///////////////////////////////////////////////////////////////////////////////////////
		
		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;


		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RotaryDial);
	};
}