/*
  ==============================================================================

    ProcessorsGraph.h
    Created: 25 Oct 2016 10:07:43pm
    Author:  Anthony

  ==============================================================================
*/

#ifndef PROCESSORSGRAPH_H_INCLUDED
#define PROCESSORSGRAPH_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "NoiseGate.h"
#include "RecordingProcessor.h"
#include "SampleTransform.h"

class ProcessorsGraph : public AudioProcessorGraph
{
public:
	ProcessorsGraph(AudioThumbnail& TN);
	~ProcessorsGraph();

	void startProcess(const File& file);
	void stop();

	bool isProcessing() const;
private:
	NoiseGate* noiseGate;
	SampleTransform* sampleTransform;
	RecordingProcessor* recordingProcessor;

	AudioProcessorGraph::AudioGraphIOProcessor* input;
	AudioProcessorGraph::AudioGraphIOProcessor* output;
};


#endif  // PROCESSORSGRAPH_H_INCLUDED
