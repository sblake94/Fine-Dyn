#include "TitleLabel.h"

#include "../../CustomLookAndFeel.h"

GUI::Controls::Labels::TitleLabel::TitleLabel
(
	juce::String _labelText,
	const int _xPos, 
	const int _yPos, 
	const int _width, 
	const int _height, 
	const int _parameterID,
	const juce::Colour _textColour,
	juce::LookAndFeel* _lookAndFeel
)
	: BaseTypes::CustomLabel(
		_labelText,
		_xPos,
		_yPos,
		_width,
		_height,
		GUI::CustomLookAndFeel::s_titleFont,
		_textColour,
		2,
		_parameterID,
		_lookAndFeel)
{
}

GUI::Controls::Labels::TitleLabel::~TitleLabel()
{
}

void GUI::Controls::Labels::TitleLabel::paint(juce::Graphics& g)
{
	BaseTypes::CustomLabel::paint(g);
}
