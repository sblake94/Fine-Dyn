/*
	==========================================================================================

	@Author : SBlake
	This class handles contains all of the dials, knobs, 
	and buttons of the GUI

	==========================================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Controls/Dials/FrequencyDial.h"
#include "Controls/Dials/GainDial.h"
#include "Controls/Dials/BandwidthDial.h"
#include "Controls/Buttons/EngageButton.h"
#include "Controls/BaseTypes/RotaryDial.h"
#include "Controls/BaseTypes/LatchButton.h"
#include "Controls/Labels/TitleLabel.h"
#include "Controls/BaseTypes/CustomControlBase.h"

using namespace GUI::Controls;
using namespace GUI::Controls::Dials;
using namespace GUI::Controls::Buttons;
using namespace GUI::Controls::Labels;

using BoundsGrid = std::vector<std::vector<juce::Rectangle<int>>>;

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
			juce::LookAndFeel* _lookAndFeelPtr = nullptr);
		~ControlManager();

		void paint(juce::Graphics& _graphics);
		void resized(const int _newWidth, const int _newHeight);

		const std::vector<BaseTypes::RotaryDial*> GetAllRotaryDials();
		const std::vector<BaseTypes::LatchButton*> GetAllLatchButtons();
		const std::vector<BaseTypes::CustomLabel*> GetAllCustomLabels();
		const std::vector<juce::Component*> GetAllCustomControls();

		const std::vector<std::vector<juce::Component*>> GetControlGroups();

		BoundsGrid GenerateGridOfBounds();

	private: /////////////////////////////////////////////////////////////////////////////////////
		FrequencyDial m_lowFreqSlider;
		FrequencyDial m_midFreqSlider;
		FrequencyDial m_highFreqSlider;

		GainDial m_lowGainSlider;
		GainDial m_midGainSlider;
		GainDial m_highGainSlider;

		BandwidthDial m_lowBandwidthSlider;
		BandwidthDial m_midBandwidthSlider;
		BandwidthDial m_highBandwidthSlider;

		EngageButton m_lowShelfBypass;
		EngageButton m_midShelfBypass;
		EngageButton m_highShelfBypass;

		EngageButton m_engageHeatButton;
		EngageButton m_masterBypassButton;

		GainDial m_masterGainSlider;
		GainDial m_heatGainSlider;

		TitleLabel m_hotTitleLabel;
		TitleLabel m_shelfTitleLabel;

		BoundsGrid m_boundsGrid;
		bool m_isGridUpdated = false;

		const int m_margin = 20;
		const int m_controlGridSizeX = 10;
		const int m_controlGridSizeY = 7;
		const int m_gridSpacingX = 8;
		const int m_gridSpacingY = 5;

		int m_controlAreaWidth;
		int m_controlAreaHeight;
		int m_controlAreaX = m_margin;
		int m_controlAreaY = m_margin;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlManager);
	};
}