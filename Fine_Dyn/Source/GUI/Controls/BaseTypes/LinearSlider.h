#pragma once

#include <JuceHeader.h>

namespace GUI::Controls::BaseTypes
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///
	/// </summary>
	class LinearSlider
		: public juce::Slider
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
	
		LinearSlider(
			juce::String _labelText,
			juce::String _unitSuffix,
			const float _rangeMin,
			const float _rangeMax,
			const float _rangeInterval,
			const float _defaultValue,
			juce::LookAndFeel* _lookAndFeel);
		~LinearSlider();

		virtual void paint(juce::Graphics& _graphics) override;

	private: /////////////////////////////////////////////////////////////////////////////////////////
		
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinearSlider);
	};
}