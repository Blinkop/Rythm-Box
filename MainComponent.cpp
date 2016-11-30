/*
==============================================================================

This file was auto-generated!

==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainContentComponent::MainContentComponent()
{
	windowHeight = 450;
	windowWidth = 245;

	/*Rectangle<int> screen_demension = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
	setSize (screen_demension.getWidth(), screen_demension.getHeight());*//*FULL DEMENSION*/

	setSize(windowWidth, windowHeight);
	mainScene.setSize(windowWidth, windowHeight);
	addAndMakeVisible(mainScene);
}

MainContentComponent::~MainContentComponent()
{
	
}

void MainContentComponent::paint(Graphics& g)
{

}

void MainContentComponent::resized()
{
	// This is called when the MainContentComponent is resized.
	// If you add any child components, this is where you should
	// update their positions.
	windowHeight = getBounds().getHeight();
	windowWidth = getBounds().getWidth();
	mainScene.setSize(windowWidth, windowHeight);
}
