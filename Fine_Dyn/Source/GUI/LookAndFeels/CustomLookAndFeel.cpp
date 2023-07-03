#include "CustomLookAndFeel.h"

using namespace GUI::LookAndFeels;
using namespace juce;

// There is probably an inbuilt way to do this in JUCE, but I haven't found it yet.
const Colour CustomLookAndFeel::s_lightShadowColour		= Colour::fromRGBA(255u,	255u,	255u,	255u);
const Colour CustomLookAndFeel::s_darkShadowColour		= Colour::fromRGBA(000u,	000u,	000u,	255u);

const Colour CustomLookAndFeel::s_colour_brightAccent		= Colour::fromRGBA(000u,	204u,	255u,	255u);
const Colour CustomLookAndFeel::s_colour_dustyAccent		= Colour::fromRGBA(000u,	051u,	153u,	255u);
const Colour CustomLookAndFeel::s_colour_cyan				= Colour::fromRGBA(000u,	204u,	255u,	255u);
const Colour CustomLookAndFeel::s_fillColorA				= Colour::fromRGBA(050u,	051u,	052u,	255u);
const Colour CustomLookAndFeel::s_fillColorB				= Colour::fromRGBA(033u,	034u,	035u,	255u);

const Colour CustomLookAndFeel::s_textColourBright			= Colour::fromRGBA(255u,	255u,	255u,	255u);
const Colour CustomLookAndFeel::s_textColourBrightT			= Colour::fromRGBA(255u,	255u,	255u,	125u);
const Colour CustomLookAndFeel::s_textColourDark			= Colour::fromRGBA(000u,	000u,	000u,	255u);
const Colour CustomLookAndFeel::s_textColourDarkT			= Colour::fromRGBA(000u,	000u,	000u,	125u);

const Font   CustomLookAndFeel::s_labelFont = Font("Montserrat", 16, Font::plain);
const Font   CustomLookAndFeel::s_titleFont = Font("Devil Breeze", 48, Font::bold);

const float CustomLookAndFeel::s_cornerRadius = 7.0f;
const float CustomLookAndFeel::s_dialIndicatorThickness = 2.0f;
const float CustomLookAndFeel::s_outlineThickness = 2.0f;
const float CustomLookAndFeel::s_controlBoundsMargin = 5.0f;

const DropShadow CustomLookAndFeel::s_lightShadow = DropShadow(
	CustomLookAndFeel::Lighten(s_fillColorA), 8, Point<int>(-5, -5));

const DropShadow CustomLookAndFeel::s_darkShadow = DropShadow(
	CustomLookAndFeel::Darken(s_fillColorA), 8, Point<int>(5, 5));

const DropShadow CustomLookAndFeel::s_panelShadow = DropShadow(
	s_lightShadowColour, 16, Point<int>(9, 9));

const bool CustomLookAndFeel::s_useDropShadows = true;


/////////////////////////////////////////////////
/// <summary>
/// Constructor for the custom look and feel
/// </summary>
CustomLookAndFeel::CustomLookAndFeel()
{
}

/////////////////////////////////////////////////
/// <summary>
/// Destructor for the custom look and feel
/// </summary>
CustomLookAndFeel::~CustomLookAndFeel()
{

}

/////////////////////////////////////////////////
/// <summary>
/// Defines the behaviour for drawing sliders
/// </summary>
/// <param name="g">The Graphics context</param>
/// <param name="x">The X Position of the Slider</param>
/// <param name="y">The Y Position of the Slider</param>
/// <param name="width">The width of the Slider</param>
/// <param name="height">The width of the Slider</param>
/// <param name="sliderPos">The initial position of the Slider</param>
/// <param name="rotaryStartAngle">The start of the rotational track</param>
/// <param name="rotaryEndAngle">The end of the rotational track</param>
/// <param name="slider">The Slider itself</param>
void CustomLookAndFeel::drawRotarySlider
(
	Graphics& g, 
	int x, 
	int y, 
	int width, 
	int height, 
	float sliderPos, 
	const float rotaryStartAngle, 
	const float rotaryEndAngle, 
	Slider& slider
)
{
	auto bounds = slider.getLocalBounds().reduced(s_controlBoundsMargin);

	Path dialBody;
	auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.5f;
	auto centreX = bounds.getCentreX();
	auto centreY = bounds.getCentreY();
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0f;
	auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	float trackthickness = 0.25f;

	// Draw the dial body
	dialBody.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, 1.0f / (trackthickness + 1.0f));
	g.setColour(Lighten(s_fillColorA));
	g.fillPath(dialBody);

	// Draw the dial indicator
	Path dialIndicator;
	dialIndicator.addPieSegment(rx, ry, rw, rw, rotaryStartAngle, angle, 1.0f / (trackthickness + 1.0f));
	g.setColour(s_colour_brightAccent);
	g.fillPath(dialIndicator);

	// Draw the dial name
	g.setColour(s_textColourBrightT);
	g.setFont(s_labelFont);
	g.drawText(slider.getName(), bounds, Justification::centredBottom, true);

	// Draw the dial value
	g.setColour(s_textColourBright);
	g.setFont(s_labelFont);
	g.drawText(slider.getTextFromValue(slider.getValue()), bounds, Justification::centred, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CustomLookAndFeel::drawToggleButton
(
	Graphics& g, 
	ToggleButton& button, 
	bool shouldDrawButtonAsHighlighted, 
	bool shouldDrawButtonAsDown
)
{
	// Draw the button body
	auto bounds = button.getLocalBounds().reduced(s_controlBoundsMargin);

	Path buttonBodyPath;
	Rectangle<float> buttonBody = bounds.reduced(s_controlBoundsMargin).toFloat();
	buttonBodyPath.addRoundedRectangle(buttonBody, s_cornerRadius);
	g.setColour(s_fillColorA);
	g.fillPath(buttonBodyPath);

	// Draw the button indicator
	g.setColour(button.getToggleState() ? s_colour_brightAccent : Lighten(s_fillColorA));
	g.drawRoundedRectangle(buttonBody, s_cornerRadius, s_outlineThickness);

	// Draw the button name
	g.setColour(s_textColourBrightT);
	g.setFont(s_labelFont);
	g.drawText(button.getName(), bounds, Justification::centredBottom, true);

	// Draw the button value
	g.setColour(s_textColourBright);
	g.setFont(s_labelFont);
	g.drawText(button.getButtonText(), bounds, Justification::centred, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CustomLookAndFeel::drawLinearSlider
(
	juce::Graphics& g,
	int x, 
	int y, 
	int width, 
	int height,
	float sliderPos, 
	float minSliderPos, 
	float maxSliderPos,
	const juce::Slider::SliderStyle style, 
	juce::Slider& slider
)
{
	// Draw the vertical slider track
	Rectangle<float> bounds = slider.getLocalBounds().reduced(s_controlBoundsMargin).toFloat();
	Rectangle<float> trackArea = bounds;
	trackArea.setWidth(5.0f);
	trackArea.setHeight(bounds.getHeight() - (3.0f * s_labelFont.getHeight()));
	trackArea.setCentre(bounds.getCentre());

	Colour trackColour = Lighten(s_fillColorA);
	g.setColour(trackColour);
	g.fillRect(trackArea);

	float val = slider.getValue();
	float range = slider.getMaximum() - slider.getMinimum();
	float pos = 1.0f - ((val - slider.getMinimum()) / range);

	// Fill the lower portion of the track to indicate the value
	Rectangle<float> fillArea = trackArea.withTrimmedTop(trackArea.getHeight() * pos);
	g.setColour(s_colour_brightAccent);
	g.fillRect(fillArea);

	// Draw the slider name
	g.setColour(s_textColourBrightT);
	g.setFont(s_labelFont);
	// TODO: MAGIC NUMBERS, PLEASE FIX
	g.drawText(slider.getName(), 
		bounds, 
		Justification::centredBottom, true);


	// Draw the slider value
	g.setColour(s_textColourBright);
	g.setFont(s_labelFont);
	g.drawText(slider.getTextFromValue(
		slider.getValue()), 
		bounds, 
		Justification::centredTop, 
		true);
}

Colour CustomLookAndFeel::Lighten(Colour _col)
{
	auto H = _col.getHue();
	auto S = jmax(0.0f, _col.getSaturation() - 0.05f);
	auto L = jmin(1.0f, _col.getLightness() * 1.5f);

	return Colour::fromHSL(H, S, L, 1.0f);
}

Colour CustomLookAndFeel::Darken(Colour _col)
{
	auto H = _col.getHue();
	auto S = jmin(1.0f, _col.getSaturation() + 0.05f);
	auto L = jmax(0.0f, _col.getLightness() / 1.5f);

	return Colour::fromHSL(H, S, L, 1.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Draws the background of all Components
/// </summary>
/// <param name="_innerPoint">The point where the gradient starts</param>
/// <param name="_outerPoint">The point where the gradient ends</param>
const ColourGradient CustomLookAndFeel::BackgroundGradient
(
	Point<float> _innerPoint, 
	Point<float> _outerPoint
)
{
	return ColourGradient(
		s_fillColorA,
		_innerPoint,
		s_fillColorB,
		_outerPoint,
		true);
}