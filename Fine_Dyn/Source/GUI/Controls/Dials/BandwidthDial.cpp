#include "BandwidthDial.h"
#include "../../LookAndFeels/CustomLookAndFeel.h"
using namespace GUI::Controls::Dials;

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor for the bandwidth dial.
/// </summary>
/// <param name="_labelText">The text that will appear in the slider's Label</param>
/// <param name="_xPos">The X Position of the Dial on the Grid</param>
/// <param name="_yPos">The Y Position of the Dial on the Grid</param>
/// <param name="_parameterID">The ID linking the Dial to it's associated Parameter (See Parameters.h)</param>
/// <param name="_lookAndFeel">The LookAndFeel of the Dial</param>
BandwidthDial::BandwidthDial
(
	const float _rangeMin,
	const float _rangeMax,
	const float _rangeInterval,
	const float _defaultValue,
	juce::LookAndFeel* _lookAndFeel
)
	: BaseTypes::RotaryDial(
		juce::String("Bandwidth"),
		juce::String(""),
		_rangeMin, 
		_rangeMax,
		_rangeInterval, 
		_defaultValue,
		_lookAndFeel)
{
	// Only specific settings for BandwidthDial controls go here
	this->setNumDecimalPlacesToDisplay(1);
	this->setSkewFactorFromMidPoint(1.0f);
}

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor for the bandwidth dial.
/// </summary>
BandwidthDial::~BandwidthDial()
{
}

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Handles the drawing of the dial
/// </summary>
/// <param name="g">The Graphics unit to be used to draw the dial</param>
void BandwidthDial::paint(juce::Graphics& g)
{
	BaseTypes::RotaryDial::paint(g);

}