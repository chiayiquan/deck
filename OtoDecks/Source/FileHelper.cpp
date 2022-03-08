/*
  ==============================================================================

    FileHelper.cpp
    Created: 8 Mar 2022 3:11:20pm
    Author:  yiquan

  ==============================================================================
*/

#include "FileHelper.h"

FileHelper::FileHelper(){};

void FileHelper::writeToCSV(String filePath, Track track)
{
  File file{filePath};
  if (!file.existsAsFile())
  {
    file.create();
  }
  file.appendText(Track::trackToString(track) + "\n");
};

std::vector<Track> FileHelper::readFromCSV(String filePath)
{
  File file{filePath};

  StringArray fileData;

  std::vector<Track> tracks;

  file.readLines(fileData);

  for (const String &data : fileData)
  {
    try
    {
      Track track = stringsToTrack(tokenise(data.toStdString(), ','));
      tracks.push_back(track);
    }
    catch (const std::exception &e)
    {
      std::cout << "CSVReader::readCSV bad data" << std::endl;
    }
  }
  return tracks;
};

Track FileHelper::stringsToTrack(std::vector<std::string> tokens)
{
  double duration;

  if (tokens.size() != 3)
  {
    std::cout << "Bad line " << std::endl;
    throw std::exception{};
  }

  try
  {
    duration = std::stod(tokens[1]);
  }
  catch (const std::exception &e)
  {
    std::cout << "FileHelper::stringsToTrack Bad float! " << tokens[1]
              << std::endl;
    throw;
  }

  return Track{tokens[0], duration, tokens[2]};
}

// cw 1 code
std::vector<std::string> FileHelper::tokenise(std::string csvLine, char separator)
{
  std::vector<std::string> tokens;
  signed int start, end;
  std::string token;
  start = csvLine.find_first_not_of(separator, 0);
  do
  {
    end = csvLine.find_first_of(separator, start);
    if (start == csvLine.length() || start == end)
      break;
    if (end >= 0)
      token = csvLine.substr(start, end - start);
    else
      token = csvLine.substr(start, csvLine.length() - start);
    tokens.push_back(token);
    start = end + 1;
  } while (end > 0);

  return tokens;
}