/*
==============================================================================

StaticIntesfaceComponent.h
Created: 7 May 2016 5:27:28pm
Author:  Anthony

==============================================================================
*/

#ifndef STATICINTESFACECOMPONENT_H_INCLUDED
#define STATICINTESFACECOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioRecorder.h"
#include "RecordingThumbnail.h"
#include "AudioLiveScrollingDisplay.h"
#include "PlaybackThumbnail.h"
#include "AudioCoreProcessing.h"

class MainScene : public Component,
				  private Button::Listener,
				  private Slider::Listener,
				  private ChangeListener
{
public:
	MainScene();
	~MainScene();

	void paint(Graphics &g) override;
	void resized() override;

	void buttonClicked(Button* button) override;
	void sliderValueChanged(Slider* sliderThatWasMoved) override;
	void changeListenerCallback(ChangeBroadcaster* source) override;
private:
	DrawableButton recordDrawableButton;
	Slider modeSlider;
	Slider zoomSlider;							//controll slider
	ToggleButton playRecordSwitch;
	ToggleButton followTransportButton;

	LiveScrollingAudioDisplay liveAudioScroller;
	ScopedPointer<AudioFormatReaderSource> currentAudioFileSource;

	AudioDeviceManager&	deviceManager;
	AudioRecorder recorder;

	AudioCoreProcessing coreProcessor;
	ProcessorsGraph processorsGraph;

	RecordingThumbnail recordingThumbnail;
	PlaybackThumbnail playbackThumbnail;

	AudioTransportSource transportSource;
	AudioSourcePlayer audioSourcePlayer;
	TimeSliceThread timeSliceThread;

	Component* currentThumbnail;

	String lastAudioFileFullPath;
	String lastAudioFile;
	bool Record;
	bool Stopped;
	Rectangle<int> SI_demension;

	static ScopedPointer<AudioDeviceManager> sharedAudioDeviceManager;

	static AudioDeviceManager& getSharedAudioDeviceManager();

	void startRecording();
	void stopRecording();
	void startPlay();
	void stopPlay();

	void switchToPlayMode();
	void switchToRecordMode();

	void showFile(const File& file);
	void loadFileIntoTransport(const File& audioFile);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainScene)
};



#endif  // STATICINTESFACECOMPONENT_H_INCLUDED
