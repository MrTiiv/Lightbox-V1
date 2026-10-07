#include "Variables.h"
#include <WS2812FX.h>
#include <PLCBlocks.h>
using namespace PLCBlocks;



WS2812FX LEDSTRIP1 = WS2812FX(LED_COUNT_1, PIN_LED_STRIP_1, NEO_GRB + NEO_KHZ800);
WS2812FX LEDSTRIP2 = WS2812FX(LED_COUNT_2, PIN_LED_STRIP_2, NEO_GRB + NEO_KHZ800);

const uint32_t Colors[] = {
  BLACK,
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  CYAN,
  BLUE,
  PURPLE,
  MAGENTA,
  PINK,
  WHITE
};

void LEDStripSetup() {

  LEDSTRIP1.init();
  LEDSTRIP1.start();

  LEDSTRIP2.init();
  LEDSTRIP2.start();
}

static uint8_t Strip1lastMode = 255;
static uint8_t Strip1lastBrightness = 255;
static uint8_t Strip1lastColorIndex = 255;
static uint8_t Strip1lastSpeed = 255;

static uint8_t Strip2lastMode = 255;
static uint8_t Strip2lastBrightness = 255;
static uint8_t Strip2lastColorIndex = 255;
static uint8_t Strip2lastSpeed = 255;

P_TRIG Strip1Sleep;
P_TRIG Strip2Sleep;
P_TRIG Strip1Wakeup;
P_TRIG Strip2Wakeup;

bool Strip1Sleeping = false;
bool Strip2Sleeping = false;

void LEDStripLoop() {
  // #### LED STRIP WAKEUP ####
  Strip1Wakeup.process(!Strip1.xSleep && Strip1.ColorIndex != 0);
  Strip2Wakeup.process(!Strip2.xSleep && Strip2.ColorIndex != 0);

  if(Strip1Wakeup.Q){
    LEDSTRIP1.start();
    Strip1Sleeping = false;
  }
  if(Strip2Wakeup.Q){
    LEDSTRIP2.start();
    Strip2Sleeping = false;
  }
  // #### LED STRIP WAKEUP END ####

  // #### LED STRIP SLEEPING ####
  if(Strip1Sleeping && Strip2Sleeping){
    return;
  }
  // #### LED STRIP SLEEPING END ####

  // #### LED STRIP LOOP SERVICE ####
  if(!Strip1Sleeping){
    LEDSTRIP1.service();
  }

  if(!Strip2Sleeping){
    LEDSTRIP2.service();
  }
  // #### LED STRIP LOOP SERVICE END ####

  // #### LED STRIP GO SLEEP ####
  Strip1Sleep.process(Strip1.xSleep || Strip1.ColorIndex == 0);
  Strip2Sleep.process(Strip2.xSleep || Strip2.ColorIndex == 0);

  if(Strip1Sleep.Q){
    Strip1GoSleep();
    Strip1Sleeping = true;
  }
  if(Strip2Sleep.Q){
    Strip2GoSleep();
    Strip2Sleeping = true;
  }
  // #### LED STRIP GO SLEEP END ####

  // #### LED STRIP CHANGE MODES ####
  if(!Strip1.xSleep && !Global.xOTAActive){
    if(Strip1.Brightness != Strip1lastBrightness){
      LEDSTRIP1.setBrightness(Strip1.Brightness);
      Strip1lastBrightness = Strip1.Brightness;
    }
    if(Strip1.Mode != Strip1lastMode){
      LEDSTRIP1.setMode(Strip1.Mode);
      Strip1lastMode = Strip1.Mode;
    }
    if(Strip1.ColorIndex != Strip1lastColorIndex){
      LEDSTRIP1.setColor(Colors[Strip1.ColorIndex]);
      Strip1lastColorIndex = Strip1.ColorIndex;
    }
    if(Strip1.Speed != Strip1lastSpeed){
      uint16_t realSpeed = map(Strip1.Speed, 1, 20, 3000, 100);
      LEDSTRIP1.setSpeed(realSpeed);
      Strip1lastSpeed = Strip1.Speed;
    }
  }

  if(!Strip2.xSleep && !Global.xOTAActive){
    if(Strip2.Brightness != Strip2lastBrightness){
      LEDSTRIP2.setBrightness(Strip2.Brightness);
      Strip2lastBrightness = Strip2.Brightness;
    }
    if(Strip2.Mode != Strip2lastMode){
      LEDSTRIP2.setMode(Strip2.Mode);
      Strip2lastMode = Strip2.Mode;
    }
    if(Strip2.ColorIndex != Strip2lastColorIndex){
      LEDSTRIP2.setColor(Colors[Strip2.ColorIndex]);
      Strip2lastColorIndex = Strip2.ColorIndex;
    }
    if(Strip2.Speed != Strip2lastSpeed){
      uint16_t realSpeed = map(Strip2.Speed, 1, 20, 3000, 100);
      LEDSTRIP2.setSpeed(realSpeed);
      Strip2lastSpeed = Strip2.Speed;
    }
  }
  // #### LED STRIP CHANGE MODES END ####
}


// #### LED STRIP HELPER VOIDS ####
void Strip1GoSleep(){
    LEDSTRIP1.setBrightness(0);
    LEDSTRIP1.setMode(0);
    LEDSTRIP1.setColor(Colors[0]);
    LEDSTRIP1.setSpeed(0);
    LEDSTRIP1.service();
    LEDSTRIP1.stop();
    Strip1lastMode = 255;
    Strip1lastBrightness = 255;
    Strip1lastColorIndex = 255;
    Strip1lastSpeed = 255;
}
void Strip2GoSleep(){
    LEDSTRIP2.setBrightness(0);
    LEDSTRIP2.setMode(0);
    LEDSTRIP2.setColor(Colors[0]);
    LEDSTRIP2.setSpeed(0);
    LEDSTRIP2.service();
    LEDSTRIP2.stop();
    Strip2lastMode = 255;
    Strip2lastBrightness = 255;
    Strip2lastColorIndex = 255;
    Strip2lastSpeed = 255;
}

void StripsOTA(){
  LEDSTRIP1.setColor(BLACK);
  
  LEDSTRIP2.setBrightness(200);
  LEDSTRIP2.setMode(13);
  LEDSTRIP2.setColor(RED);
  LEDSTRIP2.setSpeed(3000);
  Strip1lastMode = 255;
  Strip1lastBrightness = 255;
  Strip1lastColorIndex = 255;
  Strip1lastSpeed = 255;
  Strip2lastMode = 255;
  Strip2lastBrightness = 255;
  Strip2lastColorIndex = 255;
  Strip2lastSpeed = 255;
}
