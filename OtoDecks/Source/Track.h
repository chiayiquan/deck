/*
  ==============================================================================

    Track.h
    Created: 8 Mar 2022 2:04:25pm
    Author:  yiquan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Track
{
public:
  Track(String _name, double _duration, String _path);

  static String trackToString(Track track);

  String name;
  double duration;
  String path;
};