/*
==============================================================================

AudioRecroder.cpp
Created: 6 Sep 2016 3:41:32pm
Author:  Anthony

==============================================================================
*/

#include "AudioRecorder.h"

AudioRecorder::AudioRecorder(AudioThumbnail &TN) : thumbnail(TN),
									backGroundThread("Audio	Recorder Thread"),
									sampleRate(0), nextSampleNum(0), activeWriter(nullptr)
{	
	backGroundThread.startThread();
}

AudioRecorder::~AudioRecorder()
{
	stop();
}

void AudioRecorder::startRecording(const File &file)
{
	stop();

	if (sampleRate > 0)
	{
		file.deleteFile();
		ScopedPointer<FileOutputStream> fileStream(file.createOutputStream());

		if (fileStream != nullptr)
		{
			WavAudioFormat wavFormat;
			AudioFormatWriter* writer = wavFormat.createWriterFor(fileStream, sampleRate, 1, 16, StringPairArray(), 0);

			if (writer != nullptr)
			{
				fileStream.release();
				threadedWriter = new AudioFormatWriter::ThreadedWriter(writer, backGroundThread, 32768);
				thumbnail.reset(writer->getNumChannels(), writer->getSampleRate());
				nextSampleNum = 0;

				const ScopedLock sl(writerLock);
				activeWriter = threadedWriter;
			}
		}
	}
}

void AudioRecorder::stop()
{
	{
		const ScopedLock sl(writerLock);
		activeWriter = nullptr;
	}
	threadedWriter = nullptr;
}

bool AudioRecorder::isRecording() const
{
	return activeWriter != nullptr;
}

void AudioRecorder::audioDeviceAboutToStart(AudioIODevice* device)
{
	sampleRate = device->getCurrentSampleRate();
}

void AudioRecorder::audioDeviceStopped()
{
	sampleRate = 0;
}

void AudioRecorder::audioDeviceIOCallback(
	const float** inputChannelData,
	int numInputChannels, float** outputChannelData,
	int numOutputChannels, int numSamples)
{
	const ScopedLock sl(writerLock);

	incomingMidi.clear();

	if (activeWriter != nullptr)
	{
		AudioBuffer<float> buffer(const_cast<float**>(inputChannelData), thumbnail.getNumChannels(), numSamples);
		
		activeWriter->write((const float**)buffer.getArrayOfWritePointers(), numSamples);

		thumbnail.addBlock(nextSampleNum, buffer, 0, numSamples);
		nextSampleNum += numSamples;
	}
	for (int i = 0; i < numOutputChannels; ++i)
	{
		if (outputChannelData[i] != nullptr)
		{
			FloatVectorOperations::clear(outputChannelData[i], numSamples);
		}
	}
}
