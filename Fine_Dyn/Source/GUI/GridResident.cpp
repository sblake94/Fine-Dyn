#include "GridResident.h"

namespace GUI
{
	GridResident::GridResident
	(
		juce::Component* _component, 
		const int _parameterID,
		const int _xPos, 
		const int _yPos, 
		const int _width, 
		const int _height
	)
		: m_component(_component),
		m_parameterID(_parameterID),
		m_xPos(_xPos),
		m_yPos(_yPos),
		m_width(_width),
		m_height(_height)
	{
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Destructor
	/// </summary>
	GridResident::~GridResident()
	{

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Sets the value of the component
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="_value"></param>
	void GridResident::SetComponentValue(const float _value)
	{
		if (GetAsSliderPtr() != nullptr)
		{
			return GetAsSliderPtr()->setValue(_value);
		}

		if (GetAsButtonPtr() != nullptr)
		{
			return GetAsButtonPtr()->setToggleState(_value, juce::dontSendNotification);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	juce::Button* GridResident::GetAsButtonPtr() const
	{
		return dynamic_cast<juce::Button*>(m_component.get());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///
	/// </summary>
	/// <returns></returns>
	juce::Slider* GridResident::GetAsSliderPtr() const
	{
		return dynamic_cast<juce::Slider*>(m_component.get());
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	///
	/// </summary>
	/// <returns></returns>
	juce::Label* GridResident::GetAsLabelPtr() const
	{
		return dynamic_cast<juce::Label*>(m_component.get());
	}
}