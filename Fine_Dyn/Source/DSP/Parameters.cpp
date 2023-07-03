#include "Parameters.h"

using namespace Processing;

namespace Processing 
{
	// NOTE: I'm dubious about these being static, but I don't think we're doing any multi-threaded access to them, so it should be fine.

	AudioParameterBool Parameters::s_lowBandBypass = AudioParameterBool(s_lowBandBypassParamID, juce::String("Low Band Bypass"), false);
	AudioParameterBool Parameters::s_midBandBypass = AudioParameterBool(s_midBandBypassParamID, juce::String("Mid Band Bypass"), false);
	AudioParameterBool Parameters::s_highBandBypass = AudioParameterBool(s_highBandBypassParamID, juce::String("High Band Bypass"), false);

	AudioParameterFloat Parameters::s_lowFreqCutoff = AudioParameterFloat(s_lowFreqCutoffParamID, juce::String("Low Frequency Cutoff"), 20.0f, 20000.0f, 2000.0f);
	AudioParameterFloat Parameters::s_midFreqCutoff = AudioParameterFloat(s_midFreqCutoffParamID, juce::String("Mid Frequency Cutoff"), 20.0f, 20000.0f, 2000.0f);
	AudioParameterFloat Parameters::s_highFreqCutoff = AudioParameterFloat(s_highFreqCutoffParamID, juce::String("High Frequency Cutoff"), 20.0f, 20000.0f, 2000.0f);

	AudioParameterFloat Parameters::s_lowGain = AudioParameterFloat(s_lowGainParamID, juce::String("Low Gain"), -6.0f, 6.0f, 0.0f);
	AudioParameterFloat Parameters::s_midGain = AudioParameterFloat(s_midGainParamID, juce::String("Mid Gain"), -6.0f, 6.0f, 0.0f);
	AudioParameterFloat Parameters::s_highGain = AudioParameterFloat(s_highGainParamID, juce::String("High Gain"), -6.0f, 6.0f, 0.0f);

	AudioParameterFloat Parameters::s_lowBandwidth = AudioParameterFloat(s_lowBandwidthParamID, juce::String("Low Bandwidth"), 0.1f, 10.0f, 1.0f);
	AudioParameterFloat Parameters::s_midBandwidth = AudioParameterFloat(s_midBandwidthParamID, juce::String("Mid Bandwidth"), 0.1f, 10.0f, 1.0f);
	AudioParameterFloat Parameters::s_highBandwidth = AudioParameterFloat(s_highBandwidthParamID, juce::String("High Bandwidth"), 0.1f, 10.0f, 1.0f);

	AudioParameterBool Parameters::s_masterBypass = AudioParameterBool(s_masterBypassParamID, juce::String("Master Bypass"), false);
	AudioParameterFloat Parameters::s_masterGain = AudioParameterFloat(s_masterGainParamID, juce::String("Master Gain"), -6.0f, 6.0f, 0.0f);

	AudioParameterBool Parameters::s_engageHeat	= AudioParameterBool(s_engageHeatParamID, juce::String("Engage Heat"), false);
	AudioParameterFloat Parameters::s_heatGain = AudioParameterFloat(s_heatGainParamID, juce::String("Heat Gain"), -6.0f, 6.0f, 0.0f);

	FloatParamDirectory Parameters::s_floatParams = FloatParamDirectory
	{
		{ s_lowFreqCutoffParamID, &s_lowFreqCutoff },
		{ s_midFreqCutoffParamID, &s_midFreqCutoff },
		{ s_highFreqCutoffParamID, &s_highFreqCutoff },

		{ s_lowGainParamID, &s_lowGain },
		{ s_midGainParamID, &s_midGain },
		{ s_highGainParamID, &s_highGain },

		{ s_lowBandwidthParamID, &s_lowBandwidth },
		{ s_midBandwidthParamID, &s_midBandwidth },
		{ s_highBandwidthParamID, &s_highBandwidth },

		{ s_masterGainParamID, &s_masterGain },
		{ s_heatGainParamID, &s_heatGain }
	};

	BoolParamDirectory Parameters::s_boolParams = BoolParamDirectory
	{
		{ s_engageHeatParamID, &s_engageHeat },
		{ s_masterBypassParamID, &s_masterBypass },

		{ s_lowBandBypassParamID, &s_lowBandBypass },
		{ s_midBandBypassParamID, &s_midBandBypass },
		{ s_highBandBypassParamID, &s_highBandBypass}
	};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
Parameters::Parameters()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
Parameters::~Parameters()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Gets the parameter via its static ID
/// </summary>
/// <param name="_paramID"></param>
/// <returns></returns>
const juce::AudioProcessorParameter* Processing::Parameters::GetParameter(int _paramID)
{
	try{
		return dynamic_cast<AudioProcessorParameter*>(GetSliderParams().at(_paramID));
	}
	catch (exception) {
	try {
		return dynamic_cast<AudioProcessorParameter*>(GetBoolParams().at(_paramID));
	}
	catch (exception) {
		return nullptr;
	}}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Returns the slider parameters as a Reference to a ParamDirectory
/// </summary>
const FloatParamDirectory& Processing::Parameters::GetSliderParams()
{
	return s_floatParams;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Returns the toggle parameters as a Reference to a ParamDirectory
/// </summary>
const BoolParamDirectory& Processing::Parameters::GetBoolParams()
{
	return s_boolParams;
}
