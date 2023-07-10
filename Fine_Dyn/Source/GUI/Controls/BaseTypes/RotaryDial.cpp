#include "RotaryDial.h"
#include "../../LookAndFeels/CustomLookAndFeel.h"
#include "../../../DSP/Parameters.h"

using namespace GUI::Controls::BaseTypes;
/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
/// <param name="_rangeMin">The minimum value of the slider</param>
/// <param name="_rangeMax">The maximum value of the slider</param>
/// <param name="_rangeInterval">The interval between values of the slider</param>
/// <param name="_defaultValue">The default value of the slider</param>
/// <param name="_labelText">The text that will appear in the slider's Label</param>
/// <param name="_xPos">The X Position of the Dial on the Grid</param>
/// <param name="_yPos">The Y Position of the Dial on the Grid</param>
/// <param name="_paramID">The ID linking the Dial to it's associated Parameter (See Parameters.h)</param>
/// <param name="_lookAndFeel">The LookAndFeel of the Dial</param>
RotaryDial::RotaryDial
(
	juce::String _labelText,
	juce::String _unitSuffix,
	const float _rangeMin,
	const float _rangeMax,
	const float _rangeInterval,
	const float _defaultValue,
	juce::LookAndFeel* _lookAndFeel
)
	: juce::Slider()
{
	// Slider Properties
	this->setName(_labelText);
	this->setComponentID(_labelText);
	this->setRange(_rangeMin, _rangeMax, _rangeInterval);

	// Text box
	this->setTooltip(_labelText);
	this->setTextBoxIsEditable(true);
	this->setTextValueSuffix(_unitSuffix);
	this->setTextBoxStyle(NoTextBox, false, 0, 0);

	// Interactions
	this->setDoubleClickReturnValue(true, _defaultValue);
	this->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);

	// Look and Feel
	if(_lookAndFeel != nullptr)
		this->setLookAndFeel(_lookAndFeel);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
RotaryDial::~RotaryDial()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Handles the drawing of the dial
///	</summary>
/// <param name="g">The Graphics unit to be used to draw the dial</param>
void RotaryDial::paint(juce::Graphics& g)
{
	juce::Slider::paint(g);
}
