#include "CustomLabel.h"

#include "CustomControlBase.h"
#include "../../CustomLookAndFeel.h"

GUI::Controls::BaseTypes::CustomLabel::CustomLabel
(
	juce::String _labelText,
	const int _xPos, 
	const int _yPos, 
	const int _width, 
	const int _height, 
	const juce::Font _font,
	const juce::Colour _textColour,
	const int _maxLines,
	const int _parameterID, 
	juce::LookAndFeel* _lookAndFeel
)
	: juce::Label(_labelText)
	, BaseTypes::CustomControlBase(
		_labelText,
		_xPos,
		_yPos,
		_width,
		_height,
		_parameterID
	)
	, m_labelText(_labelText)
	, m_textColour(_textColour)
	, m_font(_font)
	, m_maxLines(_maxLines)
{

}

GUI::Controls::BaseTypes::CustomLabel::~CustomLabel()
{
}

void GUI::Controls::BaseTypes::CustomLabel::paint(juce::Graphics& g)
{
	juce::Label::paint(g);

	const juce::Rectangle<int> bounds = getLocalBounds().reduced(GUI::CustomLookAndFeel::s_controlBoundsMargin);

	g.setColour(m_textColour);
	g.setFont(m_font);
	g.drawFittedText(m_labelText, bounds.reduced(GUI::CustomLookAndFeel::s_controlBoundsMargin), juce::Justification::centred, m_maxLines);
}
