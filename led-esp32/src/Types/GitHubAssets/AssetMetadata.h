#pragma once
#include <Arduino.h>

class AssetMetadata
{
public:
  String url;
  String name;
  AssetMetadata() {}
  AssetMetadata(String url, String name)
  {
    this->url = url;
    this->name = name;
  }
};