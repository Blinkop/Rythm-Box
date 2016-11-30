/*
==============================================================================

AudioRecroder.h
Created: 6 Sep 2016 3:41:32pm
Author:  Anthony

==============================================================================
*/

#ifndef AUDIORECRODER_H_INCLUDED
#define AUDIORECRODER_H_INCLUDED

#include "..\JuceLibraryCode\JuceHeader.h"
#include "ProcessorsGraph.h"

class AudioRecorder : public AudioProcessorPlayer
{
public:
	AudioRecorder(AudioThumbnail &TN);
	~AudioRecorder();

	void startRecording(const File &file);
	void stop();
	bool isRecording() const;
	void audioDeviceAboutToStart(AudioIODevice* device) override;
	void audioDeviceStopped() override;
	void audioDeviceIOCallback(const float** inputChannelData,
		int numInputChannels, float** outputChannelData,
		int numOutputChannels, int numSamples) override;

private:
	AudioThumbnail &thumbnail;
	TimeSliceThread backGroundThread;
	ScopedPointer<AudioFormatWriter::ThreadedWriter> threadedWriter;
	double sampleRate;
	int64 nextSampleNum;
	MidiBuffer incomingMidi;

	CriticalSection writerLock;
	AudioFormatWriter::ThreadedWriter* volatile activeWriter;
};


#endif  // AUDIORECRODER_H_INCLUDED

