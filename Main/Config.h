#pragma once

#include <Arduino.h>

// #### FIRMWARE ####

constexpr char NAME_VERSION[] = "LUNA";
constexpr char FW_VERSION[] = "1.0.0";
constexpr char HW_VERSION[] = "LIGHTBOX_V1";

// ################
// #### INPUTS ####
// ################

// #### IR RECEIVER ####
constexpr uint8_t IR_RECEIVE_PIN = 22;
// #### IR RECEIVER END ####

// #####################
// #### INPUTS END  ####
// #####################

// #################
// #### OUTPUTS ####
// #################

// #### BUZZER ####
constexpr uint8_t PIN_BUZZER = 23; // PIN FROM BUZZER
// #### BUZZER END ####

// #### TM1637 DISPLAY ####
constexpr uint8_t PIN_TM1637_CLK = 21; // PIN CLK FROM TM1637
constexpr uint8_t PIN_TM1637_DIO = 19; // PIN DIO FROM TM1637
// #### TM1637 DISPLAY END ####

// #### WS2812 LED STRIP 1 ####
constexpr uint8_t PIN_LED_STRIP_1 = 13; // PIN LED STRIP 1 (LED STRIP TOP)
constexpr uint16_t LED_COUNT_1 = 28; // LED STIP COUNT
// #### WS2812 LED STRIP 1 END ####

// #### WS2812 LED STRIP 2 ####
constexpr uint8_t PIN_LED_STRIP_2 = 14; // PIN LED STRIP 2 (LED STRIP BOTTOM)
constexpr uint16_t LED_COUNT_2 = 8; // LED STRIP COUNT
// #### WS2812 LED STRIP 2 END ####

// #####################
// #### OUTPUTS END ####
// #####################


// ### OTA UPDATE URL ####
constexpr char OTA_MANIFEST_URL[] =
    "https://raw.githubusercontent.com/MrTiiv/LightboxHW1OTA/refs/heads/main/update%2Cjson";
// ### OTA UPDATE URL END ####

// #### LICENCE ####

//MIT License

//Copyright (c) [2026] [MrTiiv]

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.