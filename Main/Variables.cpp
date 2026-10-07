#include "Variables.h"
#include <Preferences.h>

Preferences prefs; 

// ########################
// ########################
// #### DEFAULT VALUES ####
// ########################
// ########################


// #### GLOBAL VARIABLES ####

GlobalData Global =
{
  false,  //  Global.xStandby
  true,   //  Global.xNoStandby
  false,  //  Global.xEditMode
  false,  //  Global.xOTAActive
};

// #### GLOBAL VARIABLES END ####

// #### WS2812 LED STRIP ####

LEDStripData Strip1 =
{
  1,    //  Strip1.ColorIndex
  0,    //  Strip1.Mode
  100,  //  Strip1.Brightness 
  10,   //  Strip1.Speed
  0,    //  Strip1.MAXCOLORCOUNT
  false //  Strip1.xSleep
};

LEDStripData Strip2 =
{
  1,    //  Strip1.ColorIndex
  0,    //  Strip1.Mode
  100,  //  Strip1.Brightness 
  10,   //  Strip1.Speed
  0,    //  Strip1.MAXCOLORCOUNT
  false //  Strip1.xSleep
};

// #### WS2812 LED STRIP END ####

// #### TM1637 DISPLAY ####

DisplayData Display = 
{
  DisplayIndexData::OFF,
  0,    //  Display.Index
  false //  Display.xStandby
};

// #### TM1637 Display END ####

// #### IR REMOTE ####

RemoteData Remote =
{
  false,  //  Remote.xPushed
  false,  //  Remote.xAfk
  RemoteReceive::NONE

};

// #### IR REMOTE END ####

// ############################
// ############################
// #### DEFAULT VALUES END ####
// ############################
// ############################


// ##############################
// ##############################
// #### LOAD DATA FROM FLASH ####
// ##############################
// ##############################

void LoadVariables(){
  prefs.begin("lightbox", false);

  //#### LOAD DATA FOR STRIP 1 ####
  Strip1.ColorIndex = prefs.getUChar("s1col", Strip1.ColorIndex);
  Strip1.Mode = prefs.getUChar("s1mode", Strip1.Mode);
  Strip1.Brightness = prefs.getUChar("s1bright", Strip1.Brightness);
  Strip1.Speed = prefs.getUChar("s1spd", Strip1.Speed);
  //#### LOAD DATA FOR STRIP 1 END ####

  //#### LOAD DATA FOR STRIP 2 ####
  Strip2.ColorIndex = prefs.getUChar("s2col", Strip2.ColorIndex);
  Strip2.Mode = prefs.getUChar("s2mode", Strip2.Mode);
  Strip2.Brightness = prefs.getUChar("s2bright", Strip2.Brightness);
  Strip2.Speed = prefs.getUChar("s2spd", Strip2.Speed);
  //#### LOAD DATA FOR STRIP 2 END ####

  prefs.end();
}
// ##################################
// ##################################
// #### LOAD DATA FROM FLASH END ####
// ##################################
// ##################################

// ############################
// ############################
// #### LOAD DATA TO FLASH ####
// ############################
// ############################

void SaveVariables(){
  prefs.begin("lightbox", false);

  //#### SAVE DATA FOR STRIP 1 ####
  prefs.putUChar("s1col", Strip1.ColorIndex);
  prefs.putUChar("s1mode", Strip1.Mode);
  prefs.putUChar("s1bright", Strip1.Brightness);
  prefs.putUChar("s1spd", Strip1.Speed);
  //#### SAVE DATA FOR STRIP 1 END ####

  //#### SAVE DATA FOR STRIP 2 ####
  prefs.putUChar("s2col", Strip2.ColorIndex);
  prefs.putUChar("s2mode", Strip2.Mode);
  prefs.putUChar("s2bright", Strip2.Brightness);
  prefs.putUChar("s2spd", Strip2.Speed);
  //#### SAVE DATA FOR STRIP 2 END ####
}

// ################################
// ################################
// #### LOAD DATA TO FLASH END ####
// ################################
// ################################
