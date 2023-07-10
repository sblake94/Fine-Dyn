/*
	==========================================================================================

	@Author : SBlake
	This class handles contains all of the dials, knobs, 
	and buttons of the GUI

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Controls/BaseTypes/LatchButton.h"
#include "Controls/BaseTypes/RotaryDial.h"
#include "Controls/Buttons/EngageButton.h"
#include "Controls/Dials/BandwidthDial.h"
#include "Controls/Dials/FrequencyDial.h"
#include "Controls/Dials/GainDial.h"
#include "Controls/Dials/RatioDial.h"
#include "Controls/Labels/TitleLabel.h"
#include "Controls/Sliders/ThresholdSlider.h"
#include "GridResident.h"

using namespace GUI::Controls;
using namespace GUI::Controls::BaseTypes;
using namespace GUI::Controls::Dials;
using namespace GUI::Controls::Buttons;
using namespace GUI::Controls::Labels;
using namespace GUI::Controls::Sliders;

using namespace std;
using namespace juce;

using BoundsGrid = vector<vector<juce::Rectangle<int>>>;

namespace GUI
{
	/////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///		This class handles contains all of the dials, knobs,
	///		and buttons of the GUI
	/// </summary>
	class ControlManager
	{
	public: /////////////////////////////////////////////////////////////////////////////////////
		ControlManager(
			const int _windowWidth, 
			const int _windowHeight,
			LookAndFeel* _lookAndFeelPtr = nullptr);
		~ControlManager();

		void paint(Graphics& _graphics);
		void DEBUG_DrawGrid(Graphics& _graphics);
		void DrawControlGroupPanels(Graphics& _graphics);
		void resized(const int _newWidth, const int _newHeight);

		const vector<GridResident*> GetAllGridResidents();

		const vector<vector<GridResident*>> GetControlGroups();

		BoundsGrid GenerateGridOfBounds();

	private: /////////////////////////////////////////////////////////////////////////////////////

		unique_ptr<GridResident> m_thresholdSlider;
		unique_ptr<GridResident> m_ratioDial;

		unique_ptr<GridResident> m_masterBypassButton;
		unique_ptr<GridResident> m_masterGainSlider;

		unique_ptr<GridResident> m_fineTitleLabel;
		unique_ptr<GridResident> m_dynTitleLabel;

		BoundsGrid m_boundsGrid;
		bool m_isGridUpdated = false;

		const int m_margin = 20;
		const int m_controlGridSizeX = 16;
		const int m_controlGridSizeY = 9;
		const int m_gridSpacingX = 0;
		const int m_gridSpacingY = 0;

		int m_controlAreaWidth;
		int m_controlAreaHeight;
		int m_controlAreaX = m_margin;
		int m_controlAreaY = m_margin;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlManager);
	};
}