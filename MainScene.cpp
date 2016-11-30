/*
==============================================================================

StaticIntesfaceComponent.cpp
Created: 7 May 2016 5:28:01pm
Author:  Anthony

==============================================================================
*/

#include "MainScene.h"

ScopedPointer<AudioDeviceManager> MainScene::sharedAudioDeviceManager = nullptr;

MainScene::MainScene()
					  : deviceManager(MainScene::getSharedAudioDeviceManager()),
						processorsGraph(recordingThumbnail.getAudioThumbnail()),
						coreProcessor(processorsGraph),
					    recorder(recordingThumbnail.getAudioThumbnail()),
						recordDrawableButton("Record", DrawableButton::ButtonStyle::ImageAboveTextLabel),
						playbackThumbnail(transportSource, zoomSlider),
						timeSliceThread("audio file preview")
{
	setOpaque(true);
	addAndMakeVisible(liveAudioScroller);
	playbackThumbnail.setFollowsTransport(false);

	Record = true;
	Stopped = true;
	lastAudioFile = "\\Recorded\\Just a test";
	lastAudioFileFullPath = File::getSpecialLocation(File::userDocumentsDirectory).getFullPathName() + lastAudioFile + ".wav";

	zoomSlider.setRange(0, 1, 0);
	zoomSlider.setSliderStyle(Slider::LinearHorizontal);
	zoomSlider.addListener(this);
	zoomSlider.setSkewFactor(2);

	playbackThumbnail.addChangeListener(this);

	timeSliceThread.startThread(3);

	currentThumbnail = &recordingThumbnail;

	DrawablePath drawableNormal, drawableOver, drawableDown;
	Path path;
	path.addEllipse(120, 250, 100, 100);

	drawableNormal.setPath(path);
	drawableNormal.setFill(Colours::mediumslateblue);
	drawableNormal.setStrokeFill(Colours::cornflowerblue);
	drawableNormal.setStrokeThickness(1.0f);

	drawableOver.setPath(path);
	drawableOver.setFill(Colours::blue);
	drawableOver.setStrokeFill(Colours::aliceblue);
	drawableOver.setStrokeThickness(1.0f);

	drawableDown.setPath(path);
	drawableDown.setFill(Colours::deepskyblue);
	drawableDown.setStrokeFill(Colours::deepskyblue);
	drawableDown.setStrokeThickness(1.0f);

	recordDrawableButton.setImages(&drawableNormal, &drawableOver, &drawableDown);
	recordDrawableButton.addListener(this);
	recordDrawableButton.setClickingTogglesState(true);

	modeSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
	modeSlider.setValue(0.0);
	modeSlider.setRange(0.0, 1.0);

	playRecordSwitch.setButtonText("Play/Record");
	playRecordSwitch.addListener(this);
	playRecordSwitch.setClickingTogglesState(true);

	addAndMakeVisible(playRecordSwitch);
	addAndMakeVisible(recordingThumbnail);
	addAndMakeVisible(recordDrawableButton);
	addAndMakeVisible(modeSlider);

	deviceManager.addAudioCallback(&liveAudioScroller);
	deviceManager.addAudioCallback(&coreProcessor);
	
	audioSourcePlayer.setSource(&transportSource);
}
MainScene::~MainScene()
{
	recordDrawableButton.removeListener(this);
	playRecordSwitch.removeListener(this);
	deviceManager.removeAudioCallback(&coreProcessor);
	deviceManager.removeAudioCallback(&liveAudioScroller);

	transportSource.setSource(nullptr);
	audioSourcePlayer.setSource(nullptr);

	sharedAudioDeviceManager = nullptr;
}
void MainScene::paint(Graphics &g)
{
	playbackThumbnail.setBounds(0, 0, SI_demension.getWidth(), SI_demension.getHeight() / 5);
	Font mcF("Times New Roman", 20.0f, Font::bold | Font::italic);
	g.fillAll(Colours::indigo);
	g.setFont(mcF);
	g.setColour(Colour(0xffffffff));
	g.drawText("Test", getLocalBounds(), Justification::centredBottom, true);
}
void MainScene::resized()
{
	SI_demension = getLocalBounds();
	recordDrawableButton.setBounds(SI_demension.getWidth() / 20,
								   4 * SI_demension.getHeight() / 9,
								   8 * SI_demension.getWidth() / 10,
								   8 * SI_demension.getWidth() / 10);
	currentThumbnail->setBounds(0,
								0,
								SI_demension.getWidth(),
								SI_demension.getHeight() / 5);
	modeSlider.setBounds(17 * SI_demension.getWidth() / 20,
						 4 * SI_demension.getHeight() / 9,
						 SI_demension.getWidth() / 20,
						 4 * SI_demension.getHeight() / 10);
	playRecordSwitch.setBounds(SI_demension.getWidth() / 20,
							   2 * SI_demension.getHeight() / 9,
							   5 * SI_demension.getWidth() / 10,
							   SI_demension.getHeight() / 10);
}
void MainScene::buttonClicked(Button* button)
{
	if (button == &recordDrawableButton)
	{
		if (Record)
		{
			if (coreProcessor.isProcessing())
				stopRecording();
			else
				startRecording();
		}
		else
		{
			if (Stopped)
				startPlay();
			else
				stopPlay();
		}
	}
	else if (button == &playRecordSwitch)
	{
		if (!transportSource.isPlaying())
		{
			if (Record)
				switchToPlayMode();
			else
				switchToRecordMode();
		}
	}
}

void MainScene::sliderValueChanged(Slider * sliderThatWasMoved)
{
	if (sliderThatWasMoved == &zoomSlider)
		playbackThumbnail.setZoomFactor(zoomSlider.getValue());
}

void MainScene::changeListenerCallback(ChangeBroadcaster * source)
{
	showFile(File(lastAudioFileFullPath));
}

void MainScene::startRecording()
{
	const File file(File::getSpecialLocation
		(File::userDocumentsDirectory).getNonexistentChildFile("Recorded\\Just a test", ".wav"));

	coreProcessor.processAudio(file);
	recordDrawableButton.setButtonText("Stop");
	recordingThumbnail.setDisplayFullThumbnail(false);
	playRecordSwitch.setEnabled(false);
}

void MainScene::stopRecording()
{
	coreProcessor.stop();
	recordDrawableButton.setButtonText("Record");
	recordingThumbnail.setDisplayFullThumbnail(true);
	playRecordSwitch.setEnabled(true);
}

void MainScene::startPlay()
{
	transportSource.setPosition(0);
	transportSource.start();
	Stopped = false;
	playRecordSwitch.setEnabled(false);
}

void MainScene::stopPlay()
{
	transportSource.stop();
	Stopped = true;
	playRecordSwitch.setEnabled(true);
}

void MainScene::switchToPlayMode()
{
	Record = false;

	currentThumbnail = &playbackThumbnail;

	deviceManager.removeAudioCallback(&coreProcessor);
	deviceManager.removeAudioCallback(&liveAudioScroller);
	deviceManager.addAudioCallback(&audioSourcePlayer);

	recordingThumbnail.setVisible(false);
	removeChildComponent(&recordingThumbnail);
	addAndMakeVisible(playbackThumbnail);

	showFile(File(lastAudioFileFullPath));

	recordDrawableButton.setButtonText("Play");
}

void MainScene::switchToRecordMode()
{
	Record = true;

	currentThumbnail = &recordingThumbnail;

	deviceManager.removeAudioCallback(&audioSourcePlayer);
	deviceManager.addAudioCallback(&coreProcessor);
	deviceManager.addAudioCallback(&liveAudioScroller);

	playbackThumbnail.setVisible(false);
	removeChildComponent(&playbackThumbnail);
	addAndMakeVisible(recordingThumbnail);

	recordDrawableButton.setButtonText("Record");
}

void MainScene::showFile(const File & file)
{
	loadFileIntoTransport(file);
	playbackThumbnail.setFile(file);
}

void MainScene::loadFileIntoTransport(const File& audioFile)
{
	transportSource.stop();
	transportSource.setSource(nullptr);
	currentAudioFileSource = nullptr;

	AudioFormatReader* reader = playbackThumbnail.getAudioFormatManager().createReaderFor(audioFile);

	if (reader != nullptr)
	{
		currentAudioFileSource = new AudioFormatReaderSource(reader, true);

		transportSource.setSource(currentAudioFileSource,
			32768,
			&timeSliceThread,
			reader->sampleRate);
	}
}

AudioDeviceManager & MainScene::getSharedAudioDeviceManager()
{
	if (sharedAudioDeviceManager == nullptr)
	{
		sharedAudioDeviceManager = new AudioDeviceManager();
		RuntimePermissions::request(RuntimePermissions::recordAudio,
			[](bool wasGranted) {
			int numInputChannels = wasGranted ? 2 : 0;
			sharedAudioDeviceManager->initialise(numInputChannels, 2, 0, true, String(), 0);
		});
	}

	return *sharedAudioDeviceManager;
}
