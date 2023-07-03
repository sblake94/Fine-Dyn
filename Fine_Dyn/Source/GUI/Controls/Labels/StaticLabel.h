#pragma once

#include <JuceHeader.h>
#include "../BaseTypes/CustomLabel.h"

namespace GUI::Controls::Labels
{
	// a class that inherits from juce::Label
	class StaticLabel
		: public GUI::Controls::BaseTypes::CustomLabel
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		StaticLabel(
			juce::String _labelText,
			const int _xPos,
			const int _yPos,
			const int _width,
			const int _height,
			const int _parameterID,
			const juce::Colour _textColour,
			juce::LookAndFeel* _lookAndFeel = nullptr);
		~StaticLabel();

		void paint(juce::Graphics& g) override;

	private ://///////////////////////////////////////////////////////////////////////////////////////
		
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StaticLabel);
	};
}