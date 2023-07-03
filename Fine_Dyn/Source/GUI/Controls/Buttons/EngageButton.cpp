#include "EngageButton.h"

using namespace GUI::Controls::Buttons;

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
/// <param name="_parameterID"></param>
/// <param name="_lookAndFeel"></param>
/// <param name="_labelText"></param>
/// <param name="_xPos"></param>
/// <param name="_yPos"></param>
/// <param name="_isEngaged"></param>
EngageButton::EngageButton
(
	juce::String _labelText,
	const int _xPos,
	const int _yPos,
	const int _width,
	const int _height,
	const int _parameterID,
	bool _isEngaged,
	juce::LookAndFeel* _lookAndFeel
)
	: BaseTypes::LatchButton(
		_labelText,
		_xPos,
		_yPos,
		_width,
		_height,
		_isEngaged,
		_parameterID,
		_lookAndFeel)
{
}
/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
EngageButton::~EngageButton()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Paints the button
/// </summary>
/// <param name="g"></param>
void EngageButton::paint(juce::Graphics& g)
{
	BaseTypes::LatchButton::paint(g);
}