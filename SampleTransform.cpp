/*
  ==============================================================================

    SampleTransform.cpp
    Created: 26 Nov 2016 3:09:11am
    Author:  Anthony

  ==============================================================================
*/

#include "SampleTransform.h"

SampleTransform::SampleTransform()
									: freqForwardFFT(fftOrder, false)
{
	
}

SampleTransform::~SampleTransform()
{

}

void SampleTransform::processBlock(AudioBuffer<float>& buffer, MidiBuffer & midiMessages)
{
	/*float* leftChannel = buffer.getWritePointer(0);
	float* rightChannel = buffer.getWritePointer(1);*/

	/*Scanning only left channel cuz of identity of both right and left*/
	/*zeromem(fftData, sizeof(fftData));
	memcpy(fftData, leftChannel, buffer.getNumSamples() * sizeof(float));*/

	//freqForwardFFT.performFrequencyOnlyForwardTransform(fftData);
}

void SampleTransform::processBlock(AudioBuffer<double>& buffer, MidiBuffer & midiMessages)
{
	
}

void SampleTransform::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{
}

void SampleTransform::releaseResources()
{
}

void SampleTransform::processBlockBypassed(AudioBuffer<float>& buffer, MidiBuffer & midiMessages)
{
}

void SampleTransform::processBlockBypassed(AudioBuffer<double>& buffer, MidiBuffer& midiMessages)
{

}

void SampleTransform::getStateInformation(MemoryBlock & destData)
{
	
}

void SampleTransform::setStateInformation(const void * data, int sizeInBytes)
{
	
}

const String SampleTransform::getName() const								{ return "SampleTransform"; }
double SampleTransform::getTailLengthSeconds() const						{ return 0.0; }
bool SampleTransform::acceptsMidi() const									{ return false; }
bool SampleTransform::producesMidi() const									{ return false; }
AudioProcessorEditor * SampleTransform::createEditor()						{ return nullptr; }
bool SampleTransform::hasEditor() const										{ return false; }
int SampleTransform::getNumPrograms()										{ return 1; }
int SampleTransform::getCurrentProgram()									{ return 0; }
void SampleTransform::setCurrentProgram(int index)							{}
const String SampleTransform::getProgramName(int index)						{ return ""; }
void SampleTransform::changeProgramName(int index, const String & newName)	{}
