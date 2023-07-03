#include "ControlManager.h"

#include "../DSP/Parameters.h"
#include "../GUI/LookAndFeels/CustomLookAndFeel.h"

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
		
		, m_thresholdSlider(-96, 6, 0.01f, 0.0f, "Threshold", 0, 0, 2, 5, DSP::s_thresholdParamID, true, _lookAndFeelPtr)
		, m_ratioDial("Ratio", 2, 0, 2, 2, DSP::s_ratioParamID, 1.5f, 1.0f, 8.0f, 0.01f, _lookAndFeelPtr)

		, m_masterBypassButton("Bypass", 8, 4, 2, 1, DSP::s_masterBypassParamID, false, _lookAndFeelPtr)
		, m_masterGainSlider("Output Gain", 8, 5, 2, 2, DSP::s_masterGainParamID, 0.0f, -12.0f, 12.0f, 0.0f, _lookAndFeelPtr)

		, m_fineTitleLabel("FINE", 6, 0, 4, 2, DSP::s_NULL_PARAM_ID, LookAndFeels::CustomLookAndFeel::s_colour_brightAccent, _lookAndFeelPtr)
		, m_dynTitleLabel("DYNA", 6, 1, 4, 2, DSP::s_NULL_PARAM_ID, LookAndFeels::CustomLookAndFeel::s_textColourBrightT, _lookAndFeelPtr)
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
		if (m_controlAreaHeight == 0 || m_controlAreaWidth == 0)
		{
			return;
		}

		if(false)
			DEBUG_DrawGrid(_graphics);
		else
			DrawControlGroupPanels(_graphics);
	}

	void ControlManager::DEBUG_DrawGrid(juce::Graphics& _graphics)
	{
		if (DEBUG)
		{
			// draw the outline
			juce::Rectangle<int> controlAreaBounds = juce::Rectangle<int>(m_margin, m_margin, m_controlAreaWidth, m_controlAreaHeight);
			_graphics.setColour(GUI::LookAndFeels::CustomLookAndFeel::s_colour_brightAccent.withAlpha(0.25f));
			_graphics.drawRect(controlAreaBounds, 1.0f);

			BoundsGrid grid = GenerateGridOfBounds();
			for (auto column : grid)
			{
				for (auto cell : column)
				{
					_graphics.setColour(juce::Colours::black.withMultipliedAlpha(0.2f));
					_graphics.fillRect(cell.toFloat());
				}
			}

			for (auto control : GetAllCustomControls())
			{
				auto bounds = control->getBounds();

				_graphics.fillRect(bounds);
			}
		}
	}

	void ControlManager::DrawControlGroupPanels(juce::Graphics& _graphics)
	{
		for (std::vector<juce::Component*> ctrlGroup : GetControlGroups())
		{
			// Get the collective bounds of each control in the group
			juce::Rectangle<int> ctrlGroupBounds = juce::Rectangle<int>(0, 0, 0, 0);
			for (juce::Component* component : ctrlGroup)
			{
				const juce::Rectangle<int> componentBounds = component->getBounds();
				ctrlGroupBounds = ctrlGroupBounds.getUnion(componentBounds);
			}

			//auto woodBorder = ctrlGroupBounds.expanded(
			//	GUI::LookAndFeels::CustomLookAndFeel::s_controlBoundsMargin,
			//	GUI::LookAndFeels::CustomLookAndFeel::s_controlBoundsMargin);

			//juce::Colour woodCol =
			//	GUI::LookAndFeels::CustomLookAndFeel::Darken(
			//		GUI::LookAndFeels::CustomLookAndFeel::s_colour_dustyAccent
			//	);

			//_graphics.setColour(woodCol);
			//_graphics.fillRoundedRectangle(woodBorder.toFloat(), GUI::LookAndFeels::CustomLookAndFeel::s_cornerRadius);

			// Draw the control group
			Path panelPath;
			panelPath.addRoundedRectangle(ctrlGroupBounds.toFloat(), GUI::LookAndFeels::CustomLookAndFeel::s_cornerRadius);
			GUI::LookAndFeels::CustomLookAndFeel::s_darkShadow.drawForPath(_graphics, panelPath);
			GUI::LookAndFeels::CustomLookAndFeel::s_lightShadow.drawForPath(_graphics, panelPath);


			_graphics.setColour(GUI::LookAndFeels::CustomLookAndFeel::s_fillColorA);
			_graphics.fillPath(panelPath);
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

		for (GUI::Controls::BaseTypes::LinearSlider* LinearSliders : GetAllLinearSliders())
		{
			juce::Point<int>& topLeft = m_boundsGrid
				[LinearSliders->m_xPos]
				[LinearSliders->m_yPos]
				.getTopLeft();

			juce::Point<int>& bottomRight = m_boundsGrid
				[LinearSliders->m_xPos + LinearSliders->m_width - 1]
				[LinearSliders->m_yPos + LinearSliders->m_height - 1]
				.getBottomRight();

			juce::Rectangle<int> bounds = juce::Rectangle<int>(topLeft, bottomRight);

			LinearSliders->setBounds(bounds);
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
	/// Returns a vector of pointers to all dials.
	/// </summary>
	/// <returns>Vector of Component*</returns>
	const std::vector<BaseTypes::RotaryDial*> ControlManager::GetAllRotaryDials()
	{
		std::vector<BaseTypes::RotaryDial*> result;

		result.push_back(&m_masterGainSlider);
		result.push_back(&m_ratioDial);

		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of pointers to all controls.
	/// </summary>
	/// <returns>Vector of Component*</returns>
	const std::vector<BaseTypes::LinearSlider*> ControlManager::GetAllLinearSliders()
	{
		std::vector<BaseTypes::LinearSlider*> result;

		result.push_back(&m_thresholdSlider);


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

		result.push_back(&m_masterBypassButton);

		return result;
	}

	const std::vector<BaseTypes::CustomLabel*> ControlManager::GetAllCustomLabels()
	{
		std::vector<BaseTypes::CustomLabel*> result;

		result.push_back(&m_fineTitleLabel);
		result.push_back(&m_dynTitleLabel);

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

		for (BaseTypes::LinearSlider* linearSliderPtr : GetAllLinearSliders())
		{
			result.push_back(dynamic_cast<juce::Component*>(linearSliderPtr));
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

		// Compressor
		result.push_back(std::vector<juce::Component*>
		{
			dynamic_cast<juce::Component*>(&m_thresholdSlider),
			dynamic_cast<juce::Component*>(&m_ratioDial)
		});

		// Master
		result.push_back(std::vector<juce::Component*>
		{
			dynamic_cast<juce::Component*>(&m_masterBypassButton),
			dynamic_cast<juce::Component*>(&m_masterGainSlider),

			dynamic_cast<juce::Component*>(&m_fineTitleLabel),
			dynamic_cast<juce::Component*>(&m_dynTitleLabel)
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