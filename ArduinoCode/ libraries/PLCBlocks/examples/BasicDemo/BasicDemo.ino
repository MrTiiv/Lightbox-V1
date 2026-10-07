// SPDX-License-Identifier: Unlicense
// Created with assistance from OpenAI ChatGPT/Codex; see NOTICE.md.

#include <PLCBlocks.h>

using namespace PLCBlocks;

constexpr uint8_t BUTTON_PIN = 4;   // Button to GND, INPUT_PULLUP
constexpr uint8_t RESET_PIN = 5;    // Button to GND, INPUT_PULLUP
#ifdef LED_BUILTIN
constexpr uint8_t LED_PIN = LED_BUILTIN;
#else
constexpr uint8_t LED_PIN = 2;      // Common ESP32 onboard LED; adjust if needed
#endif

FirstScan firstScan;
CycleTime cycleTime;
ClockMemory clockMemory;
P_TRIG startEdge;
SR runLatch;
TON startDelay(T_SEC(2));
CTU starts;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RESET_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // Call every FB instance exactly once per scan where possible.
  firstScan.process();
  cycleTime.process();
  clockMemory.process();

  const bool start = (digitalRead(BUTTON_PIN) == LOW);
  const bool reset = (digitalRead(RESET_PIN) == LOW);

  startEdge.process(start);
  runLatch.process(startEdge.Q, reset);       // SR: reset has priority
  startDelay.process(runLatch.Q);             // Non-blocking 2 s TON
  starts.process(startEdge.Q, reset, 3);      // Count positive edges

  // After the delay, blink with clock-memory bit 5 (1 Hz period).
  digitalWrite(LED_PIN, startDelay.Q && clockMemory.Q5);

  if (firstScan.Q) {
    Serial.println("First scan");
  }

  static uint32_t lastReport = 0;
  if (millis() - lastReport >= T_SEC(1)) {
    lastReport += T_SEC(1);
    Serial.print("Run=");
    Serial.print(runLatch.Q);
    Serial.print(" TON.Q=");
    Serial.print(startDelay.Q);
    Serial.print(" ET=");
    Serial.print(static_cast<unsigned long>(startDelay.ET));
    Serial.print(" Starts=");
    Serial.print(static_cast<long>(starts.CV));
    Serial.print(" Cycle=");
    Serial.print(static_cast<unsigned long>(cycleTime.MS));
    Serial.println(" ms");
  }
}
