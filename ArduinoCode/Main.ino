#include <Arduino.h>
#include "Config.h"
#include "LightboxUI.h"
#include "Variables.h"
#include <PLCBlocks.h>
using namespace PLCBlocks;

P_TRIG SAVEDATAAUTO;
P_TRIG LEDSTRIPOTA;

void setup() {
  LoadVariables();
  remoteSetup();
  DisplaySetup();
  LEDStripSetup();
  LightboxUISetup();
  BuzzerStratupMelody();
}

void loop() {
  remoteLoop();
  DisplayLoop();
  LEDStripLoop();
  BuzzerLoop();
  LightboxUILoop();


  // #### OTA ####
  LEDSTRIPOTA.process(Global.xOTAActive);
  if(Remote.Button == RemoteReceive::KeyHASH && !Global.xOTAActive){
    xStartOTAHotspot = true;
    BuzzerOTAMelody();
  }
  if(LEDSTRIPOTA.Q){
    StripsOTA();
  }
  if(Global.xOTAActive){
    Display.xStandby = true;
    return; 
  }
  // #### OTA END ####

  // #### STANDBY MODE ####
  Global.xNoStandby = !Global.xStandby;
  if (Remote.Button == RemoteReceive::KeySTAR && Global.xStandby) {
    Global.xStandby = false;
    BuzzerStandbyMelody();
  } else if (Remote.Button == RemoteReceive::KeySTAR && !Global.xStandby) {
    Global.xStandby = true;
    BuzzerStandbyMelody();
  }

  if (Global.xStandby) {
    Display.xStandby = true;
    Strip1.xSleep = true;
    Strip2.xSleep = true;
    Global.xEditMode = false; 
    return;
  } else {
    Display.xStandby = false;
    Strip1.xSleep = false;
    Strip2.xSleep = false;
  }
  // #### STANDBY MODE END ####

  // #### REMOTE AFK MODE ####
  if (Remote.xAfk) {
    Display.xStandby = true;
    Global.xEditMode = false;
  } else {
    Display.xStandby = false;
  }
  // #### REMOTE AFK MODE END ####

  // #### SAVE DATA ON REMOTE AFK OR ON MANUAL TRIGGER ####
  SAVEDATAAUTO.process(Remote.xAfk);

  if(SAVEDATAAUTO.Q){
    SaveVariables();
  }
  // #### SAVE DATA ON REMOTE AFK OR ON MANUAL TRIGGER END ####

  // #### MAIN MENU ####
  if (!Global.xEditMode) {
    // #### UP AND DOWN IN MAIN MENU ####
    if ((Remote.Button == RemoteReceive::KeyUP || Remote.Button == RemoteReceive::KeyRIGHT) && Display.Index != 7) {
      Display.Index++; 
      BuzzerConfirmBeep();
    } else if ((Remote.Button == RemoteReceive::KeyDOWN || Remote.Button == RemoteReceive::KeyLEFT) && Display.Index != 0) {
      Display.Index--; 
      BuzzerConfirmBeep();
    }
    // #### UP AND DOWN IN MAIN MENU END ####

    // #### DIRECT CHOOSE IN MAIN MENU ####
    switch (Remote.Button) {
      case RemoteReceive::Key1:
        Display.Index = 0;
        BuzzerConfirmBeep();
        break;
      case RemoteReceive::Key2:
        Display.Index = 1;
        BuzzerConfirmBeep();
        break;
      case RemoteReceive::Key3:
        Display.Index = 2; 
        BuzzerConfirmBeep(); 
        break;
      case RemoteReceive::Key4:
        Display.Index = 3; 
        BuzzerConfirmBeep();
        break;
      case RemoteReceive::Key5:
        Display.Index = 4; 
        BuzzerConfirmBeep(); 
        break;
      case RemoteReceive::Key6:
        Display.Index = 5; 
        BuzzerConfirmBeep(); 
        break;
      case RemoteReceive::Key7:
        Display.Index = 6; 
        BuzzerConfirmBeep(); 
        break;
      case RemoteReceive::KeyOK:
        Global.xEditMode = true;
        BuzzerConfirmBeep(); 
        break;
    }
  }
  // #### DIRECT CHOOSE IN MAIN MENU END####
  // #### MAIN MENU END ####

  // #### EDIT MODE ####
  else if (Global.xEditMode) {
    switch (Display.Index) {
      case 0:
        if ((Remote.Button == RemoteReceive::KeyUP || Remote.Button == RemoteReceive::KeyRIGHT) && Strip1.ColorIndex < 10) {
          Strip1.ColorIndex++;
          BuzzerConfirmBeep();
        } else if ((Remote.Button == RemoteReceive::KeyDOWN || Remote.Button == RemoteReceive::KeyLEFT) && Strip1.ColorIndex != 0) {
          Strip1.ColorIndex--;
          BuzzerConfirmBeep();
        }
        break;
      case 1:
        if ((Remote.Button == RemoteReceive::KeyUP || Remote.Button == RemoteReceive::KeyRIGHT) && Strip2.ColorIndex < 10) {
          Strip2.ColorIndex++;
          BuzzerConfirmBeep();
        } else if ((Remote.Button == RemoteReceive::KeyDOWN || Remote.Button == RemoteReceive::KeyLEFT) && Strip2.ColorIndex != 0) {
          Strip2.ColorIndex--;
          BuzzerConfirmBeep();
        }
        break;
      case 2:
        if ((Remote.Button == RemoteReceive::KeyUP || Remote.Button == RemoteReceive::KeyRIGHT) && Strip1.Brightness != 200) {
          Strip1.Brightness += 10;
          BuzzerConfirmBeep();
        } else if ((Remote.Button == RemoteReceive::KeyDOWN || Remote.Button == RemoteReceive::KeyLEFT) && Strip1.Brightness != 10) {
          Strip1.Brightness-= 10;
          BuzzerConfirmBeep();
        }
        break;
      case 3:
        if ((Remote.Button == RemoteReceive::KeyUP || Remote.Button == RemoteReceive::KeyRIGHT) && Strip2.Brightness != 200) {
          Strip2.Brightness += 10;
          BuzzerConfirmBeep();
        } else if ((Remote.Button == RemoteReceive::KeyDOWN || Remote.Button == RemoteReceive::KeyLEFT) && Strip2.Brightness != 10) {
          Strip2.Brightness -= 10;
          BuzzerConfirmBeep();
        }
        break;
      case 4:
        if ((Remote.Button == RemoteReceive::KeyUP || Remote.Button == RemoteReceive::KeyRIGHT) && Strip1.Mode != 55) {
          Strip1.Mode++;
          BuzzerConfirmBeep();
        } else if ((Remote.Button == RemoteReceive::KeyDOWN || Remote.Button == RemoteReceive::KeyLEFT) && Strip1.Mode != 0) {
          Strip1.Mode--;
          BuzzerConfirmBeep();
        }
        break;
      case 5:
        if ((Remote.Button == RemoteReceive::KeyUP || Remote.Button == RemoteReceive::KeyRIGHT) && Strip2.Mode != 55) {
          Strip2.Mode++;
          BuzzerConfirmBeep();
        } else if ((Remote.Button == RemoteReceive::KeyDOWN || Remote.Button == RemoteReceive::KeyLEFT) && Strip2.Mode != 0) {
          Strip2.Mode--;
          BuzzerConfirmBeep();
        }
        break;
      case 6:
        if ((Remote.Button == RemoteReceive::KeyUP || Remote.Button == RemoteReceive::KeyRIGHT) && Strip1.Speed != 20) {
          Strip1.Speed++;
          BuzzerConfirmBeep();
        } else if ((Remote.Button == RemoteReceive::KeyDOWN || Remote.Button == RemoteReceive::KeyLEFT) && Strip1.Speed != 0) {
          Strip1.Speed--;
          BuzzerConfirmBeep();
        }
        break;
      case 7:
        if ((Remote.Button == RemoteReceive::KeyUP || Remote.Button == RemoteReceive::KeyRIGHT) && Strip2.Speed != 20) {
          Strip2.Speed++;
          BuzzerConfirmBeep();
        } else if ((Remote.Button == RemoteReceive::KeyDOWN || Remote.Button == RemoteReceive::KeyLEFT) && Strip2.Speed != 0) {
          Strip2.Speed--;
          BuzzerConfirmBeep();
        }
        break;
    }
      if (Remote.Button == RemoteReceive::KeyOK){
        Global.xEditMode = false;
        BuzzerConfirmBeep();
      }
      // #### EDIT MODE END ####
  }
}
