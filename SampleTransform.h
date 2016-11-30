/*
  ==============================================================================

    SampleTransform.h
    Created: 26 Nov 2016 3:09:11am
    Author:  Anthony

  ==============================================================================
*/

#ifndef SAMPLETRANSFORM_H_INCLUDED
#define SAMPLETRANSFORM_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class SampleTransform : public AudioProcessor
{
public:
	SampleTransform();
	~SampleTransform();

	const String getName() const override;

	void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;
	void processBlock(AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override;

	void prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock) override;

	void releaseResources() override;
	void processBlockBypassed(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;
	void processBlockBypassed(AudioBuffer<double>& buffer, MidiBuffer& midiMessages) override;
	double getTailLengthSeconds() const override;
	bool acceptsMidi() const override;
	bool producesMidi() const override;
	AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	void changeProgramName(int index, const String& newName) override;
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;
private:
	enum
	{
		fftOrder = 9,
		fftSize = 1 << fftOrder
	};
	FFT freqForwardFFT;

	float fftData[fftSize];
};


#endif  // SAMPLETRANSFORM_H_INCLUDED
