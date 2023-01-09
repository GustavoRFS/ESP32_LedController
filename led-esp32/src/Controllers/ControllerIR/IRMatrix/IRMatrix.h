#include <Arduino.h>
#include "Controllers/ControllerIR/RemoteControlCommand/RemoteControlCommand.h"

RemoteControlCommand IRMatrix[]={
  // Row 1
  RemoteControlCommand(new uint32_t[2]{0x8503705D,0xF700FF},2,true), // Increase Brightness
  RemoteControlCommand(new uint32_t[2]{0xDEB0C861,0xF7807F},2,false), // Decrease Brightness
  RemoteControlCommand(false,new uint32_t[2]{0xD4DD0381,0xF740BF},2), // Turn off
  RemoteControlCommand(true,new uint32_t[2]{0xCE1972FD,0xF7C03F},2), // Turn on
  // Row 2
  RemoteControlCommand(Color(255,0,0),new uint32_t[2]{0xE85952E1,0xF720DF},2),
  RemoteControlCommand(Color(0,255,0),new uint32_t[3]{0x78CDA4DC,0x78CDA4DD,0xF7A05F},3),
  RemoteControlCommand(Color(0,0,255),new uint32_t[2]{0xA2672345,0xF7609F},2),
  RemoteControlCommand(Color(255,255,255),new uint32_t[2]{0x9BA392C1,0xF7E01F},2),
  // Row 3
  RemoteControlCommand(Color(255,25,0),new uint32_t[2]{0xD3FD9A81,0xF710EF},2),
  RemoteControlCommand(Color(0,255,75),new uint32_t[2]{0x6471EC7D,0xF7906F},2),
  RemoteControlCommand(Color(35,0,255),new uint32_t[2]{0x9D52009D,0xF750AF},2),
  RemoteControlCommand(new Effect(),new uint32_t[2]{0xDCC45BE1,0xF7D02F},2), // Flash
  // Row 4
  RemoteControlCommand(Color(255,60,0),new uint32_t[2]{0x84044BBD,0xF730CF},2),
  RemoteControlCommand(Color(0,255,255),new uint32_t[2]{0x14789DB9,0xF7B04F},2),
  RemoteControlCommand(Color(90,0,255),new uint32_t[2]{0x3E121C21,0xF7708F},2),
  RemoteControlCommand(new Effect(),new uint32_t[2]{0x374E8B9D,0xF7F00F},2), // Strobe
  // Row 5
  RemoteControlCommand(Color(255,100,0),new uint32_t[2]{0xB0F9B3E1,0xF708F7},2),
  RemoteControlCommand(Color(0,140,255),new uint32_t[2]{0x416E05DD,0xF78877},2),
  RemoteControlCommand(Color(120,0,200),new uint32_t[2]{0x6A844445,0xF748B7},2),
  RemoteControlCommand(new Effect(),new uint32_t[2]{0xB9C07541,0xF7C837},2), // Fade
  // Row 6
  RemoteControlCommand(Color(255,200,0),new uint32_t[2]{0x9DE75E1D,0xF728D7},2),
  RemoteControlCommand(Color(0,50,255),new uint32_t[2]{0xF794B621,0xF7A857},2),
  RemoteControlCommand(Color(255,0,100),new uint32_t[2]{0x57F52E81,0xF76897},2),
  RemoteControlCommand(new Effect(),new uint32_t[2]{0xA7315F7D,0xF7E817},2), // Smooth
};