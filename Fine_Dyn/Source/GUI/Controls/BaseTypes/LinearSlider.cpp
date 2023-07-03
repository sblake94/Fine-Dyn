#include "LinearSlider.h"
#include "../../../DSP/Parameters.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
/// <param name="_rangeMin"></param>
/// <param name="_rangeMax"></param>
/// <param name="_rangeInterval"></param>
/// <param name="_defaultValue"></param>
/// <param name="_labelText"></param>
/// <param name="_unitSuffix"></param>
/// <param name="_xPos"></param>
/// <param name="_yPos"></param>
/// <param name="_width"></param>
/// <param name="_height"></param>
/// <param name="_paramID"></param>
/// <param name="_lookAndFeel"></param>
GUI::Controls::BaseTypes::LinearSlider::LinearSlider
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
	float value = DSP::Parameters::GetSliderParams().at(_paramID)->get();
	this->setValue(value);

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
	this->setSliderStyle(juce::Slider::LinearVertical);

	// Look and Feel
	if (_lookAndFeel != nullptr)
		this->setLookAndFeel(_lookAndFeel);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
GUI::Controls::BaseTypes::LinearSlider::~LinearSlider()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Paints the LinearSlider
/// </summary>
void GUI::Controls::BaseTypes::LinearSlider::paint(juce::Graphics& _graphics)
{
	juce::Slider::paint(_graphics);
}
