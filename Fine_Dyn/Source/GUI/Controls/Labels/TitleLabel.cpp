#include "TitleLabel.h"

#include "../../LookAndFeels/CustomLookAndFeel.h"

GUI::Controls::Labels::TitleLabel::TitleLabel
(
	juce::String _labelText,
	const juce::Colour _textColour,
	juce::LookAndFeel* _lookAndFeel
)
	: BaseTypes::CustomLabel(
		_labelText,
		GUI::LookAndFeels::CustomLookAndFeel::s_titleFont,
		_textColour,
		2,
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
