#include "GainDial.h"

using namespace GUI::Controls::Dials;

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor for the GainDial class.
/// </summary>
/// <param name="_labelText">The text that will appear in the slider's Label</param>
/// <param name="_xPos">The X Position of the Dial on the Grid</param>
/// <param name="_yPos">The Y Position of the Dial on the Grid</param>
/// <param name="_parameterID">The ID linking the Dial to it's associated Parameter (See Parameters.h)</param>
/// <param name="_lookAndFeel">The LookAndFeel of the Dial</param>
GainDial::GainDial
(
	const float _rangeMin,
	const float _rangeMax,
	const float _rangeInterval,
	const float _defaultValue,
	juce::LookAndFeel* _lookAndFeel
)
	: BaseTypes::RotaryDial(
		juce::String("Gain"),
		juce::String(" dB"),
		_rangeMin,
		_rangeMax,
		_rangeInterval,
		_defaultValue,
		_lookAndFeel
	)
{
	// Only specific settings for GainDial controls go here
	this->setNumDecimalPlacesToDisplay(2);
}

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor for the GainDial class.
/// </summary>
GainDial::~GainDial()
{
}

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the position of the GainDial on the Grid.
/// </summary>
/// <param name="g">The Graphics unit to be used to draw the dial</param>
void GainDial::paint(juce::Graphics& g)
{
	BaseTypes::RotaryDial::paint(g);
}
