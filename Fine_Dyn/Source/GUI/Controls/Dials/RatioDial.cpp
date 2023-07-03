#include "RatioDial.h"
#include "../../LookAndFeels/CustomLookAndFeel.h"
using namespace GUI::Controls::Dials;

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor for the ratio dial.
/// </summary>
/// <param name="_labelText">The text that will appear in the slider's Label</param>
/// <param name="_xPos">The X Position of the Dial on the Grid</param>
/// <param name="_yPos">The Y Position of the Dial on the Grid</param>
/// <param name="_parameterID">The ID linking the Dial to it's associated Parameter (See Parameters.h)</param>
/// <param name="_lookAndFeel">The LookAndFeel of the Dial</param>
RatioDial::RatioDial
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
		_rangeInterval,
		_defaultValue,
		_labelText,
		" : 1",
		_xPos,
		_yPos,
		_width,
		_height,
		_parameterID,
		_lookAndFeel)
{
	this->setNumDecimalPlacesToDisplay(2);
	this->setSkewFactorFromMidPoint(2.0f);
}

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor for the bandwidth dial.
/// </summary>
RatioDial::~RatioDial()
{
}

/////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Handles the drawing of the dial
/// </summary>
/// <param name="g">The Graphics unit to be used to draw the dial</param>
void RatioDial::paint(juce::Graphics& g)
{
	BaseTypes::RotaryDial::paint(g);

}