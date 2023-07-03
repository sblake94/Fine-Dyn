#include "ControlManager.h"

#include "../Processing/Parameters.h"
#include "../GUI/CustomLookAndFeel.h"

namespace GUI
{
	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Constructor for the ControlManager class.
	/// </summary>
	/// <param name="_windowWidth">The width of the editor window</param>
	/// <param name="_windowHeight">The height of the editor window</param>
	/// <param name="_lookAndFeelPtr">The custom LookAndFeel to be used when drawing the controls</param>
	ControlManager::ControlManager
	(
		const int _windowWidth,
		const int _windowHeight,
		juce::LookAndFeel* _lookAndFeelPtr
	)
		: m_controlAreaHeight(_windowHeight - 2 * m_margin)
		, m_controlAreaWidth(_windowWidth - 2 * m_margin)

		, m_lowShelfBypass("Low Shelf", 0, 0, 2, 1, Processing::s_lowBandBypassParamID, true, _lookAndFeelPtr)
		, m_midShelfBypass("Mid Shelf", 2, 0, 2, 1, Processing::s_midBandBypassParamID, true, _lookAndFeelPtr)
		, m_highShelfBypass("High Shelf", 4, 0, 2, 1, Processing::s_highBandBypassParamID, true, _lookAndFeelPtr)

		, m_lowFreqSlider("Freq", 0, 1, 2, 2, Processing::s_lowFreqCutoffParamID, 50.0f, 5.0f, 500.0f, 0.01f, _lookAndFeelPtr)
		, m_midFreqSlider("Freq", 2, 1, 2, 2, Processing::s_midFreqCutoffParamID, 1000.0f, 100.0f, 10000.0f, 0.01f, _lookAndFeelPtr)
		, m_highFreqSlider("Freq", 4, 1, 2, 2, Processing::s_highFreqCutoffParamID, 2000.0f, 200.0f, 20000.0f, 0.01f, _lookAndFeelPtr)

		, m_lowGainSlider("Gain", 0, 3, 2, 2, Processing::s_lowGainParamID, 0.0f, -6.0f, 6.0f, 0.0f, _lookAndFeelPtr)
		, m_midGainSlider("Gain", 2, 3, 2, 2, Processing::s_midGainParamID, 0.0f, -6.0f, 6.0f, 0.0f, _lookAndFeelPtr)
		, m_highGainSlider("Gain", 4, 3, 2, 2, Processing::s_highGainParamID, 0.0f, -6.0f, 6.0f, 0.0f, _lookAndFeelPtr)

		, m_lowBandwidthSlider("BW", 0, 5, 2, 2, Processing::s_lowBandwidthParamID, 1.0f, 0.01f, 4.0f, 0.01f, _lookAndFeelPtr)
		, m_midBandwidthSlider("BW", 2, 5, 2, 2, Processing::s_midBandwidthParamID, 1.0f, 0.01f, 4.0f, 0.01f, _lookAndFeelPtr)
		, m_highBandwidthSlider("BW", 4, 5, 2, 2, Processing::s_highBandwidthParamID, 1.0f, 0.01f, 4.0f, 0.01f, _lookAndFeelPtr)

		, m_engageHeatButton("Heat", 6, 4, 2, 1, Processing::s_engageHeatParamID, false, _lookAndFeelPtr)
		, m_heatGainSlider("Heat Gain", 6, 5, 2, 2, Processing::s_heatGainParamID, 0.0f, -12.0f, 12.0f, 0.0f, _lookAndFeelPtr)
		, m_masterBypassButton("Bypass", 8, 4, 2, 1, Processing::s_masterBypassParamID, false, _lookAndFeelPtr)
		, m_masterGainSlider("Output Gain", 8, 5, 2, 2, Processing::s_masterGainParamID, 0.0f, -12.0f, 12.0f, 0.0f, _lookAndFeelPtr)

		, m_hotTitleLabel("HOT", 6, 0, 4, 2, Processing::s_NULL_PARAM_ID, CustomLookAndFeel::s_colour_burningOrange, _lookAndFeelPtr)
		, m_shelfTitleLabel("SHELF", 6, 1, 4, 3, Processing::s_NULL_PARAM_ID, juce::Colours::white, _lookAndFeelPtr)
	{
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Destructor for the ControlManager class.
	/// </summary>
	ControlManager::~ControlManager()
	{
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Paint the ControlManager.
	/// </summary>
	void ControlManager::paint(juce::Graphics& _graphics)
	{
		// check that the window size is not zero

		
		if (DEBUG && false)
		{
			// draw the outline
			juce::Rectangle<int> controlAreaBounds = juce::Rectangle<int>(m_margin, m_margin, m_controlAreaWidth, m_controlAreaHeight);
			_graphics.setColour(GUI::CustomLookAndFeel::s_colour_burningOrange);
			_graphics.drawRect(controlAreaBounds, 1.0f);

			BoundsGrid grid = GenerateGridOfBounds();
			for (auto column : grid)
			{
				for (auto cell : column) 
				{
					_graphics.setColour(juce::Colours::white.withMultipliedAlpha(0.5f));
					_graphics.drawRect(cell, 1.0f);
				}
			}
		}

		// Draw control groups
		if (true)
		{
			for (std::vector<juce::Component*> ctrlGroup : GetControlGroups())
			{
				// Get the collective bounds of each control in the group
				juce::Rectangle<int> ctrlGroupBounds = juce::Rectangle<int>(0,0,0,0);
				for (juce::Component* component : ctrlGroup)
				{
					const juce::Rectangle<int> componentBounds = component->getBounds();
					ctrlGroupBounds = ctrlGroupBounds.getUnion(componentBounds);
				}

				auto woodBorder = ctrlGroupBounds.expanded(
					GUI::CustomLookAndFeel::s_controlBoundsMargin, 
					GUI::CustomLookAndFeel::s_controlBoundsMargin);


				juce::Colour woodCol = 
					GUI::CustomLookAndFeel::Darken(
					GUI::CustomLookAndFeel::s_colour_dustyOrange
					);

				_graphics.setColour(woodCol);
				_graphics.fillRoundedRectangle(woodBorder.toFloat(), GUI::CustomLookAndFeel::s_cornerRadius);
				_graphics.setColour(GUI::CustomLookAndFeel::s_shadowColour);
				_graphics.drawRoundedRectangle(woodBorder.toFloat()
								, GUI::CustomLookAndFeel::s_cornerRadius
								, GUI::CustomLookAndFeel::s_outlineThickness);


				// Draw the shadow
				if (GUI::CustomLookAndFeel::s_useDropShadows)
				{
					juce::Path shadowPath;
					shadowPath.addRoundedRectangle(ctrlGroupBounds.toFloat(), GUI::CustomLookAndFeel::s_cornerRadius);
					GUI::CustomLookAndFeel::s_panelShadow.drawForPath(_graphics, shadowPath);
				}

				// Draw the control group
				_graphics.setGradientFill(
					GUI::CustomLookAndFeel::BackgroundGradient(
						ctrlGroupBounds.getTopLeft().toFloat(),
						ctrlGroupBounds.getBottomRight().toFloat()
					));
				_graphics.fillRoundedRectangle(ctrlGroupBounds.toFloat(), GUI::CustomLookAndFeel::s_cornerRadius);

				_graphics.setColour(GUI::CustomLookAndFeel::s_shadowColour);
				_graphics.drawRoundedRectangle(ctrlGroupBounds.toFloat()
					, GUI::CustomLookAndFeel::s_cornerRadius
					, GUI::CustomLookAndFeel::s_outlineThickness);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Resizes and Repositions all components.
	/// </summary>
	/// <param name="_newWidth"></param>
	/// <param name="_newHeight"></param>
	void ControlManager::resized
	(
		const int _newWidth, 
		const int _newHeight
	)
	{
		m_controlAreaHeight = _newHeight - 2 * m_margin;
		m_controlAreaWidth = _newWidth - 2 * m_margin;

		m_isGridUpdated = false;
		m_boundsGrid = GenerateGridOfBounds();

		// Iterate over your controls and set their positions
		for (GUI::Controls::BaseTypes::RotaryDial* rotaryDial : GetAllRotaryDials())
		{
			juce::Point<int>& topLeft = m_boundsGrid
				[rotaryDial->m_xPos]
				[rotaryDial->m_yPos]
				.getTopLeft();

			juce::Point<int>& bottomRight = m_boundsGrid
				[rotaryDial->m_xPos + rotaryDial->m_width - 1]
				[rotaryDial->m_yPos + rotaryDial->m_height - 1]
				.getBottomRight();

			rotaryDial->setBounds(juce::Rectangle<int>(topLeft, bottomRight));
		}

		for (GUI::Controls::BaseTypes::LatchButton* latchButton : GetAllLatchButtons())
		{
			juce::Point<int>& topLeft = m_boundsGrid
				[latchButton->m_xPos]
				[latchButton->m_yPos]
				.getTopLeft();

			juce::Point<int>& bottomRight = m_boundsGrid
				[latchButton->m_xPos + latchButton->m_width - 1]
				[latchButton->m_yPos + latchButton->m_height - 1]
				.getBottomRight();

			juce::Rectangle<int> bounds = juce::Rectangle<int>(topLeft, bottomRight);

			latchButton->setBounds(bounds);
		}

		for (GUI::Controls::BaseTypes::CustomLabel* customLabel : GetAllCustomLabels())
		{
			juce::Point<int>& topLeft = m_boundsGrid
				[customLabel->m_xPos]
				[customLabel->m_yPos]
				.getTopLeft();

			juce::Point<int>& bottomRight = m_boundsGrid
				[customLabel->m_xPos + customLabel->m_width - 1]
				[customLabel->m_yPos + customLabel->m_height - 1]
				.getBottomRight();

			customLabel->setBounds(juce::Rectangle<int>(topLeft, bottomRight));
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of pointers to all controls.
	/// </summary>
	/// <returns>Vector of Component*</returns>
	const std::vector<BaseTypes::RotaryDial*> ControlManager::GetAllRotaryDials()
	{
		std::vector<BaseTypes::RotaryDial*> result;

		result.push_back(&m_lowFreqSlider);
		result.push_back(&m_midFreqSlider);
		result.push_back(&m_highFreqSlider);

		result.push_back(&m_lowGainSlider);
		result.push_back(&m_midGainSlider);
		result.push_back(&m_highGainSlider);

		result.push_back(&m_lowBandwidthSlider);
		result.push_back(&m_midBandwidthSlider);
		result.push_back(&m_highBandwidthSlider);

		result.push_back(&m_masterGainSlider);
		result.push_back(&m_heatGainSlider);

		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of pointers to all buttons.
	/// </summary>
	/// <returns>Vector of Component*</returns>
	const std::vector<BaseTypes::LatchButton*> ControlManager::GetAllLatchButtons()
	{
		std::vector<BaseTypes::LatchButton*> result;

		result.push_back(&m_engageHeatButton);
		result.push_back(&m_masterBypassButton);

		result.push_back(&m_lowShelfBypass);
		result.push_back(&m_midShelfBypass);
		result.push_back(&m_highShelfBypass);

		return result;
	}

	const std::vector<BaseTypes::CustomLabel*> ControlManager::GetAllCustomLabels()
	{
		std::vector<BaseTypes::CustomLabel*> result;

		result.push_back(&m_hotTitleLabel);
		result.push_back(&m_shelfTitleLabel);

		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of pointers to all controls.
	/// </summary>
	/// <returns>Vector of Component*</returns>
	const std::vector<juce::Component*> ControlManager::GetAllCustomControls()
	{
		std::vector<juce::Component*> result;

		for (BaseTypes::RotaryDial* rotaryDialPtr : GetAllRotaryDials())
		{
			result.push_back(dynamic_cast<juce::Component*>(rotaryDialPtr));
		}

		for (BaseTypes::LatchButton* latchButtonPtr : GetAllLatchButtons())
		{
			result.push_back(dynamic_cast<juce::Component*>(latchButtonPtr));
		}

		for (BaseTypes::CustomLabel* customLabelPtr : GetAllCustomLabels())
		{
			result.push_back(dynamic_cast<juce::Component*>(customLabelPtr));
		}

		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of vectors, each containing grouped controls.
	/// </summary>
	/// <returns>Vector of vectors of Component*</returns>
	const std::vector<std::vector<juce::Component*>> ControlManager::GetControlGroups()
	{
		std::vector<std::vector<juce::Component*>> result;

		// Low Shelf
		result.push_back(std::vector<juce::Component*>
		{
			dynamic_cast<juce::Component*>(&m_lowShelfBypass),
			dynamic_cast<juce::Component*>(&m_lowFreqSlider),
			dynamic_cast<juce::Component*>(&m_lowGainSlider),
			dynamic_cast<juce::Component*>(&m_lowBandwidthSlider)
		});

		// Mid Shelf
		result.push_back(std::vector<juce::Component*>
		{
			dynamic_cast<juce::Component*>(&m_midShelfBypass),
			dynamic_cast<juce::Component*>(&m_midFreqSlider),
			dynamic_cast<juce::Component*>(&m_midGainSlider),
			dynamic_cast<juce::Component*>(&m_midBandwidthSlider)
		});

		// High Shelf
		result.push_back(std::vector<juce::Component*>
		{
			dynamic_cast<juce::Component*>(&m_highShelfBypass),
			dynamic_cast<juce::Component*>(&m_highFreqSlider),
			dynamic_cast<juce::Component*>(&m_highGainSlider),
			dynamic_cast<juce::Component*>(&m_highBandwidthSlider)
		});

		// Master
		result.push_back(std::vector<juce::Component*>
		{
			dynamic_cast<juce::Component*>(&m_masterBypassButton),
			dynamic_cast<juce::Component*>(&m_masterGainSlider),

			dynamic_cast<juce::Component*>(&m_engageHeatButton),
			dynamic_cast<juce::Component*>(&m_heatGainSlider),

			dynamic_cast<juce::Component*>(&m_hotTitleLabel),
			dynamic_cast<juce::Component*>(&m_shelfTitleLabel)
		});

		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of vectors, each containing bounds that can be used to place controls. 
	/// Top-Left is 0,0
	/// </summary>
	/// <returns>Vector of vectors of Rectangle<int></returns>
	BoundsGrid ControlManager::GenerateGridOfBounds()
	{
		if (m_isGridUpdated)
		{
			return m_boundsGrid;
		}


		const int cellWidth = (m_controlAreaWidth / m_controlGridSizeX);
		const int cellHeight =	(m_controlAreaHeight / m_controlGridSizeY);

		for (int x = 0; x < m_controlGridSizeX; x++)
		{
			// add the new column
			m_boundsGrid.push_back(std::vector<juce::Rectangle<int>>());

			for (int y = 0; y < m_controlGridSizeY; y++)
			{
				// calculate the position of the cell
				int cellXPos = m_margin + (x * cellWidth);
				int cellYPos = m_margin + (y * cellHeight);

				juce::Rectangle<int> controlBounds = 
					juce::Rectangle<int>(cellXPos, cellYPos, cellWidth, cellHeight)
					.reduced(m_gridSpacingX, m_gridSpacingY);

				m_boundsGrid[x].push_back(controlBounds);
			}
		}

		m_isGridUpdated = true;
		return m_boundsGrid;
	}
}