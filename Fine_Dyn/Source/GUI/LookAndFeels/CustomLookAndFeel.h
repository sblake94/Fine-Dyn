#pragma once

#include <JuceHeader.h>

namespace GUI::LookAndFeels
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

		void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
			float sliderPos, float minSliderPos, float maxSliderPos,
			const juce::Slider::SliderStyle style, juce::Slider& slider) override;

		static juce::Colour Lighten(juce::Colour _col);
		static juce::Colour Darken(juce::Colour _col);

		static const juce::Colour s_lightShadowColour; 
		static const juce::Colour s_darkShadowColour;
		static const juce::Colour s_colour_brightAccent;
		static const juce::Colour s_colour_dustyAccent;
		static const juce::Colour s_colour_cyan;
		static const juce::Colour s_textColourBright;
		static const juce::Colour s_textColourBrightT;
		static const juce::Colour s_textColourDark;
		static const juce::Colour s_textColourDarkT;
		static const juce::Colour s_fillColorA;
		static const juce::Colour s_fillColorB;

		static const juce::Font s_labelFont;
		static const juce::Font s_titleFont;

		static const juce::DropShadow s_lightShadow;
		static const juce::DropShadow s_darkShadow;

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


