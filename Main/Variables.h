#pragma once

#include <Arduino.h>

// #### GLOBAL VARIABLES ####

struct GlobalData{
  bool xStandby;
  bool xNoStandby;
  bool xEditMode;
  bool xOTAActive;
};

extern GlobalData Global;

// #### GLOBAL VARIABLES END ####

// #### WS2812 LED STRIP ####

struct LEDStripData{
  uint8_t ColorIndex;
  uint8_t Mode;
  uint8_t Brightness;
  uint8_t Speed;
  uint8_t MAXCOLORCOUNT; 
  bool xSleep;
};
extern LEDStripData Strip1; 
extern LEDStripData Strip2; 

// #### WS2812 LED STRIP END ####

// #### TM1637 DISPLAY ####

enum class DisplayIndexData{
  OFF,
  STRIP1COLOR,
  STRIP2COLOR,
  STRIP1BRIGHT,
  STRIP2BRIGHT,
  STRIP1MODE,
  STRIP2MODE,
  STRIP1SPEED,
  STRIP2SPEED
};

struct DisplayData{
  DisplayIndexData IndexData; 
  uint8_t Index;
  bool xStandby;
};

extern DisplayData Display; 


// #### TM1637 DISPLAY END ####

// #### IR REMOTE ####

enum class RemoteReceive {
  NONE,
  Key1,
  Key2,
  Key3,
  Key4,
  Key5,
  Key6,
  Key7,
  Key8,
  Key9,
  Key0,
  KeySTAR,
  KeyHASH,
  KeyOK,
  KeyUP,
  KeyDOWN,
  KeyLEFT,
  KeyRIGHT
  };

struct RemoteData{
  bool xPushed;
  bool xAfk;
  RemoteReceive Button;
};

extern RemoteData Remote; 

// #### IR REMOTE END ####

// #### SAVE/LOAD FROM FLASH ####
void LoadVariables();
void SaveVariables();
// #### SAVE/LOAD FROM FLASH END ####