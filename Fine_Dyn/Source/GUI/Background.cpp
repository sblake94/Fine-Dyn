#include "Background.h"

#include "LookAndFeels/CustomLookAndFeel.h"

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
	g.setColour(GUI::LookAndFeels::CustomLookAndFeel::s_fillColorA);

	g.fillRect(0, 0, width, height);
}