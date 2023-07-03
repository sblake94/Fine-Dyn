#pragma once

#include <JuceHeader.h>

namespace GUI
{
	////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// A custom look and feel for the GUI. 
	/// </summary>
	class CustomLookAndFeel
		: public juce::LookAndFeel_V4
	{
	public: ////////////////////////////////////////////////////////////////////////////////////////////////

		CustomLookAndFeel();
		~CustomLookAndFeel();

		void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, 
			float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, 
			juce::Slider&) override;

		void drawToggleButton(juce::Graphics& g, juce::ToggleButton& button, 
			bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

		static juce::Colour Lighten(juce::Colour _col);
		static juce::Colour Darken(juce::Colour _col);

		static const juce::Colour s_shadowColour;
		static const juce::Colour s_colour_burningOrange;
		static const juce::Colour s_colour_dustyOrange;
		static const juce::Colour s_colour_cyan;
		static const juce::Colour s_textColourBright;
		static const juce::Colour s_textColourBrightT;
		static const juce::Colour s_textColourDark;
		static const juce::Colour s_textColourDarkT;
		static const juce::Colour s_fillColorA;
		static const juce::Colour s_fillColorB;

		static const juce::Font s_labelFont;
		static const juce::Font s_titleFont;

		static const juce::DropShadow s_dialShadow;
		static const juce::DropShadow s_buttonShadow;

		static const juce::DropShadow s_panelShadow;
		
		static const float s_cornerRadius;
		static const float s_dialIndicatorThickness;
		static const float s_outlineThickness;
		static const float s_controlBoundsMargin;
		
		static const bool s_useDropShadows;

		static const juce::ColourGradient BackgroundGradient(
			juce::Point<float> _innerPoint, juce::Point<float> _outerPoint);

	private:////////////////////////////////////////////////////////////////////////////////////////////////
	};
}


