#include "BiquadUnit.h"
#include "Parameters.h"

using namespace Processing;


//////////////////////////////////////////////////////////////////
/// <summary>
/// Constructor
/// </summary>
BiquadUnit::BiquadUnit()
{
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Destructor
///	</summary>
BiquadUnit::~BiquadUnit()
{
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Applies the biquad filter to the input buffer and stores the
/// result in the output buffer
/// </summary>
/// <param name="_inputBuffer">The input buffer</param>
/// <param name="_outputBuffer">The output buffer</param>
/// <param name="_params">The parameters</param>
/// <param name="_filterType">The filter type</param>
/// <param name="_sampleRate">The sample rate</param>
/// <param name="_sampleFrames">The number of sample frames</param>
void BiquadUnit::ApplyBiquad
(
	juce::AudioBuffer<float>& _buffer,
	const FilterType _filterType,
	const int _sampleRate
)
{
	// Get the parameters
	FloatParamDirectory sliderParams = Processing::Parameters::GetSliderParams();

	// Pick filter type
	switch (_filterType) 
	{
		case FilterType::HighShelf:
			SetHighShelfCoeffs(_sampleRate);
			break;

		case FilterType::PeakShelf:
			SetPeakShelfCoeffs(_sampleRate);
			break;

		case FilterType::LowShelf:
			SetLowShelfCoeffs(_sampleRate);
			break;

		// ... other filter types go here ...

		default:
			throw new std::exception("Invalid filter type");
	}

	// Process the samples
	for (int sampleIdx = 0; sampleIdx < _buffer.getNumSamples(); sampleIdx++)
	{
		const double inputSampleL = _buffer.getSample(0, sampleIdx);
		const double inputSampleR = _buffer.getSample(1, sampleIdx);

		double tempSampleL =
			(m_b0 / m_a0) * inputSampleL +
			(m_b1 / m_a0) * m_in1L +
			(m_b2 / m_a0) * m_in2L -
			(m_a1 / m_a0) * m_out1L -
			(m_a2 / m_a0) * m_out2L;

		double tempSampleR =
			(m_b0 / m_a0) * inputSampleR +
			(m_b1 / m_a0) * m_in1R +
			(m_b2 / m_a0) * m_in2R -
			(m_a1 / m_a0) * m_out1R -
			(m_a2 / m_a0) * m_out2R;

		// Clip both channels
		if (tempSampleL > 1.0) tempSampleL = 1.0;
		if (tempSampleL < -1.0) tempSampleL = -1.0;
		if (tempSampleR > 1.0) tempSampleR = 1.0;
		if (tempSampleR < -1.0) tempSampleR = -1.0;

		m_in2L = m_in1L;
		m_in1L = inputSampleL;
		m_out2L = m_out1L;
		m_out1L = tempSampleL;

		m_in2R = m_in1R;
		m_in1R = inputSampleR;
		m_out2R = m_out1R;
		m_out1R = tempSampleR;

		_buffer.setSample(0, sampleIdx, tempSampleL);
		_buffer.setSample(1, sampleIdx, tempSampleR);
	}
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the shared coefficients for a shelf filter
/// </summary>
/// <param name="_gain">The gain</param>
/// <param name="_cutoff">The cutoff frequency</param>
/// <param name="_sliderParams">The slider parameters</param>
/// <param name="_sampleRate">The sample rate</param>
void BiquadUnit::SetShelfCoeffs
(
	const float _gain, 
	const float _cutoff,
	const float _bandwidth,
	const int _sampleRate
)
{
	A = pow(10.0, _gain / 40.0);
	w0 = juce::MathConstants<double>::twoPi * _cutoff / _sampleRate;
	cosw0 = cos(w0);
	sinw0 = sin(w0);
	alpha = sinw0 * sinh((log10(2) / 2) * _bandwidth * (w0 / sinw0));
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the coefficients for a High shelf filter
/// </summary>
/// <param name="_sliderParams">The slider parameters</param>
/// <param name="_sampleRate">The sample rate</param>
/// 
void BiquadUnit::SetHighShelfCoeffs
(
	const int _sampleRate
)
{
	const float hfCutoff = *(Processing::Parameters::GetSliderParams().at(s_highFreqCutoffParamID));
	const float hfGain = *(Processing::Parameters::GetSliderParams().at(s_highGainParamID));
	const float hfBW = *(Processing::Parameters::GetSliderParams().at(s_highBandwidthParamID));

	SetShelfCoeffs(hfGain, hfCutoff, hfBW, _sampleRate);

	m_b0 = A * ((A + 1) + (A - 1) * cosw0 + 2 * sqrt(A * alpha));
	m_b1 = -2 * A * ((A - 1) + (A + 1) * cosw0);
	m_b2 = A * ((A + 1) + (A - 1) * cosw0 - 2 * sqrt(A * alpha));
	m_a0 = (A + 1) - (A - 1) * cosw0 + 2 * sqrt(A * alpha);
	m_a1 = 2 * ((A - 1) - (A + 1) * cosw0);
	m_a2 = (A + 1) - (A - 1) * cosw0 - 2 * sqrt(A * alpha);
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the coefficients for a Peak shelf filter
/// </summary>
/// <param name="_sliderParams">The slider parameters</param>
/// <param name="_sampleRate">The sample rate</param>
void BiquadUnit::SetPeakShelfCoeffs
(
	const int _sampleRate
)
{
	const float peakCutoff = *(Processing::Parameters::GetSliderParams().at(s_midFreqCutoffParamID));
	const float peakGain = *(Processing::Parameters::GetSliderParams().at(s_midGainParamID));
	const float peakBW = *(Processing::Parameters::GetSliderParams().at(s_midBandwidthParamID));

	SetShelfCoeffs(peakGain, peakCutoff, peakBW, _sampleRate);

	m_b0 = 1 + alpha * A;
	m_b1 = -2 * cosw0;
	m_b2 = 1 - alpha * A;
	m_a0 = 1 + alpha / A;
	m_a1 = -2 * cosw0;
	m_a2 = 1 - alpha / A;
}

//////////////////////////////////////////////////////////////////
/// <summary>
/// Sets the coefficients for a Low shelf filter
/// </summary>
/// <param name="_sliderParams">The slider parameters</param>
/// <param name="_sampleRate">The sample rate</param>
void BiquadUnit::SetLowShelfCoeffs
(
	const int _sampleRate
)
{
	const float lfCutoff = *(Processing::Parameters::GetSliderParams().at(s_lowFreqCutoffParamID));
	const float lfGain = *(Processing::Parameters::GetSliderParams().at(s_lowGainParamID));
	const float lfBW = *(Processing::Parameters::GetSliderParams().at(s_lowBandwidthParamID));

	SetShelfCoeffs(lfGain, lfCutoff, lfBW, _sampleRate);

	m_b0 = A * ((A + 1) - (A - 1) * cosw0 + 2 * sqrt(A * alpha));
	m_b1 = 2 * A * ((A - 1) - (A + 1) * cosw0);
	m_b2 = A * ((A + 1) - (A - 1) * cosw0 - 2 * sqrt(A * alpha));
	m_a0 = (A + 1) + (A - 1) * cosw0 + 2 * sqrt(A * alpha);
	m_a1 = -2 * ((A - 1) + (A + 1) * cosw0);
	m_a2 = (A + 1) + (A - 1) * cosw0 - 2 * sqrt(A * alpha);
}
