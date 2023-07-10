#include "ThresholdSlider.h"

////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// 
/// </summary>
/// <param name="_rangeMin"></param>
/// <param name="_rangeMax"></param>
/// <param name="_rangeInterval"></param>
/// <param name="_defaultValue"></param>
/// <param name="_labelText"></param>
/// <param name="_xPos"></param>
/// <param name="_yPos"></param>
/// <param name="_width"></param>
/// <param name="_height"></param>
/// <param name="_paramID"></param>
/// <param name="_isVertical"></param>
/// <param name="_lookAndFeel"></param>
GUI::Controls::Sliders::ThresholdSlider::ThresholdSlider
(
	const float _rangeMin, 
	const float _rangeMax, 
	const float _rangeInterval, 
	const float _defaultValue, 
	const bool _isVertical,
	juce::LookAndFeel* _lookAndFeel
)
	: GUI::Controls::BaseTypes::LinearSlider(
		juce::String("Threshold"),
		juce::String(" dB"),
		_rangeMin,
		_rangeMax,
		_rangeInterval,
		_defaultValue,
		_lookAndFeel)
{
}

////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
GUI::Controls::Sliders::ThresholdSlider::~ThresholdSlider()
{
}

////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Paints the GainDBSlider
/// </summary>
/// <param name="_graphics"></param>
void GUI::Controls::Sliders::ThresholdSlider::paint(juce::Graphics& _graphics)
{
	LinearSlider::paint(_graphics);
}
