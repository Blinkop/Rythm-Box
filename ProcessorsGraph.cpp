/*
  ==============================================================================

    ProcessorsGraph.cpp
    Created: 25 Oct 2016 10:07:43pm
    Author:  Anthony

  ==============================================================================
*/
/*
  ==============================================================================
	 Default graph state:
  ------------------------------------------------------------------------------
  |			INPUT -> NOISEGATE -> SAMPLETRANSFORM -> RECORDER -> OUTPUT		   |
  ------------------------------------------------------------------------------
  Noise Gate: provides clear sound detection to avoid any kind of noise analyze
  Sample Transform: analyze and transforms the source signal to defined samples
	witch are stored in kit's location.
  ==============================================================================
*/

#include "ProcessorsGraph.h"

ProcessorsGraph::ProcessorsGraph(AudioThumbnail& TN)
{
	noiseGate = new NoiseGate();
	sampleTransform = new SampleTransform();
	recordingProcessor = new RecordingProcessor(TN);

	input = new AudioProcessorGraph::AudioGraphIOProcessor
		(AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode);
	output = new AudioProcessorGraph::AudioGraphIOProcessor
		(AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode);

	this->addNode(input, 1);
	this->addNode(output, 2);
	this->addNode(recordingProcessor, 3);
	this->addNode(noiseGate, 4);
	this->addNode(sampleTransform, 5);

	this->addConnection(1, 0, 4, 0);					//LEFT : INPUT->NOISEGATE
	this->addConnection(1, 1, 4, 1);					//RIGHT : INPUT->NOISEGATE
	this->addConnection(4, 0, 5, 0);					//LEFT : NOISEGATE->SAMPLETRANSFORM
	this->addConnection(4, 1, 5, 1);					//RIGHT : NOISEGATE->SAMPLETRANSFORM
	this->addConnection(5, 0, 3, 0);					//LEFT : SAMPLETRANSFORM->RECORDER
	this->addConnection(5, 1, 3, 1);					//RIGHT : SAMPLETRANSFORM->RECORDER
	this->addConnection(3, 0, 2, 0);					//LEFT : RECORDER->OUTPUT
	this->addConnection(3, 1, 2, 1);					//RIGHT : RECORDER->OUTPUT
}

ProcessorsGraph::~ProcessorsGraph()
{
	this->clear();
}

void ProcessorsGraph::startProcess(const File& file)
{
	recordingProcessor->startRecording(file);
}

void ProcessorsGraph::stop()
{
	recordingProcessor->stop();
}

bool ProcessorsGraph::isProcessing() const
{
	return recordingProcessor->isRecording();
}


