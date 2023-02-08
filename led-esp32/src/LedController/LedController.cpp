#include "FastLED.h"

#include "LedController.h"
#include "Utils/Utils.h"

CRGBArray<NUM_LEDS> leds;

void LedController::setup()
{
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void LedController::setColor(Color color)
{
  for (uint16_t i = 0; i < NUM_LEDS; i++)
    leds[i].setRGB(color.r, color.g, color.b);
  FastLED.show();
}

void LedController::setGradient(Gradient *gradient)
{
  xTaskCreate([](void *params)
              {
                Gradient *gradient = (Gradient *)params;

                for (uint8_t i = 0; i < gradient->size; i++)
                {
                  if (i == 0)
                    i++;

                  GradientUnit previousColor = gradient->units[i - 1];
                  GradientUnit nextColor = gradient->units[i];

                  uint8_t firstIndex = map(previousColor.percentage, 0, 100, 0, NUM_LEDS);
                  uint8_t lastIndex = map(nextColor.percentage, 0, 100, 0, NUM_LEDS);

                  if (i == 1)
                  {
                    for (uint8_t i = 0; i < firstIndex; i++)
                    {
                      leds[i].setRGB(
                          previousColor.color.r,
                          previousColor.color.g,
                          previousColor.color.b);
                    }
                  }

                  if (i == gradient->size - 1)
                  {
                    for (uint8_t i = firstIndex; i < NUM_LEDS; i++)
                    {
                      leds[i].setRGB(
                          nextColor.color.r,
                          nextColor.color.g,
                          nextColor.color.b);
                    }
                  }

                  for (uint8_t i = firstIndex; i < lastIndex; i++)
                  {
                    float intensity = map(i, firstIndex, lastIndex, 0, 100) / 100.0;
                    leds[i].setRGB(
                        previousColor.color.r * (1 - intensity) + nextColor.color.r * intensity,
                        previousColor.color.g * (1 - intensity) + nextColor.color.g * intensity,
                        previousColor.color.b * (1 - intensity) + nextColor.color.b * intensity);
                  }
                }

                FastLED.show(); 

                delete gradient;
                vTaskDelete(NULL); },
              "setGradient", 10000, gradient, 1, NULL);
}

void LedController::setEffect(Effect *effect)
{
}