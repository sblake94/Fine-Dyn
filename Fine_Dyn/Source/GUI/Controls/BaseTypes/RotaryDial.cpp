#include "RotaryDial.h"
#include "../../CustomLookAndFeel.h"
#include "../../../Processing/Parameters.h"

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
	const float _rangeMin,
	const float _rangeMax,
	const float _rangeInterval,
	const float _defaultValue,
	juce::String _labelText,
	juce::String _unitSuffix,
	const int _xPos,
	const int _yPos,
	const int _width,
	const int _height,
	const int _paramID,
	juce::LookAndFeel* _lookAndFeel
)
	: juce::Slider()
	, CustomControlBase(
		_labelText, 
		_xPos, 
		_yPos, 
		_width, 
		_height, 
		_paramID)
{

	float value = Processing::Parameters::GetSliderParams().at(_paramID)->get();
	this->setValue(value);


	// Slider Properties
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
	auto bounds = getLocalBounds();

	// draw a Label at the top of the dial
	g.setColour(GUI::CustomLookAndFeel::s_textColourBrightT);
	g.setFont(GUI::CustomLookAndFeel::s_labelFont);
	
	g.drawText(m_labelText, 0, 0, bounds.getWidth(), m_textBoxHeight, juce::Justification::centred, true);

	// Value text
	g.setColour(GUI::CustomLookAndFeel::s_textColourBrightT);
	static char buffer[16];
	std::snprintf(buffer, sizeof(buffer), "%.2f", getValue());
	const juce::String text = juce::String(buffer) + juce::String(getTextValueSuffix());

	g.drawText(text, bounds.reduced(GUI::CustomLookAndFeel::s_controlBoundsMargin), 
		juce::Justification::centredBottom,
		true);

	juce::Slider::paint(g);
}
