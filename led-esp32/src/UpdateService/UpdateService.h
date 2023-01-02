#include "Types/GitHubAssets/Assets.h"

class UpdateService{
  public:
    static bool checkForUpdate();
    static void update();
    static void setup();
  private:
    static void downloadUpdateAssets();
    static Assets getAllUpdateAssets();
};