/*
==============================================================================

TimeComponent.h
Created: 7 May 2016 5:27:51pm
Author:  Anthony

==============================================================================
*/

#ifndef TIMECOMPONENT_H_INCLUDED
#define TIMECOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class RecordingThumbnail : public Component,
	private ChangeListener
{
public:
	RecordingThumbnail();
	~RecordingThumbnail();
	AudioThumbnail& getAudioThumbnail();
	void setDisplayFullThumbnail(bool displayFull);


	void paint(Graphics &g) override;
	void resized() override;

private:
	AudioFormatManager formatManager;
	AudioThumbnailCache thumbnailCache;
	AudioThumbnail thumbnail;

	bool displayFullThumb;

	void changeListenerCallback(ChangeBroadcaster* source) override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RecordingThumbnail)
};



#endif  // TIMECOMPONENT_H_INCLUDED
