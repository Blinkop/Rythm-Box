/*
  ==============================================================================

    NoiseGate.cpp
    Created: 30 Oct 2016 3:44:01pm
    Author:  Anthony

  ==============================================================================
*/

#include "NoiseGate.h"

NoiseGate::NoiseGate()
{
	addParameter(threshold = new AudioParameterFloat("threshold", "Threshold", 0.0f, 1.0f, 0.005f));
}

NoiseGate::~NoiseGate()
{

}

void NoiseGate::processBlock(AudioBuffer<float>& buffer, MidiBuffer & midiMessages)
{
	if (buffer.getRMSLevel(0, 0, buffer.getNumSamples()) < threshold->get())
	{
		buffer.applyGain(0.0f);
	}
}

void NoiseGate::processBlock(AudioBuffer<double>& buffer, MidiBuffer & midiMessages)
{
	double* leftChannel = buffer.getArrayOfWritePointers()[0];
	double* rightChannel = buffer.getArrayOfWritePointers()[1];

	if (buffer.getRMSLevel(0, 0, buffer.getNumSamples()) < threshold->get())
	{
		buffer.applyGain(0.0);
	}
}

void NoiseGate::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{
}

void NoiseGate::releaseResources()
{
}

void NoiseGate::processBlockBypassed(AudioBuffer<float>& buffer, MidiBuffer & midiMessages)
{
}

void NoiseGate::processBlockBypassed(AudioBuffer<double>& buffer, MidiBuffer& midiMessages)
{

}

void NoiseGate::getStateInformation(MemoryBlock & destData)
{
	MemoryOutputStream stream(destData, true);

	stream.writeFloat(*threshold);
}

void NoiseGate::setStateInformation(const void * data, int sizeInBytes)
{
	MemoryInputStream stream(data, static_cast<size_t> (sizeInBytes), false);

	threshold->setValueNotifyingHost(stream.readFloat());
}

const String NoiseGate::getName() const									{ return "NoiseGate"; }
double NoiseGate::getTailLengthSeconds() const							{ return 0.0; }
bool NoiseGate::acceptsMidi() const										{ return false; }
bool NoiseGate::producesMidi() const									{ return false; }
AudioProcessorEditor * NoiseGate::createEditor()						{ return nullptr; }
bool NoiseGate::hasEditor() const										{ return false; }
int NoiseGate::getNumPrograms()											{ return 1; }
int NoiseGate::getCurrentProgram()										{ return 0; }
void NoiseGate::setCurrentProgram(int index)							{}
const String NoiseGate::getProgramName(int index)						{ return ""; }
void NoiseGate::changeProgramName(int index, const String & newName)	{}
