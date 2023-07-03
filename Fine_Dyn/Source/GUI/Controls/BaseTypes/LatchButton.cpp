#include "LatchButton.h"
#include "../../../DSP/Parameters.h"

using namespace GUI::Controls::BaseTypes;

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// A base class for a button that can be latched on or off. Can also be instantiated itself
/// </summary>
/// <param name="_labelText">The text to display on the button</param>
/// <param name="_xPos">The x position of the button</param>
/// <param name="_yPos">The y position of the button</param>
/// <param name="_isLatched">Whether the button is latched on or off</param>
/// <param name="_parameterID">The ID of the parameter that the button controls</param>
/// <param name="_lookAndFeel">The look and feel to use for the button</param>
LatchButton::LatchButton
(
	juce::String _labelText,
	const int _xPos,
	const int _yPos,
	const int _width,
	const int _height,
	const bool _isLatched,
	const int _paramID,
	juce::LookAndFeel* _lookAndFeel
)
	: juce::ToggleButton()
	, CustomControlBase(
		_labelText, 
		_xPos, 
		_yPos,
		_width,
		_height,
		_paramID)
{
	// Get the value of the parameter from the processor
	try
	{
		const bool state = DSP::Parameters::GetBoolParams().at(_paramID)->get();
		this->setState(state ? juce::Button::buttonDown : juce::Button::buttonNormal);
	}
	catch (const std::exception& e)
	{
		DBG(e.what());
	}

	this->setButtonText(_labelText);
	this->setComponentID(_labelText);
	this->setToggleState(_isLatched, juce::sendNotification);

	if (_lookAndFeel != nullptr)
		this->setLookAndFeel(_lookAndFeel);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
LatchButton::~LatchButton()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Paints the button
/// </summary>
/// <param name="g">The graphics context to paint to</param>
void LatchButton::paint(juce::Graphics& g)
{
	juce::ToggleButton::paint(g);
}