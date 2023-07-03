/*
	==========================================================================================

	@Author : SBlake
	This class simply draws the background of the GUI
	This allows us to contain future fancy logic for making the background reactive

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace GUI
{
	////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// This class simply draws the background of the GUI
	/// This allows us to contain future fancy logic for making the background reactive
	/// </summary>
	class Background
		: public juce::Component
	{
	public: ////////////////////////////////////////////////////////////////////////////////////////////

		Background();
		~Background();

		void paint(juce::Graphics& g, int width, int height);

	private: ////////////////////////////////////////////////////////////////////////////////////////////
		const juce::Colour m_backgroundColourA = juce::Colour::fromRGB(51, 51, 51);
		const juce::Colour m_backgroundColourB = juce::Colour::fromRGB(34, 34, 34);
	};
}