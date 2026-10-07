#include <ezBuzzer.h>
#include "Variables.h"

ezBuzzer buzzer(PIN_BUZZER, BUZZER_TYPE_PASSIVE, HIGH);

// #### Startup Melody ####
int startupMelody[] =
{
    2093,
    2637,
    3136,
    3520,
    3136,
    3951
};

int startupDurations[] =
{
    16,
    16,
    16,
    8,
    16,
    4
};

const int startupLength =
    sizeof(startupMelody) / sizeof(startupMelody[0]);

// #### Startup Melody END ####

// #### Standby Melody ####

int standbyMelody[] =
{
  1047, 
  1319, 
  1047  
};

int standbyDurations[] =
{
  16,
  16,
  8
};

const int standbyLength =
    sizeof(standbyMelody) / sizeof(standbyMelody[0]);

// #### Standby Melody END ####

// #### OTA Melody ####

int otaMelody[] =
{
  1568, 784,  
  1568, 784,  
  1568, 784,  
  1568, 784, 
  1568, 784  
};

int otaDurations[] =
{
  16, 16,
  16, 16,
  16, 16,
  16, 16,
  16, 16
};

const int otaLength =
    sizeof(otaMelody) / sizeof(otaMelody[0]);

// #### OTA Melody END ####

void BuzzerLoop(){
  buzzer.loop();
};

void BuzzerStratupMelody(){
  buzzer.playMelody(startupMelody, startupDurations, startupLength);
};

void BuzzerStandbyMelody() {
  buzzer.playMelody(standbyMelody, standbyDurations, standbyLength);
}

void BuzzerOTAMelody() {
  buzzer.playMelody(otaMelody, otaDurations, otaLength);
}

void BuzzerConfirmBeep(){
  buzzer.beep(250, 0, 800);
};