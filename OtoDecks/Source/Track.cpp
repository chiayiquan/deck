/*
  ==============================================================================

    Track.cpp
    Created: 8 Mar 2022 2:04:25pm
    Author:  yiquan

  ==============================================================================
*/

#include "Track.h"

Track::Track(String _name, double _duration, String _path) : name(_name), duration(_duration), path(_path){};

String Track::trackToString(Track track)
{
  return track.name + "," + std::to_string(track.duration) + "," + track.path;
};