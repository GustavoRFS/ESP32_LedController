#pragma once
#include "Types/GitHubAssets/Assets.h"

class UpdateService{
  public:
    static bool checkForUpdate();
    static void update();
    static void setup();
    static bool downloadAssets();
  private:
    static Assets* getAllUpdateAssets(bool includeFirmware);
};