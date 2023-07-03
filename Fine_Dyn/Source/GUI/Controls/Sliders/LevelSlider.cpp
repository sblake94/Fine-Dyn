#include "LevelSlider.h"

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
GUI::Controls::Sliders::LevelSlider::LevelSlider
(
	const float _rangeMin, 
	const float _rangeMax, 
	const float _rangeInterval, 
	const float _defaultValue, 
	juce::String _labelText, 
	const int _xPos, 
	const int _yPos, 
	const int _width, 
	const int _height, 
	const int _paramID, 
	const bool _isVertical,
	juce::LookAndFeel* _lookAndFeel
)
	: GUI::Controls::BaseTypes::LinearSlider(
		_rangeMin,
		_rangeMax,
		_rangeInterval,
		_defaultValue,
		_labelText,
		" dB",
		_xPos,
		_yPos,
		_width,
		_height,
		_paramID,
		_lookAndFeel)
{
}

////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
GUI::Controls::Sliders::LevelSlider::~LevelSlider()
{
}

////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Paints the GainDBSlider
/// </summary>
/// <param name="_graphics"></param>
void GUI::Controls::Sliders::LevelSlider::paint(juce::Graphics& _graphics)
{
	LinearSlider::paint(_graphics);
}
