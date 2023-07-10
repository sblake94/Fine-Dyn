#pragma once

#include <JuceHeader.h>

namespace GUI::Controls::BaseTypes
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A base class for a button that can be latched on or off. Can also be instantiated itself
	/// </summary>
	class LatchButton
		: public juce::ToggleButton
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		LatchButton(
			juce::String _labelText,
			const bool _isLatched,
			juce::LookAndFeel* _lookAndFeel = nullptr);
		~LatchButton();

		void paint(juce::Graphics& g) override;

	private://///////////////////////////////////////////////////////////////////////////////////////
		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const int m_labelFontSize = 18;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LatchButton);
	};
}