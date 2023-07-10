#include "CustomLabel.h"

#include "../../LookAndFeels/CustomLookAndFeel.h"

GUI::Controls::BaseTypes::CustomLabel::CustomLabel
(
	const juce::String _labelText,
	const juce::Font _font,
	const juce::Colour _textColour,
	const int _maxLines,
	juce::LookAndFeel* _lookAndFeel
)
	: juce::Label(_labelText)
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

	const juce::Rectangle<int> bounds = getLocalBounds().reduced(GUI::LookAndFeels::CustomLookAndFeel::s_controlBoundsMargin);

	g.setColour(m_textColour);
	g.setFont(m_font);
	g.drawFittedText(m_labelText, bounds.reduced(GUI::LookAndFeels::CustomLookAndFeel::s_controlBoundsMargin), juce::Justification::centred, m_maxLines);
}
