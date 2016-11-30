/*
==============================================================================

RecordingThumbnail.cpp
Created: 7 May 2016 5:28:11pm
Author:  Anthony

==============================================================================
*/

#include "RecordingThumbnail.h"

RecordingThumbnail::RecordingThumbnail()
										: thumbnailCache(10),
										thumbnail(512, formatManager, thumbnailCache),
										displayFullThumb(false)
{
	formatManager.registerBasicFormats();
	thumbnail.addChangeListener(this);
}

RecordingThumbnail::~RecordingThumbnail()
{
	thumbnail.removeChangeListener(this);
}

AudioThumbnail& RecordingThumbnail::getAudioThumbnail()
{
	return thumbnail;
}

void RecordingThumbnail::setDisplayFullThumbnail(bool displayFull)
{
	displayFullThumb = displayFull;
	repaint();
}

void RecordingThumbnail::paint(Graphics &g)
{
	g.fillAll(Colours::darkgrey);
	g.setColour(Colours::lightgrey);

	if (thumbnail.getTotalLength() > 0.0)
	{
		const double endTime = displayFullThumb ? thumbnail.getTotalLength()
			: jmax(30.0, thumbnail.getTotalLength());

		Rectangle<int> thumbArea(getLocalBounds());
		thumbnail.drawChannels(g, thumbArea.reduced(2), 0.0, endTime, 1.0f);
	}
	else
	{
		g.setFont(14.0f);
		g.drawFittedText("(No file recorded)", getLocalBounds(), Justification::centred, 2);
	}
}

void RecordingThumbnail::resized()
{

}

void RecordingThumbnail::changeListenerCallback(ChangeBroadcaster * source)
{
	if (source == &thumbnail)
	{
		repaint();
	}
}
