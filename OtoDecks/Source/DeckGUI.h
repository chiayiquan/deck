/*
  ==============================================================================

    DeckGUI.h
    Created: 3 Feb 2022 12:15:11pm
    Author:  yiquan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

using namespace juce;
//==============================================================================
/*
 */
class DeckGUI : public juce::Component,
                public Button::Listener,
                public Slider::Listener,
                public FileDragAndDropTarget,
                public Timer
{
public:
  DeckGUI(DJAudioPlayer *player,
          AudioFormatManager &formatManagerToUse,
          AudioThumbnailCache &cacheToUse);
  ~DeckGUI() override;

  void paint(juce::Graphics &) override;
  void resized() override;

  /** implement Button::Listener */
  void buttonClicked(Button *button) override;
  /** implement Slider  ::Listener */
  void sliderValueChanged(Slider *slider) override;

  bool isInterestedInFileDrag(const StringArray &files) override;
  void filesDropped(const StringArray &files, int x, int y) override;

  void timerCallback() override;

  double getDuration(URL audioURL);

private:
  TextButton playButton{"PLAY"};
  TextButton stopButton{"STOP"};
  TextButton loadButton{"LOAD"};

  Slider volSlider;
  Slider speedSlider;
  Slider posSlider;

  DJAudioPlayer *player;

  WaveformDisplay waveformDisplay;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
