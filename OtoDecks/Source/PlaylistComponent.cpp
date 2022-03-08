/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 3 Feb 2022 8:33:50pm
    Author:  yiquan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include <cmath>

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI *_deckGUI1, DeckGUI *_deckGUI2) : deckGUI1(_deckGUI1), deckGUI2(_deckGUI2)
{
  // In your constructor, you should add any child components, and
  // initialise any special settings that your component needs.
  tableComponent.getHeader()
      .addColumn("Track Title", 1, 300);
  tableComponent.getHeader()
      .addColumn("Track Duration", 2, 100);
  tableComponent.getHeader()
      .addColumn("", 3, 200);

  tableComponent.getHeader()
      .addColumn("", 4, 200);

  tableComponent.setModel(this);

  addAndMakeVisible(tableComponent);
  addAndMakeVisible(addToLibButton);
  addAndMakeVisible(searchBar);

  addToLibButton.addListener(this);
  searchBar.addListener(this);

  searchBar.setTextToShowWhenEmpty("Search", Colours::white);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint(juce::Graphics &g)
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
  g.drawText("PlaylistComponent", getLocalBounds(),
             juce::Justification::centred, true); // draw some placeholder text
}

void PlaylistComponent::resized()
{
  // This method is where you should set the bounds of any child
  // components that your component contains..
  int height = getHeight() / 8;
  addToLibButton.setBounds(0, 0, getWidth(), height);
  searchBar.setBounds(0, height, getWidth(), height);
  tableComponent.setBounds(0, height * 2, getWidth(), height * 6);
}

int PlaylistComponent::getNumRows()
{
  return listToDisplay.size();
};

void PlaylistComponent::paintRowBackground(Graphics &g,
                                           int rowNumber,
                                           int width,
                                           int height,
                                           bool rowIsSelected)
{
  if (rowIsSelected)
  {
    g.fillAll(Colours::orange);
  }
  else
  {
    g.fillAll(Colours::darkgrey);
  }
};

void PlaylistComponent::paintCell(Graphics &g,
                                  int rowNumber,
                                  int columnId,
                                  int width,
                                  int height,
                                  bool rowIsSelected)
{
  if (columnId == 1)
  {

    g.drawText(listToDisplay[rowNumber].name,
               2,
               0,
               width - 4,
               height,
               Justification::centredLeft,
               true);
  }
  else if (columnId == 2)
  {
    g.drawText(stringDuration(listToDisplay[rowNumber].duration),
               2,
               0,
               width - 4,
               height,
               Justification::centredLeft,
               true);
  }
};

Component *PlaylistComponent::refreshComponentForCell(int rowNumber,
                                                      int columnId,
                                                      bool isRowSelected,
                                                      Component *existingComponentToUpdate)
{
  if (columnId == 3)
  {
    if (existingComponentToUpdate == nullptr)
    {
      TextButton *btn = new TextButton{"deck 1"};
      String id{std::to_string(rowNumber)};
      btn->setComponentID(id);

      btn->addListener(this);
      existingComponentToUpdate = btn;
    }
  }
  else if (columnId == 4)
  {
    if (existingComponentToUpdate == nullptr)
    {
      TextButton *btn = new TextButton{"deck 2"};
      String id{std::to_string(rowNumber)};
      btn->setComponentID(id);

      btn->addListener(this);
      existingComponentToUpdate = btn;
    }
  }
  return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button *button)
{
  if (button == &addToLibButton)
  {
    FileChooser chooser{"Select a file..."};
    if (chooser.browseForFileToOpen())
    {
      URL chosenFileUrl = URL{chooser.getResult()};
      String name = chosenFileUrl.getFileName();
      double duration = deckGUI1->getDuration(chosenFileUrl);
      String path = "file:///" + chosenFileUrl.getDomain() + "/" + chosenFileUrl.getSubPath();
      originalList.push_back(Track{name, duration, path});
      updateListToDisplay();
    }
  }
  else
  {
    int id = std::stoi(button->getComponentID().toStdString());
  }
};

void PlaylistComponent::updateListToDisplay()
{
  listToDisplay = originalList;
  tableComponent.updateContent();
};

String PlaylistComponent::stringDuration(double duration)
{
  int roundedDuration = std::round(duration);
  int minute = roundedDuration / 60;
  int second = roundedDuration % 60;
  String durationStr = std::to_string(minute) + " min " + std::to_string(second) + " second";
  return durationStr;
};

void PlaylistComponent::textEditorTextChanged(TextEditor &editor)
{
  String value = editor.getTextValue().toString();
  if (value.length() > 0)
  {
    std::vector<Track> filteredResult;
    for (const Track &track : originalList)
    {
      if (track.name.containsIgnoreCase(value))
      {
        filteredResult.push_back(track);
      }
    }
    listToDisplay = filteredResult;
  }
  else
  {
    listToDisplay = originalList;
  }
  tableComponent.updateContent();
};