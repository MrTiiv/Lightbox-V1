#include "Variables.h"
#include <IRremote.hpp>
#include <PLCBlocks.h>
using namespace PLCBlocks;

TON delayREMOTEAFK(T_SEC(30));

void remoteSetup() {
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void remoteLoop() {
  // #### SET REMOTE DO DEFAULT OPTIONS ####
  Remote.Button = RemoteReceive::NONE;
  Remote.xPushed = false;
  // #### SET REMOTE DO DEFAULT OPTIONS END ####

  // #### REMOTE BUTTON TRANSLATOR LOGIC ####
  if (IrReceiver.decode() && !Global.xOTAActive) {
    bool isRepeat = IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT;

    if (!isRepeat) {
      switch (IrReceiver.decodedIRData.command) {
        case 69:
          Remote.Button = RemoteReceive::Key1;
          break;
        case 70:
          Remote.Button = RemoteReceive::Key2;
          break;
        case 71:
          Remote.Button = RemoteReceive::Key3;
          break;
        case 68:
          Remote.Button = RemoteReceive::Key4;
          break;
        case 64:
          Remote.Button = RemoteReceive::Key5;
          break;
        case 67:
          Remote.Button = RemoteReceive::Key6;
          break;
        case 7:
          Remote.Button = RemoteReceive::Key7;
          break;
        case 21:
          Remote.Button = RemoteReceive::Key8;
          break;
        case 9:
          Remote.Button = RemoteReceive::Key9;
          break;
        case 25:
          Remote.Button = RemoteReceive::Key0;
          break;
        case 22:
          Remote.Button = RemoteReceive::KeySTAR;
          break;
        case 13:
          Remote.Button = RemoteReceive::KeyHASH;
          break;
        case 24:
          Remote.Button = RemoteReceive::KeyUP;
          break;
        case 82:
          Remote.Button = RemoteReceive::KeyDOWN;
          break;
        case 90:
          Remote.Button = RemoteReceive::KeyRIGHT;
          break;
        case 8:
          Remote.Button = RemoteReceive::KeyLEFT;
          break;
        case 28:
          Remote.Button = RemoteReceive::KeyOK;
          break;
        case 0:
          Remote.Button = RemoteReceive::NONE;
          break;
        default:
          Remote.Button = RemoteReceive::NONE;
          break;
      }
      // #### REMOTE BUTTON TRANSLATOR LOGIC END ####

      // #### REMOTE RECEIVES SIGNAL ####
      if (Remote.Button != RemoteReceive::NONE) {
        Remote.xAfk = false;
        Remote.xPushed = true;
      }
      // #### REMOTE RECEIVES SIGNAL END ####
    }
    IrReceiver.resume();
  }
  // #### REMOTE AFK ####
  delayREMOTEAFK.process(!Remote.xPushed);
  Remote.xAfk = delayREMOTEAFK.Q;
  // #### REMOTE AFK END ####
}
