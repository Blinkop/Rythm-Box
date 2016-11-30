/*
  ==============================================================================

    RecordingProcessor.cpp
    Created: 6 Nov 2016 2:14:37am
    Author:  Anthony

  ==============================================================================
*/

#include "RecordingProcessor.h"

RecordingProcessor::RecordingProcessor(AudioThumbnail& TN)
															: thumbnail(TN),
															  backGroundThread("Audio Recording processor"),
															  sampleRate(0),
															  nextSampleNum(0),
															  activeWriter(nullptr)
{
	backGroundThread.startThread();
}

RecordingProcessor::~RecordingProcessor()
{
	stop();
}

void RecordingProcessor::startRecording(const File & file)
{
	stop();

	if (sampleRate > 0)
	{
		file.deleteFile();
		ScopedPointer<FileOutputStream> fileStream(file.createOutputStream());

		if (fileStream != nullptr)
		{
			WavAudioFormat wavFormat;
			AudioFormatWriter* writer = wavFormat.createWriterFor(fileStream, sampleRate, 2, 16, StringPairArray(), 0);

			if (writer != nullptr)
			{
				fileStream.release();
				threadedWriter = new AudioFormatWriter::ThreadedWriter(writer, backGroundThread, 32768);
				thumbnail.reset(writer->getNumChannels(), writer->getSampleRate());
				nextSampleNum = 0;

				const ScopedLock sl(this->getCallbackLock());
				activeWriter = threadedWriter;
			}
		}
	}
}

void RecordingProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer & midiMessages)
{
	if (activeWriter != nullptr)
	{
		activeWriter->write((const float**)buffer.getArrayOfWritePointers(), buffer.getNumSamples());

		thumbnail.addBlock(nextSampleNum, buffer, 0, buffer.getNumSamples());
		nextSampleNum += buffer.getNumSamples();
	}
}

void RecordingProcessor::processBlock(AudioBuffer<double>& buffer, MidiBuffer & midiMessages)
{
	if (activeWriter != nullptr)
	{
		activeWriter->write((const float**)buffer.getArrayOfWritePointers(), buffer.getNumSamples());

		/*Double precission promlem*/
		//thumbnail.addBlock(nextSampleNum, buffer, 0, buffer.getNumSamples());
		nextSampleNum += buffer.getNumSamples();
	}
}

void RecordingProcessor::prepareToPlay(double sampleRate, int maximumExpectedSamplesPerBlock)
{
	this->sampleRate = getSampleRate();
}

void RecordingProcessor::releaseResources()
{
	sampleRate = 0;
}

void RecordingProcessor::processBlockBypassed(AudioBuffer<float>& buffer, MidiBuffer & midiMessages)
{
}

void RecordingProcessor::processBlockBypassed(AudioBuffer<double>& buffer, MidiBuffer& midiMessages)
{

}

void RecordingProcessor::getStateInformation(MemoryBlock & destData)
{
}

void RecordingProcessor::setStateInformation(const void * data, int sizeInBytes)
{
}

bool RecordingProcessor::isRecording() const
{
	return activeWriter != nullptr;
}

void RecordingProcessor::stop()
{
	{
		const ScopedLock sl(this->getCallbackLock());
		activeWriter = nullptr;
	}
	threadedWriter = nullptr;
}

const String RecordingProcessor::getName() const								{ return "RecordingProcessor"; }
double RecordingProcessor::getTailLengthSeconds() const							{ return 0.0; }
bool RecordingProcessor::acceptsMidi() const									{ return false; }
bool RecordingProcessor::producesMidi() const									{ return false; }
AudioProcessorEditor * RecordingProcessor::createEditor()						{ return nullptr; }
bool RecordingProcessor::hasEditor() const										{ return false; }
int RecordingProcessor::getNumPrograms()										{ return 1; }
int RecordingProcessor::getCurrentProgram()										{ return 0; }
void RecordingProcessor::setCurrentProgram(int index)							{}
const String RecordingProcessor::getProgramName(int index)						{ return ""; }
void RecordingProcessor::changeProgramName(int index, const String & newName)	{}
