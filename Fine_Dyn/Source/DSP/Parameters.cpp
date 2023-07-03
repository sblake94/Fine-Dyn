#include "Parameters.h"

using namespace DSP;

namespace DSP 
{
	// NOTE: I'm dubious about these being static, but I don't think we're doing any multi-threaded access to them, so it should be fine.

	
	AudioParameterBool Parameters::s_masterBypass = AudioParameterBool(s_masterBypassParamID, juce::String("Master Bypass"), false);
	AudioParameterFloat Parameters::s_masterGain = AudioParameterFloat(s_masterGainParamID, juce::String("Master Gain"), -6.0f, 6.0f, 0.0f);

	AudioParameterFloat Parameters::s_threshold = AudioParameterFloat(s_thresholdParamID, juce::String("Threshold"), -96.0f, 6.0f, -0.0f);
	AudioParameterFloat Parameters::s_ratio = AudioParameterFloat(s_ratioParamID, juce::String("Ratio"), 1.0f, 20.0f, 1.0f);

	FloatParamDirectory Parameters::s_floatParams = FloatParamDirectory
	{
		{ s_masterGainParamID, &s_masterGain },
		{ s_thresholdParamID, &s_threshold },
		{ s_ratioParamID, &s_ratio }

	};

	BoolParamDirectory Parameters::s_boolParams = BoolParamDirectory
	{
		{ s_masterBypassParamID, &s_masterBypass },
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
const juce::AudioProcessorParameter* DSP::Parameters::GetParameter(int _paramID)
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
const FloatParamDirectory& DSP::Parameters::GetSliderParams()
{
	return s_floatParams;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Returns the toggle parameters as a Reference to a ParamDirectory
/// </summary>
const BoolParamDirectory& DSP::Parameters::GetBoolParams()
{
	return s_boolParams;
}
