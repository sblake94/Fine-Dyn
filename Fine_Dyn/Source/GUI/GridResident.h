#pragma once

#include <JuceHeader.h>
#include <type_traits>

namespace GUI
{
	class GridResident
	{

	public:
		GridResident(
			juce::Component* _component,
			const int _parameterID,
			const int _xPos, 
			const int _yPos,
			const int _width,
			const int _height);
		~GridResident();

		void SetComponentValue(const float _value);

		juce::Button* GetAsButtonPtr() const;
		juce::Slider* GetAsSliderPtr() const;
		juce::Label* GetAsLabelPtr() const;

		std::unique_ptr<juce::Component> m_component;
		int m_parameterID;
		int m_xPos;
		int m_yPos;
		int m_width;
		int m_height;
		
	};
}
