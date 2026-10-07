#include "Variables.h"
#include <TM1637.h>
#include <PLCBlocks.h>
using namespace PLCBlocks;

String DisplayText;
String DisplayActual;

P_TRIG DisplayOFFEdge;
P_TRIG DisplayONEdge;

TM1637 tm(PIN_TM1637_CLK, PIN_TM1637_DIO);

void DisplaySetup() {
  tm.begin();
  tm.setBrightnessPercent(90);
  tm.clearScreen();
  tm.display("8888");
}

void DisplayLoop() {

  // #### DISPLAY STANDBY MODE ####
  DisplayOFFEdge.process(Display.xStandby);
  DisplayONEdge.process(!Display.xStandby);

  if (DisplayOFFEdge.Q) {
    tm.clearScreen();
    tm.offMode();
    DisplayText = "OFF";
    return;
  }
  if (DisplayONEdge.Q) {
    tm.onMode();
    DisplayDisplay();
  }
  // #### DISPLAY STANDBY MODE END ####


  // #### DISPLAY MAIN MENU ####
  if (!Global.xEditMode && !Display.xStandby) {
    switch (Display.Index) {

      case 0:
        Display.IndexData = DisplayIndexData::STRIP1COLOR;
        DisplayText = "1COL";
        DisplayDisplay();
        break;

      case 1:
        Display.IndexData = DisplayIndexData::STRIP2COLOR;
        DisplayText = "2COL";
        DisplayDisplay();
        break;

      case 2:
        Display.IndexData = DisplayIndexData::STRIP1BRIGHT;
        DisplayText = "1bri";
        DisplayDisplay();
        break;

      case 3:
        Display.IndexData = DisplayIndexData::STRIP2BRIGHT;
        DisplayText = "2bri";
        DisplayDisplay();
        break;

      case 4:
        Display.IndexData = DisplayIndexData::STRIP1MODE;
        DisplayText = "1Ani";
        DisplayDisplay();
        break;

      case 5:
        Display.IndexData = DisplayIndexData::STRIP2MODE;
        DisplayText = "2Ani";
        DisplayDisplay();
        break;

      case 6:
        Display.IndexData = DisplayIndexData::STRIP1SPEED;
        DisplayText = "1SPE";
        DisplayDisplay();
        break;

      case 7:
        Display.IndexData = DisplayIndexData::STRIP2SPEED;
        DisplayText = "2SPE";
        DisplayDisplay();
        break;
    }
  }
  // #### DISPLAY MAIN MENU END ####

  // #### DISPLAY EDIT MODE ####
  else if (Global.xEditMode) {
    switch (Display.IndexData) {

      case DisplayIndexData::STRIP1COLOR:
        DisplayText = Strip1.ColorIndex;
        DisplayDisplay();
        break;

      case DisplayIndexData::STRIP2COLOR:
        DisplayText = Strip2.ColorIndex;
        DisplayDisplay();
        break;

      case DisplayIndexData::STRIP1BRIGHT:
        DisplayText = Strip1.Brightness;
        DisplayDisplay();
        break;

      case DisplayIndexData::STRIP2BRIGHT:
        DisplayText = Strip2.Brightness;
        DisplayDisplay();
        break;

      case DisplayIndexData::STRIP1MODE:
        DisplayText = Strip1.Mode;
        DisplayDisplay();
        break;

      case DisplayIndexData::STRIP2MODE:
        DisplayText = Strip2.Mode;
        DisplayDisplay();
        break;

      case DisplayIndexData::STRIP1SPEED:
        DisplayText = Strip1.Speed;
        DisplayDisplay();
        break;

      case DisplayIndexData::STRIP2SPEED:
        DisplayText = Strip2.Speed;
        DisplayDisplay();
        break;
    }
  }
  // #### DISPLAY EDIT MODE END ####
}

// #### SET TEXT TO DISPLAY OUTPUT ####
void DisplayDisplay() {
  if (DisplayText != DisplayActual) {
    tm.clearScreen();
    tm.display(DisplayText);
    DisplayActual = DisplayText;
  }
}
// #### SET TEXT TO DISPLAY OUTPUT END ####