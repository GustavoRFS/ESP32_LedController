#include "RemoteControlCommand.h"
#include "LedController/LedController.h"

void RemoteControlCommand::performCommand()
{
  if (color)
  {
    return LedController::setColor(*color);
  }

  if (effect)
  {
    return LedController::setEffect(effect);
  }

  if (switchPower)
  {
    *switchPower ? LedController::turnOff() : LedController::turnOn();
  }

  if (changeBrightness)
  {
    *changeBrightness > 0 ? LedController::increaseBrightness() : LedController::decreaseBrightness();
  }
}

RemoteControlCommand::RemoteControlCommand(Color color, uint32_t *remoteControlCodes, uint8_t remoteControlCodesAmount)
{
  this->color = new Color(color);
  this->remoteControlCodesAmount = remoteControlCodesAmount;
  this->remoteControlCodes = remoteControlCodes;
}

RemoteControlCommand::RemoteControlCommand(Effect *effect, uint32_t *remoteControlCodes, uint8_t remoteControlCodesAmount)
{
  this->effect = effect;
  this->remoteControlCodesAmount = remoteControlCodesAmount;
  this->remoteControlCodes = remoteControlCodes;
}

RemoteControlCommand::RemoteControlCommand(bool switchPower, uint32_t *remoteControlCodes, uint8_t remoteControlCodesAmount)
{
  this->switchPower = new uint8_t(switchPower);
  this->remoteControlCodesAmount = remoteControlCodesAmount;
  this->remoteControlCodes = remoteControlCodes;
}

RemoteControlCommand::RemoteControlCommand(uint32_t *remoteControlCodes, uint8_t remoteControlCodesAmount, bool changeBrightness)
{
  this->changeBrightness = new uint8_t(changeBrightness);
  this->remoteControlCodesAmount = remoteControlCodesAmount;
  this->remoteControlCodes = remoteControlCodes;
}

RemoteControlCommand::~RemoteControlCommand()
{
  if (color)
    delete color;
  if (effect)
    delete effect;
  if (switchPower)
    delete switchPower;
  if (changeBrightness)
    delete changeBrightness;

  if (remoteControlCodes)
    delete[] remoteControlCodes;
}