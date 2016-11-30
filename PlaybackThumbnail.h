/*
  ==============================================================================

    PlaybackThumbnail.h
    Created: 22 Oct 2016 1:24:57am
    Author:  Anthony

  ==============================================================================
*/

#ifndef PLAYBACKTHUMBNAIL_H_INCLUDED
#define PLAYBACKTHUMBNAIL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class PlaybackThumbnail : public Component,
						  public ChangeListener,
						  public ChangeBroadcaster,
						  private ScrollBar::Listener,
						  private Timer
{
public:
	PlaybackThumbnail(AudioTransportSource& _transportSource,
					  Slider& slider);
	~PlaybackThumbnail();

	void setFile(const File& file);
	File getCurrentFile() const noexcept;
	AudioFormatManager& getAudioFormatManager();

	void setZoomFactor(double amount);
	void setRange(Range<double> range);
	void setFollowsTransport(bool shouldFollow);

	void paint(Graphics& g) override;
	void resized() override;

	void changeListenerCallback(ChangeBroadcaster*) override;

	void mouseDown(const MouseEvent& e) override;
	void mouseDrag(const MouseEvent& e) override;
	void mouseUp(const MouseEvent&) override;
	void mouseWheelMove(const MouseEvent&, const MouseWheelDetails& wheel) override;
private:
	AudioTransportSource& transportSource;
	Slider& zoomSlider;
	ScrollBar scrollbar;

	AudioFormatManager formatManager;

	AudioThumbnailCache thumbnailCache;
	AudioThumbnail thumbnail;
	Range<double> visibleRange;
	bool isFollowingTransport;

	File currentFile;

	DrawableRectangle currentPositionMarker;

	float timeToX(const double time) const;
	double xToTime(const float x) const;

	bool canMoveTransport() const noexcept;

	void scrollBarMoved(ScrollBar* scrollbarThatHasMoved, double newRangeStart) override;

	void timerCallback() override;

	void updateCursorPosition();

};



#endif  // PLAYBACKTHUMBNAIL_H_INCLUDED
