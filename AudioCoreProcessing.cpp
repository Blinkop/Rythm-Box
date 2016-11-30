/*
  ==============================================================================

    AudioCoreProcessing.cpp
    Created: 25 Oct 2016 9:27:12pm
    Author:  Anthony

  ==============================================================================
*/

#include "AudioCoreProcessing.h"

AudioCoreProcessing::AudioCoreProcessing(ProcessorsGraph& pGraph)
																: processorsGraph(pGraph)
{
	
}

AudioCoreProcessing::~AudioCoreProcessing()
{

}

void AudioCoreProcessing::processAudio(const File& file)
{
	this->setProcessor(&processorsGraph);
	processorsGraph.startProcess(file);
}

void AudioCoreProcessing::stop()
{
	processorsGraph.stop();
	this->setProcessor(nullptr);
}

bool AudioCoreProcessing::isProcessing() const
{
	return processorsGraph.isProcessing();
}
