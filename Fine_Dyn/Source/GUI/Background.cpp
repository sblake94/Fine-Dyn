#include "Background.h"

#include "CustomLookAndFeel.h"

////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
GUI::Background::Background()
{
}

////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor of the class
/// </summary>
GUI::Background::~Background()
{
}

////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Paints the background.
/// </summary>
/// <param name="g">: The graphics context that must be used to paint the background.</param>
/// <param name="width">: The width of the background.</param>
/// <param name="height">: The height of the background.</param>
void GUI::Background::paint(juce::Graphics& g, int width, int height)
{
	juce::ColourGradient gradient(
		GUI::CustomLookAndFeel::s_fillColorB,
		0, 0, 
		GUI::CustomLookAndFeel::Darken(GUI::CustomLookAndFeel::s_fillColorB),
		width, height, true);

	g.setGradientFill(gradient);
	g.fillRect(0, 0, width, height);
}