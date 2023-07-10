#pragma once

#include <JuceHeader.h>

namespace GUI::Controls::BaseTypes
{
	class CustomLabel
		: public juce::Label
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////

		CustomLabel(
			const juce::String _labelText,
			const juce::Font _font,
			const juce::Colour _textColour,
			const int _maxLines,
			juce::LookAndFeel* _lookAndFeel = nullptr);
		~CustomLabel();

		void paint(juce::Graphics& g) override;

		const int m_maxLines;

	private: /////////////////////////////////////////////////////////////////////////////////////////

		juce::String m_labelText;
		const juce::Colour m_textColour;
		const int m_textBoxHeight = 12;
		const int m_textBoxWidth = 50;
		const juce::Font m_font;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLabel);
	};
}