/*
  ==============================================================================

    RecordingProcessor.h
    Created: 6 Nov 2016 2:14:37am
    Author:  Anthony

  ==============================================================================
*/

#ifndef RECORDINGPROCESSOR_H_INCLUDED
#define RECORDINGPROCESSOR_H_INCLUDED

#include "..\JuceLibraryCode\JuceHeader.h"

class RecordingProcessor : public AudioProcessor
{
public:
	RecordingProcessor(AudioThumbnail& TN);
	~RecordingProcessor();

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

	bool isRecording() const;
	void startRecording(const File& file);
	void stop();
private:
	AudioThumbnail &thumbnail;
	TimeSliceThread backGroundThread;

	AudioFormatWriter::ThreadedWriter* volatile activeWriter;
	ScopedPointer<AudioFormatWriter::ThreadedWriter> threadedWriter;
	
	double sampleRate;
	int64 nextSampleNum;

};



#endif  // RECORDINGPROCESSOR_H_INCLUDED
