#pragma once

#include <JuceHeader.h>

using namespace juce;
using namespace std;

using FloatParamDirectory = std::map<int, juce::AudioParameterFloat*>;
using BoolParamDirectory = std::map<int, juce::AudioParameterBool*>;

namespace DSP
{
	/// Static Ids to be used for linging parameters to dials
	/// NOTE ALPHA: These must be unique
	/// NOTE THE 2ND: I'm pretty sure since they're static AND const, 
	/// we don't need to worry about any multi-threaded shenenigans?

	static const int s_NULL_PARAM_ID(0);
	static const int s_masterBypassParamID(1);
	static const int s_masterGainParamID(2);
	static const int s_thresholdParamID(3);
	static const int s_ratioParamID(4);
}

namespace DSP
{
	//////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Holds all the parameters for the plugin in a static class
	/// NOTE: Dubious about this approach, but it allows easy access to these without having to pass the class around
	/// TODO: Optimise this
	/// </summary>
	static class Parameters
	{
	public: //////////////////////////////////////////////////////////////////////

		Parameters();
		~Parameters();

		static const juce::AudioProcessorParameter* GetParameter(int _paramID);

		static const FloatParamDirectory& GetSliderParams();
		static const BoolParamDirectory& GetBoolParams();

	private: //////////////////////////////////////////////////////////////////////

		static FloatParamDirectory s_floatParams;
		static BoolParamDirectory s_boolParams;

		static AudioParameterFloat s_threshold;
		static AudioParameterFloat s_ratio;

		static AudioParameterBool s_masterBypass;
		static AudioParameterFloat s_masterGain;
	};
}