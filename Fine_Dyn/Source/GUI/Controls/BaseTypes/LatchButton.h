#pragma once

#include <JuceHeader.h>
#include "../BaseTypes/CustomControlBase.h"

namespace GUI::Controls::BaseTypes
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A base class for a button that can be latched on or off. Can also be instantiated itself
	/// </summary>
	class LatchButton
		: public juce::ToggleButton
		, public CustomControlBase
	{
	public: /////////////////////////////////////////////////////////////////////////////////////////
		LatchButton(
			juce::String _labelText,
			const int _xPos,
			const int _yPos,
			const int _width,
			const int _height,
			const bool _isLatched,
			const int _parameterID,
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