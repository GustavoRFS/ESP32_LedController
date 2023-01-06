#include "Utils.h"

void Utils::delay(uint64_t milliseconds){
  vTaskDelay(milliseconds/portTICK_PERIOD_MS);
}