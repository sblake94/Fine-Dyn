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
		
		, m_thresholdSlider(std::make_unique<GridResident>(
			new ThresholdSlider(-36.f, 12.f, 0.1f, 0.0f, true, _lookAndFeelPtr), 
			DSP::s_thresholdParamID, 
			0, 0, 3, 6))

		, m_ratioDial(std::make_unique<GridResident>(
			new RatioDial(1.0f, 8.0f, 0.0f, 1.5f, _lookAndFeelPtr),
			DSP::s_ratioParamID,
			3, 0, 3, 3))

		, m_masterBypassButton(std::make_unique<GridResident>(
			new EngageButton("Bypass", false, _lookAndFeelPtr),
			DSP::s_masterBypassParamID, 
			8, 5, 3, 1))

		, m_masterGainSlider(std::make_unique<GridResident>(
			new GainDial(-12.0f, 12.0f, 0.0f, 0.0f, _lookAndFeelPtr),
			DSP::s_masterGainParamID, 
			8, 6, 3, 3))

		, m_fineTitleLabel(std::make_unique<GridResident>(
			new TitleLabel("FINE", LookAndFeels::CustomLookAndFeel::s_colour_brightAccent, _lookAndFeelPtr),
			DSP::s_NULL_PARAM_ID, 
			8, 1, 3, 1))

		, m_dynTitleLabel(std::make_unique<GridResident>(
			new TitleLabel("DYNA", LookAndFeels::CustomLookAndFeel::s_textColourBrightT, _lookAndFeelPtr),
			DSP::s_NULL_PARAM_ID,
			8, 2, 3, 1))
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

			for (auto& control : GetAllGridResidents())
			{
				auto bounds = control->m_component->getBounds();

				_graphics.fillRect(bounds);
			}
		}
	}

	void ControlManager::DrawControlGroupPanels(juce::Graphics& _graphics)
	{
		for (vector<GridResident*> ctrlGroup : GetControlGroups())
		{
			// Get the collective bounds of each control in the group
			juce::Rectangle<int> ctrlGroupBounds = juce::Rectangle<int>(0, 0, 0, 0);
			for (auto& component : ctrlGroup)
			{
				const juce::Rectangle<int> componentBounds = component->m_component->getBounds();
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
		for (GUI::GridResident* gridResident : GetAllGridResidents())
		{
			juce::Point<int>& topLeft = m_boundsGrid
				[gridResident->m_xPos]
				[gridResident->m_yPos]
				.getTopLeft();

			juce::Point<int>& bottomRight = m_boundsGrid
				[gridResident->m_xPos + gridResident->m_width - 1]
				[gridResident->m_yPos + gridResident->m_height - 1]
				.getBottomRight();

				gridResident->m_component->setBounds(juce::Rectangle<int>(topLeft, bottomRight));
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Gets pointers to all the controls in the ControlManager.
	/// </summary>
	/// <returns>BoundsGrid</returns>
	const vector<GridResident*> ControlManager::GetAllGridResidents()
	{
		vector<GridResident*> result;

		result.push_back(m_thresholdSlider.get());
		result.push_back(m_ratioDial.get());

		result.push_back(m_masterBypassButton.get());
		result.push_back(m_masterGainSlider.get());

		result.push_back(m_fineTitleLabel.get());
		result.push_back(m_dynTitleLabel.get());

		return result;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Returns a vector of vectors, each containing grouped controls.
	/// </summary>
	/// <returns>Vector of vectors of Component*</returns>
	const vector<vector<GridResident*>> ControlManager::GetControlGroups()
	{
		vector<vector<GridResident*>> result;

		// Compressor
		result.push_back(vector<GridResident*>
		{
			m_thresholdSlider.get(),
			m_ratioDial.get()
		});

		// Master
		result.push_back(vector<GridResident*>
		{
			m_masterBypassButton.get(),
			m_masterGainSlider.get(),

			m_fineTitleLabel.get(),
			m_dynTitleLabel.get(),
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
			m_boundsGrid.push_back(vector<juce::Rectangle<int>>());

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