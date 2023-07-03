#pragma once

#include <JuceHeader.h>

namespace GUI::Controls::BaseTypes
{
	/////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Base class for all custom sliders
	/// </summary>
	class CustomControlBase
	{
	public://///////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="_paramID">The ID of the Slider</param>
		inline CustomControlBase(
			juce::String _labelText,
			const int _xPos,
			const int _yPos,
			const int _width,
			const int _height,
			const int _paramID)
			: m_id(_paramID)
			, m_labelText(_labelText)
			, m_xPos(_xPos)
			, m_yPos(_yPos)
			, m_width(_width)
			, m_height(_height)
		{
		};

		/////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// The ID of the Slider
		/// </summary>
		const int m_id;

		juce::String m_labelText;
		int m_xPos, m_yPos;
		int m_width, m_height;

	private://///////////////////////////////////////////////////////////////////////////////////////
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomControlBase);
	};
}