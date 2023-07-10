#pragma once

#include <JuceHeader.h>
#include "../BaseTypes/CustomLabel.h"

namespace GUI::Controls::Labels
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A label for displaying large text
	/// </summary>
	class TitleLabel
		: public GUI::Controls::BaseTypes::CustomLabel
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////

		TitleLabel(
			juce::String _labelText,
			const juce::Colour _textColour,
			juce::LookAndFeel* _lookAndFeel = nullptr);
		~TitleLabel();

		void paint(juce::Graphics& g) override;

	private: /////////////////////////////////////////////////////////////////////////////////////////

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TitleLabel);
	};
}