#include "StaticLabel.h"

#include "../../../GUI/LookAndFeels/CustomLookAndFeel.h"

GUI::Controls::Labels::StaticLabel::StaticLabel
(
	juce::String _labelText,
	const int _xPos, 
	const int _yPos, 
	const int _width, 
	const int _height, 
	const int _paramID,
	const juce::Colour _textColour,
	juce::LookAndFeel* _lookAndFeel
)
	: CustomLabel(
		_labelText,
		_xPos,
		_yPos,
		_width,
		_height,
		juce::Font(12.0f),
		_textColour,
		1,
		_paramID,
		_lookAndFeel
	)
{
	
}

GUI::Controls::Labels::StaticLabel::~StaticLabel()
{
}

void GUI::Controls::Labels::StaticLabel::paint(juce::Graphics& g)
{
	GUI::Controls::BaseTypes::CustomLabel::paint(g);
}
