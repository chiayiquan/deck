/*
  ==============================================================================

    Track.h
    Created: 8 Mar 2022 2:04:25pm
    Author:  yiquan

  ==============================================================================
*/

#include <JuceHeader.h>
#pragma once

class Track
{
public:
  Track(String _name, double _duration, String _path);

  String name;
  double duration;
  String path;
};