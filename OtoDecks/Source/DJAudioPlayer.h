/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 3 Feb 2022 10:57:16am
    Author:  yiquan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace juce;

class DJAudioPlayer : public AudioSource
{
public:
  DJAudioPlayer(AudioFormatManager &_formatManager);
  ~DJAudioPlayer();

  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
  void
  getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
  void releaseResources() override;

  void loadURL(URL audioURL);
  void setGain(double gain);
  void setSpeed(double ratio);
  void setPosition(double posInSecs);
  void setPositionRelative(double pos);

  void start();
  void stop();

  /** et the relative position of the playhead */
  double getPositionRelative();

private:
  AudioFormatManager &formatManager;
  std::unique_ptr<AudioFormatReaderSource> readerSource;
  AudioTransportSource transportSource;
  ResamplingAudioSource resampleSource{&transportSource, false, 2};
};
