/*
  ==============================================================================

    FileHelper.h
    Created: 8 Mar 2022 3:11:20pm
    Author:  yiquan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Track.h"

class FileHelper
{
public:
  FileHelper();

  static void writeToCSV(String filePath, Track track);

  static std::vector<Track> readFromCSV(String filePath);

  static std::vector<std::string> tokenise(std::string csvLine, char separator);

  static Track stringsToTrack(std::vector<std::string> tokens);
};