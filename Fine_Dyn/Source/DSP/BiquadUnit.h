#pragma once

#include "Parameters.h"

namespace Processing
{
	/////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Holds all Logic and State of a Biquad Filter Instance
	/// </summary>
	class BiquadUnit
	{
	public://////////////////////////////////////////////////////////////////

		BiquadUnit();
		~BiquadUnit();

		enum FilterType
		{
			HighShelf,
			PeakShelf,
			LowShelf
		};

		void ApplyBiquad(
			juce::AudioBuffer<float>& _buffer,
			const FilterType _filterType,
			const int _sampleRate
		);

		void SetHighShelfCoeffs(const int _sampleRate);
		void SetPeakShelfCoeffs(const int _sampleRate);
		void SetLowShelfCoeffs(const int _sampleRate);

	private://////////////////////////////////////////////////////////////////

		void SetShelfCoeffs(
			const float _gain,
			const float _cutoff,
			const float _bandwidth,
			const int _sampleRate);

		// Biquad Coefficients
		double m_b0, m_b1, m_b2, m_a0, m_a1, m_a2;
		double m_in1L, m_in2L, m_out1L, m_out2L;
		double m_in1R, m_in2R, m_out1R, m_out2R;


		// Peak/Shelf Coefficients
		double A, w0, cosw0, sinw0, alpha;
	};
}