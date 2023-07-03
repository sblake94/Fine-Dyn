#include "FineDynProcessing.h"
#include "Parameters.h"

using namespace DSP;

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
FineDynProcessing::FineDynProcessing()
{
	floatingPointDitherL = 1.0; while (floatingPointDitherL < 16386) floatingPointDitherL = rand() * UINT32_MAX;
	floatingPointDitherR = 1.0; while (floatingPointDitherR < 16386) floatingPointDitherR = rand() * UINT32_MAX;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
/// </summary>
FineDynProcessing::~FineDynProcessing()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Process the audio buffer
/// </summary>
/// <param name="_inputBuffer"></param>
/// <param name="_outputBuffer"></param>
/// <param name="_params"></param>
/// <param name="_sampleRate"></param>
void FineDynProcessing::ProcessReplacing
(
	juce::AudioBuffer<float>& _inputBuffer,
	juce::AudioBuffer<float>& _outputBuffer,
	const int _sampleRate
)
{
	// Bypass Logic
	if (Parameters::GetBoolParams().at(s_masterBypassParamID)->get() == true) 
		{ _outputBuffer = _inputBuffer; return; }

	juce::AudioBuffer<float>& tempBuffer = _inputBuffer;

	// Do the processing
	// ...

	_outputBuffer = tempBuffer;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Applies a sine curve to the buffer
/// </summary>
/// <param name="_buffer"></param>
/// <param name="_sampleFrames"></param>
void FineDynProcessing::ApplyCurve(juce::AudioSampleBuffer& _buffer)
{
	for (int sampleIdx = 0; sampleIdx < _buffer.getNumSamples(); sampleIdx++)
	{
		// Get the sample
		double sampleL = _buffer.getSample(0, sampleIdx);
		double sampleR = _buffer.getSample(1, sampleIdx);
				
		sampleL = sin(sampleL);
		sampleR = sin(sampleR);

		_buffer.setSample(0, sampleIdx, sampleL);
		_buffer.setSample(1, sampleIdx, sampleR);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Applies an inverse sine curve to the buffer
/// </summary>
/// <param name="_buffer"></param>
/// <param name="_sampleFrames"></param>
void FineDynProcessing::RemoveCurve(juce::AudioSampleBuffer& _buffer)
{
	Clip(_buffer, -1.0, 1.0);

	for (int sampleIdx = 0; sampleIdx < _buffer.getNumSamples(); sampleIdx++)
	{
		// Get the sample
		double sampleL = _buffer.getSample(0, sampleIdx);
		double sampleR = _buffer.getSample(1, sampleIdx);

		sampleL = asin(sampleL);
		sampleR = asin(sampleR);

		_buffer.setSample(0, sampleIdx, sampleL);
		_buffer.setSample(1, sampleIdx, sampleR);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Clip the output to prevent amplitude spikes
/// </summary>
/// <param name="_buffer"></param>
/// <param name="_min"></param>
/// <param name="_max"></param>
void FineDynProcessing::Clip
(
	juce::AudioSampleBuffer& _buffer,
	double _min,
	double _max
)
{
	for (int sampleIdx = 0; sampleIdx < _buffer.getNumSamples(); sampleIdx++)
	{
		// Get the sample
		double sampleL = _buffer.getSample(0, sampleIdx);
		double sampleR = _buffer.getSample(1, sampleIdx);

		if (sampleL > _max) sampleL = _max;
		if (sampleL < _min) sampleL = _min;
		if (sampleR > _max) sampleR = _max;
		if (sampleR < _min) sampleR = _min;

		_buffer.setSample(0, sampleIdx, sampleL);
		_buffer.setSample(1, sampleIdx, sampleR);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// Apply Gain to the buffer
/// </summary>
/// <param name="_buffer"></param>
/// <param name="_gainDB"></param>
void FineDynProcessing::ApplyGainDB
(
	juce::AudioSampleBuffer& _buffer,
	const float const& _gainDB
)
{
	const double gain = Decibels::decibelsToGain(_gainDB);

	for (int sampleIdx = 0; sampleIdx < _buffer.getNumSamples(); sampleIdx++)
	{
		// Get the sample
		double sampleL = _buffer.getSample(0, sampleIdx);
		double sampleR = _buffer.getSample(1, sampleIdx);

		if(fabs(sampleL) < 1.018e-23) sampleL = floatingPointDitherL * 1.18e-17;
		if(fabs(sampleR) < 1.018e-23) sampleR = floatingPointDitherR * 1.18e-17;

		sampleL *= gain;
		sampleR *= gain;

		DitherStereoSample(sampleL, sampleR);

		_buffer.setSample(0, sampleIdx, sampleL);
		_buffer.setSample(1, sampleIdx, sampleR);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// The following Dither function is based on a technique designbed by Chris from Airwindows, 
/// many thanks @Chris for his open-source wonder-code!
/// This dither technique is applied in most, if not all, of his plugins.
/// Please check out his work at: https://www.airwindows.com/
/// Or his github at: https://github.com/airwindows/airwindows
/// </summary>
/// <param name="sampleL"></param>
/// <param name="sampleR"></param>
void FineDynProcessing::DitherStereoSample
(
	double& sampleL, 
	double& sampleR
)
{
	int exponent;

	frexpf((float)sampleL, &exponent);
	floatingPointDitherL ^= floatingPointDitherL << 13;
	floatingPointDitherL ^= floatingPointDitherL >> 17;
	floatingPointDitherL ^= floatingPointDitherL << 5;
	sampleL += ((double(floatingPointDitherL) - uint32_t(0x7fffffff)) * 5.5e-361 * pow(2, exponent + 62));

	frexpf((float)sampleR, &exponent);
	floatingPointDitherR ^= floatingPointDitherR << 13;
	floatingPointDitherR ^= floatingPointDitherR >> 17;
	floatingPointDitherR ^= floatingPointDitherR << 5;
	sampleR += ((double(floatingPointDitherR) - uint32_t(0x7fffffff)) * 5.5e-361 * pow(2, exponent + 62));
}