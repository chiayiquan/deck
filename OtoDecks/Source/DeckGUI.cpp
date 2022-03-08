/*
  ==============================================================================

    DeckGUI.cpp
    Created: 3 Feb 2022 12:15:11pm
    Author:  yiquan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer *_player,
                 AudioFormatManager &formatManagerToUse,
                 AudioThumbnailCache &cacheToUse)
    : player(_player),
      waveformDisplay(formatManagerToUse, cacheToUse)
{
  // In your constructor, you should add any child components, and
  // initialise any special settings that your component needs.
  addAndMakeVisible(playButton);
  addAndMakeVisible(stopButton);
  addAndMakeVisible(loadButton);

  addAndMakeVisible(volSlider);
  addAndMakeVisible(speedSlider);
  addAndMakeVisible(posSlider);

  addAndMakeVisible(waveformDisplay);

  playButton.addListener(this);
  stopButton.addListener(this);
  loadButton.addListener(this);
  volSlider.addListener(this);
  speedSlider.addListener(this);
  posSlider.addListener(this);

  volSlider.setRange(0.0, 1.0);
  posSlider.setRange(0.0, 1.0);

  startTimer(500);
}

DeckGUI::~DeckGUI()
{
  stopTimer();
}

void DeckGUI::paint(juce::Graphics &g)
{
  /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId)); // clear the background

  g.setColour(juce::Colours::grey);
  g.drawRect(getLocalBounds(), 1); // draw an outline around the component

  g.setColour(juce::Colours::white);
  g.setFont(14.0f);
  g.drawText("DeckGUI", getLocalBounds(),
             juce::Justification::centred, true); // draw some placeholder text
}

void DeckGUI::resized()
{
  double rowH = getHeight() / 8;
  playButton.setBounds(0, 0, getWidth(), rowH);
  stopButton.setBounds(0, rowH, getWidth(), rowH);
  volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
  speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
  posSlider.setBounds(0, rowH * 4, getWidth(), rowH);
  waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
  loadButton.setBounds(0, rowH * 7, getWidth(), rowH);
}

void DeckGUI::buttonClicked(Button *button)
{
  if (button == &playButton)
  {
    player->start();
  }
  if (button == &stopButton)
  {
    player->stop();
  }
  if (button == &loadButton)
  {
    chooser =
        std::make_unique<juce::FileChooser>("Select a file...", juce::File{});
    auto chooserFlags = juce::FileBrowserComponent::openMode |
                        juce::FileBrowserComponent::canSelectFiles;

    chooser->launchAsync(chooserFlags, [this](const FileChooser &fc)
                         {
                           if (fc.getResults().size() > 0)
                           {
                             auto file = fc.getURLResult();
                             player->loadURL(file);
                             return waveformDisplay.loadURL(file);
                             // if (file != File{}) {
                             //   return loadFile(file);
                             // }
                           }
                         });
  }
};

void DeckGUI::sliderValueChanged(Slider *slider)
{
  if (slider == &volSlider)
  {
    player->setGain(slider->getValue());
  }
  if (slider == &speedSlider)
  {
    player->setSpeed(slider->getValue());
  }
  if (slider == &posSlider)
  {
    player->setPositionRelative(slider->getValue());
  }
};

bool DeckGUI::isInterestedInFileDrag(const StringArray &files)
{
  return true;
};
void DeckGUI::filesDropped(const StringArray &files, int x, int y)
{
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
    waveformDisplay.loadURL(URL{File{files[0]}});
  }
};

void DeckGUI::timerCallback()
{
  waveformDisplay.setPositionRelative(player->getPositionRelative());
};