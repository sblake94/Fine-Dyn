#include "CustomLookAndFeel.h"

// There is probably an inbuilt way to do this in JUCE, but I haven't found it yet.
const juce::Colour GUI::CustomLookAndFeel::s_shadowColour			= juce::Colour::fromRGBA(000u,	000u,	000u,	150u);
const juce::Colour GUI::CustomLookAndFeel::s_colour_burningOrange	= juce::Colour::fromRGBA(255u,	75u,	0u,		255u);
const juce::Colour GUI::CustomLookAndFeel::s_colour_dustyOrange		= juce::Colour::fromRGBA(153u,	051u,	000u,	255u);
const juce::Colour GUI::CustomLookAndFeel::s_colour_cyan			= juce::Colour::fromRGBA(000u,	204u,	255u,	255u);
const juce::Colour GUI::CustomLookAndFeel::s_fillColorA				= juce::Colour::fromRGBA(051u,	051u,	051u,	255u);
const juce::Colour GUI::CustomLookAndFeel::s_fillColorB				= juce::Colour::fromRGBA(034u,	034u,	034u,	255u);

const juce::Colour GUI::CustomLookAndFeel::s_textColourBright		= juce::Colour::fromRGBA(255u,	255u,	255u,	255u);
const juce::Colour GUI::CustomLookAndFeel::s_textColourBrightT		= juce::Colour::fromRGBA(255u,	255u,	255u,	125u);
const juce::Colour GUI::CustomLookAndFeel::s_textColourDark			= juce::Colour::fromRGBA(000u,	000u,	000u,	255u);
const juce::Colour GUI::CustomLookAndFeel::s_textColourDarkT		= juce::Colour::fromRGBA(000u,	000u,	000u,	125u);

const juce::Font   GUI::CustomLookAndFeel::s_labelFont = juce::Font("Montserrat", 16, juce::Font::plain);
const juce::Font   GUI::CustomLookAndFeel::s_titleFont = juce::Font("Devil Breeze", 48, juce::Font::bold);

const float GUI::CustomLookAndFeel::s_cornerRadius = 7.0f;
const float GUI::CustomLookAndFeel::s_dialIndicatorThickness = 2.0f; 
const float GUI::CustomLookAndFeel::s_outlineThickness = 2.0f;
const float GUI::CustomLookAndFeel::s_controlBoundsMargin = 5.0f;

const juce::DropShadow GUI::CustomLookAndFeel::s_dialShadow = juce::DropShadow(
		GUI::CustomLookAndFeel::s_shadowColour, 16, juce::Point<int>(9, 9));

const juce::DropShadow GUI::CustomLookAndFeel::s_buttonShadow = juce::DropShadow(
		GUI::CustomLookAndFeel::s_shadowColour, 1, juce::Point<int>(0, 0));

const juce::DropShadow GUI::CustomLookAndFeel::s_panelShadow = juce::DropShadow(
		GUI::CustomLookAndFeel::s_shadowColour, 16, juce::Point<int>(9, 9));

const bool GUI::CustomLookAndFeel::s_useDropShadows = true;


/////////////////////////////////////////////////
/// <summary>
/// Constructor for the custom look and feel
/// </summary>
GUI::CustomLookAndFeel::CustomLookAndFeel()
{
}

/////////////////////////////////////////////////
/// <summary>
/// Destructor for the custom look and feel
/// </summary>
GUI::CustomLookAndFeel::~CustomLookAndFeel()
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
void GUI::CustomLookAndFeel::drawRotarySlider
(
	juce::Graphics& g, 
	int x, 
	int y, 
	int width, 
	int height, 
	float sliderPos, 
	const float rotaryStartAngle, 
	const float rotaryEndAngle, 
	juce::Slider& slider
)
{
	auto bounds = slider.getLocalBounds().reduced(GUI::CustomLookAndFeel::s_controlBoundsMargin);

	float sliderDefaultPos = 0;

	auto currentAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	auto restingPointAngle = rotaryStartAngle + sliderDefaultPos * (rotaryEndAngle - rotaryStartAngle);

	// draw the pie
	juce::Path piePath;

	// get a perfect square that fits in bounds
	auto pieBounds = bounds.withSizeKeepingCentre(
		juce::jmin(bounds.getWidth(), bounds.getHeight()), 
		juce::jmin(bounds.getWidth(), bounds.getHeight()))
		.reduced(15.0f);
		
	piePath.addPieSegment(pieBounds.toFloat(), rotaryStartAngle, currentAngle, 0.0f);
	g.setColour(GUI::CustomLookAndFeel::s_colour_burningOrange);
	g.fillPath(piePath);

	piePath.clear();
	g.setColour(GUI::CustomLookAndFeel::s_shadowColour);
	piePath.addPieSegment(pieBounds.toFloat(), currentAngle, rotaryEndAngle, 0.0f);
	g.fillPath(piePath);

	bounds.reduce(GUI::CustomLookAndFeel::s_controlBoundsMargin, GUI::CustomLookAndFeel::s_controlBoundsMargin);

	auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 3.5f;
	auto centreX = bounds.getCentreX();
	auto centreY = bounds.getCentreY();
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0f;

	juce::Path dialPath;
	dialPath.addEllipse(rx, ry, rw, rw);

	if (s_useDropShadows)
	{
		// draw a drop shadow for the dial, originating from the top left corner
		s_dialShadow.drawForPath(g, dialPath);
	}

	// fill
	juce::ColourGradient gradFill = BackgroundGradient(juce::Point<float>(rx, ry), bounds.getBottomRight().toFloat());
	g.setGradientFill(gradFill);
	g.fillEllipse(rx, ry, rw, rw);

	// indicator
	juce::Path p;
	auto pointerLength = radius * 0.33f;
	// lotta magic numbers here, let's do better
	p.addRoundedRectangle(-s_dialIndicatorThickness * 0.5f, -radius, s_dialIndicatorThickness, 10.0f, 2.0f);
	p.applyTransform(juce::AffineTransform::rotation(currentAngle).translated(centreX, centreY));

	g.setColour(s_colour_burningOrange);
	g.fillPath(p);

	// outline
	g.setColour(s_shadowColour);
	g.drawEllipse(rx, ry, rw, rw, s_outlineThickness);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void GUI::CustomLookAndFeel::drawToggleButton
(
	juce::Graphics& g, 
	juce::ToggleButton& button, 
	bool shouldDrawButtonAsHighlighted, 
	bool shouldDrawButtonAsDown
)
{
	// draw the background behind the button text
	const juce::Rectangle<int> buttonArea = button.getLocalBounds().reduced(s_controlBoundsMargin * 3, s_controlBoundsMargin);
	juce::Path buttonPath;
	buttonPath.addRoundedRectangle(buttonArea.toFloat(), s_cornerRadius);
	

	// Shadow for the button
	if (s_useDropShadows)
	{
		buttonPath.addRoundedRectangle(buttonArea.toFloat(), s_cornerRadius);
		s_buttonShadow.drawForPath(g, buttonPath);
	}

	// Draw the button itself
	const juce::ColourGradient gradFill = 
		juce::ColourGradient(
			s_fillColorA,
			buttonArea.getTopLeft().toFloat(),
			s_fillColorB,
			buttonArea.getBottomRight().toFloat(),
			true);

	g.setGradientFill(gradFill);
	g.fillPath(buttonPath);

	// draw the border around the button
	const bool buttonState = button.getToggleState();
	g.setColour(buttonState ? s_colour_burningOrange : s_shadowColour);
	g.drawRoundedRectangle(buttonArea.toFloat().reduced(s_outlineThickness / 3.33f), s_cornerRadius, s_outlineThickness);

	// Draw the text in the button
	const juce::String buttonText = button.getButtonText();
	g.setColour(s_textColourBright);
	g.setFont(s_labelFont);
	g.drawFittedText(buttonText, buttonArea, juce::Justification::centred, 2);
}

juce::Colour GUI::CustomLookAndFeel::Lighten(juce::Colour _col)
{
	auto H = _col.getHue();
	auto S = juce::jmax(0.0f, _col.getSaturation() - 0.05f);
	auto L = juce::jmin(1.0f, _col.getLightness() * 1.5f);

	return juce::Colour::fromHSL(H, S, L, 1.0f);
}

juce::Colour GUI::CustomLookAndFeel::Darken(juce::Colour _col)
{
	auto H = _col.getHue();
	auto S = juce::jmin(1.0f, _col.getSaturation() + 0.05f);
	auto L = juce::jmax(0.0f, _col.getLightness() / 1.5f);

	return juce::Colour::fromHSL(H, S, L, 1.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Draws the background of all Components
/// </summary>
/// <param name="_innerPoint">The point where the gradient starts</param>
/// <param name="_outerPoint">The point where the gradient ends</param>
const juce::ColourGradient GUI::CustomLookAndFeel::BackgroundGradient
(
	juce::Point<float> _innerPoint, 
	juce::Point<float> _outerPoint
)
{
	return juce::ColourGradient(
		s_fillColorA,
		_innerPoint,
		s_fillColorB,
		_outerPoint,
		true);
}