/*
  ==============================================================================

    AudioCoreProcessing.h
    Created: 25 Oct 2016 9:27:12pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef AUDIOCOREPROCESSING_H_INCLUDED
#define AUDIOCOREPROCESSING_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ProcessorsGraph.h"

class AudioCoreProcessing : public AudioProcessorPlayer
{
public:
	AudioCoreProcessing(ProcessorsGraph& pGraph);
	~AudioCoreProcessing();

	void processAudio(const File& file);
	void stop();

	bool isProcessing() const;
private:
	ProcessorsGraph& processorsGraph;
};


#endif  // AUDIOCOREPROCESSING_H_INCLUDED
