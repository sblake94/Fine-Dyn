#pragma once

#include "Parameters.h"
#include "BiquadUnit.h"

namespace Processing
{
	///////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Dedicated class for holding all DSP logic
	/// In this class we use a dithering tecnique designed by Chris from Airwindows.
	/// Credit for the technique goes to him.
	/// 
	/// Please check his website and github for more info:
	/// https://www.airwindows.com/
	/// https://github.com/airwindows/airwindows
	/// 
	/// </summary>
	class BiquadProcessing
	{
	public: //////////////////////////////////////////////////////////////////

		BiquadProcessing();
		~BiquadProcessing();

		void ProcessReplacing
		(
			juce::AudioBuffer<float>& _inputBuffer,
			juce::AudioBuffer<float>& _outputBuffer,
			const int _sampleRate
		);

		void ApplyCurve(juce::AudioSampleBuffer& _buffer);
		void RemoveCurve(juce::AudioSampleBuffer& _buffer);

		void Clip
		(
			juce::AudioSampleBuffer& _buffer,
			double _min,
			double _max
		);

		void ApplyGainDB
		(
			juce::AudioSampleBuffer& _buffer,
			const float const& _gainDB
		);

		void DitherStereoSample(double& sampleL, double& sampleR);

	private://////////////////////////////////////////////////////////////////

		BiquadUnit m_biquadA;
		BiquadUnit m_biquadB;
		BiquadUnit m_biquadC;

		uint32_t floatingPointDitherL;
		uint32_t floatingPointDitherR;
	};
}