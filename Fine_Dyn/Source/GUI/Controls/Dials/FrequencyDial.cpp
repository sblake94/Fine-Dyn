#include "FrequencyDial.h"

using namespace GUI::Controls::Dials;

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor for the FrequencyDial class.
/// </summary>
/// <param name="_labelText">The text that will appear in the slider's Label</param>
/// <param name="_xPos">The X Position of the Dial on the Grid</param>
/// <param name="_yPos">The Y Position of the Dial on the Grid</param>
/// <param name="_parameterID">The ID linking the Dial to it's associated Parameter (See Parameters.h)</param>
/// <param name="_lookAndFeel">The LookAndFeel of the Dial</param>
FrequencyDial::FrequencyDial
(
	juce::String _labelText,
	const int _xPos,
	const int _yPos,
	const int _width,
	const int _height,
	const int _parameterID,
	const float _defaultValue,
	const float _rangeMin,
	const float _rangeMax,
	const float _rangeInterval,
	juce::LookAndFeel* _lookAndFeel
)
	: BaseTypes::RotaryDial(
		_rangeMin,
		_rangeMax,
		0.0f,
		_defaultValue,
		_labelText,
		" hz",
		_xPos,
		_yPos,
		_width,
		_height,
		_parameterID,
		_lookAndFeel)
{
	// Only specific settings for FrequencyDial controls go here
	this->setSkewFactor(0.29f);
	this->setNumDecimalPlacesToDisplay(0);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor for the FrequencyDial class.
/// </summary>
FrequencyDial::~FrequencyDial()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Handles the drawing of the dial
/// </summary>
/// <param name="g">The Graphics unit to be used to draw the dial</param>
void FrequencyDial::paint(juce::Graphics& g)
{
	BaseTypes::RotaryDial::paint(g);

	const int sliderTop = m_textBoxHeight;
	const juce::Rectangle<int> sliderBounds(getLocalBounds().removeFromTop(getHeight() - 2 * m_textBoxHeight));

}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the ID of the parameter that the dial is linked to.
/// </summary>
/// <param name="_parameterID"></param>
void FrequencyDial::SetParameterID(const juce::ParameterID _parameterID)
{
	this->m_parameterID = _parameterID;
}
