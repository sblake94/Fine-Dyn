#pragma once

#include <JuceHeader.h>

using namespace juce;
using namespace std;

using FloatParamDirectory = std::map<int, juce::AudioParameterFloat*>;
using BoolParamDirectory = std::map<int, juce::AudioParameterBool*>;

namespace Processing
{
	/// Static Ids to be used for linging parameters to dials
	/// NOTE ALPHA: These must be unique
	/// NOTE THE 2ND: I'm pretty sure since they're static AND const, 
	/// we don't need to worry about any multi-threaded shenenigans?

	static const int s_lowFreqCutoffParamID(0);
	static const int s_midFreqCutoffParamID(1);
	static const int s_highFreqCutoffParamID(2);
	static const int s_lowGainParamID(3);
	static const int s_midGainParamID(4);
	static const int s_highGainParamID(5);
	static const int s_lowBandwidthParamID(6);
	static const int s_midBandwidthParamID(7);
	static const int s_highBandwidthParamID(8);
	static const int s_engageHeatParamID(9);
	static const int s_masterBypassParamID(10);
	static const int s_highBandBypassParamID(11);
	static const int s_midBandBypassParamID(12);
	static const int s_lowBandBypassParamID(13);
	static const int s_masterGainParamID(14);
	static const int s_heatGainParamID(15);
	static const int s_NULL_PARAM_ID(INT_MAX);
}

namespace Processing
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

		static AudioParameterBool s_lowBandBypass;
		static AudioParameterBool s_midBandBypass;
		static AudioParameterBool s_highBandBypass;

		static AudioParameterFloat s_lowFreqCutoff;
		static AudioParameterFloat s_midFreqCutoff;
		static AudioParameterFloat s_highFreqCutoff;

		static AudioParameterFloat s_lowGain;
		static AudioParameterFloat s_midGain;
		static AudioParameterFloat s_highGain;

		static AudioParameterFloat s_lowBandwidth;
		static AudioParameterFloat s_midBandwidth;
		static AudioParameterFloat s_highBandwidth;

		static AudioParameterBool s_masterBypass;
		static AudioParameterFloat s_masterGain;

		static AudioParameterBool s_engageHeat;
		static AudioParameterFloat s_heatGain;
	};
}