/*
  ==============================================================================

    PlaylistComponent.h
    Created: 3 Feb 2022 8:33:50pm
    Author:  yiquan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DeckGUI.h"
#include "Track.h"

using namespace juce;

//==============================================================================
/*
 */
class PlaylistComponent : public juce::Component,
                          public juce::TableListBoxModel,
                          public Button::Listener
{
public:
  PlaylistComponent(DeckGUI *_deckGUI1, DeckGUI *_deckGUI2);
  ~PlaylistComponent() override;

  void paint(juce::Graphics &) override;
  void resized() override;

  int getNumRows() override;
  void paintRowBackground(Graphics &,
                          int rowNumber,
                          int width,
                          int height,
                          bool rowIsSelected) override;

  void paintCell(Graphics &,
                 int rowNumber,
                 int columnId,
                 int width,
                 int height,
                 bool rowIsSelected) override;

  Component *refreshComponentForCell(int rowNumber,
                                     int columnId,
                                     bool isRowSelected,
                                     Component *existingComponentToUpdate) override;

  void buttonClicked(Button *button) override;

  void updateListToDisplay();

  String stringDuration(double duration);

private:
  TableListBox tableComponent;
  std::vector<Track> originalList;
  std::vector<Track> listToDisplay;
  std::vector<std::string> trackTitles;

  TextButton addToLibButton{"Add To Library"};

  DeckGUI *deckGUI1;
  DeckGUI *deckGUI2;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
