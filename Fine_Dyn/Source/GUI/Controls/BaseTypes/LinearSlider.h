#pragma once

#include <JuceHeader.h>

#include "CustomControlBase.h"

namespace GUI::Controls::BaseTypes
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///
	/// </summary>
	class LinearSlider
		: public juce::Slider
		, public CustomControlBase
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
	
		LinearSlider(
			const float _rangeMin,
			const float _rangeMax,
			const float _rangeInterval,
			const float _defaultValue,
			juce::String _labelText,
			juce::String _unitSuffix,
			const int _xPos,
			const int _yPos,
			const int _width,
			const int _height,
			const int _paramID,
			juce::LookAndFeel* _lookAndFeel);
		~LinearSlider();

		virtual void paint(juce::Graphics& _graphics) override;

	private: /////////////////////////////////////////////////////////////////////////////////////////
		
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LinearSlider);
	};
}