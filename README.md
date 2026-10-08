
# Lightbox Hardware Version 1

This is the repo of my self-designed Lightbox. You can see in the pictures below how it looks.

I created two Lightboxes as gifts for the Artists [@MyunaArt](https://myuna-art.com/) and  [@yumiioosdoodles](https://linktr.ee/yumiiosdoodles?utm_source=linktree_profile_share&ltsid=7fec71ab-67c4-4d89-bf50-f49b9ad849fc)

Here I will describe the functionality of the Lightbox with my Code and also which Hardware is inside and which libraries I used for the Code.

This Project is released under the [MIT License](https://github.com/MrTiiv/Lightbox-V1/blob/main/LICENSE). You can find the License in this Repo.

This Project was made with all the love I am legally allowed to give. 





## AI Transparency

As stated in my profile description, I want to be transparent about how I use AI in my projects.

I used Codex for this project.

If you want to know how I used AI for this project, you can see it in the [AI-Transparency.md](https://github.com/MrTiiv/Lightbox-V1/blob/main/AI-Transparency.md)

**AI DID NOT WRITE ANY OF THE MAIN CODE. THE MAIN CODE WAS WRITTEN BY ME**

## Pictures of the Lightbox


![Picture1](https://github.com/MrTiiv/Lightbox-V1/blob/main/Pictures/lightboxY1.png?raw=true)
![Picture2](https://github.com/MrTiiv/Lightbox-V1/blob/main/Pictures/lightboxM1.png?raw=true)
You can see more pictures in the [Picture Folder](https://github.com/MrTiiv/Lightbox-V1/tree/main/Pictures)


## Manual
Here I will now describe how the Lightbox works and what each Menu point means.

If the IR Sensor in the Back of the Base box is not recognizing a Valid Signal for 30 Seconds the Display in the Back will turn off. 

If the IR Sensor recognizes a Valid Signal from the Remote, the display will turn on and display the current chosen Menu function. 

Also, when the Display turns off, the Controller inside the Box will save the Current Options so in case of a Power loss the last state will be loaded. 

Use the "UP","DOWN","LEFT" and "RIGHT" buttons to navigate through the menu.

Press "OK" to edit the selected menu option. Press "OK" again to return to the main menu.

Press "*" to put the lightbox into standby mode. Press it again to restore the previous state.

Press "#" to start OTA mode.

### Main Menu:

1 refers to the top LED strip.

2 refers to the bottom LED strip.

| Menu Name | Setting | Possible Values | Description |
|-----------|------------|-----------------|------------|
|1COL / 2COL | Color for the LEDs| 0  - 10 | Choose the Color of the LEDs|
|1bri / 2bri | Brightness for the LEDs | 10 - 200 | Choose the Brightness of the LEDs |
|1Ani / 2Ani | Animation for the LEDs | 0 - 55 | Choose the Animation of the LEDs |
|1SPE / 2SPE | Speed for the LEDs | 0 - 20 | Sets the speed for supported animations. |

### Colors:

| Number | Color |
|:--------:|-------|
|0 | OFF |
|1 | RED |
|2 | ORANGE |
|3 | YELLOW |
|4 | GREEN | 
|5 | CYAN |
|6 | BLUE |
|7 | PURPLE |
|8 | MAGENTA |
|9 | PINK |
|10| WHITE |

### Animations: 

| Number | Effect | Description |
|:---:|--------|-------------|
| 0 | **Static** | No blinking. Just plain old static light. |
| 1 | **Blink** | Normal blinking. 50% on/off time. |
| 2 | **Breath** | Does the "standby-breathing" of well known i-Devices. Fixed Speed. |
| 3 | **Color Wipe** | Lights all LEDs after each other up. Then turns them in that order off. Repeat. |
| 4 | **Color Wipe Inverse** | Same as Color Wipe, except swaps on/off colors. |
| 5 | **Color Wipe Reverse** | Lights all LEDs after each other up. Then turns them in reverse order off. Repeat. |
| 6 | **Color Wipe Reverse Inverse** | Same as Color Wipe Reverse, except swaps on/off colors. |
| 7 | **Color Wipe Random** | Turns all LEDs after each other to a random color. Then starts over with another color. |
| 8 | **Random Color** | Lights all LEDs in one random color up. Then switches them to the next random color. |
| 9 | **Single Dynamic** | Lights every LED in a random color. Changes one random LED after the other to a random color. |
| 10 | **Multi Dynamic** | Lights every LED in a random color. Changes all LED at the same time to new random colors. |
| 11 | **Rainbow** | Cycles all LEDs at once through a rainbow. |
| 12 | **Rainbow Cycle** | Cycles a rainbow over the entire string of LEDs. |
| 13 | **Scan** | Runs a single pixel back and forth. |
| 14 | **Dual Scan** | Runs two pixel back and forth in opposite directions. |
| 15 | **Fade** | Fades the LEDs on and (almost) off again. |
| 16 | **Theater Chase** | Theatre-style crawling lights. Inspired by the Adafruit examples. |
| 17 | **Theater Chase Rainbow** | Theatre-style crawling lights with rainbow effect. Inspired by the Adafruit examples. |
| 18 | **Running Lights** | Running lights effect with smooth sine transition. |
| 19 | **Twinkle** | Blink several LEDs on, reset, repeat. |
| 20 | **Twinkle Random** | Blink several LEDs in random colors on, reset, repeat. |
| 21 | **Twinkle Fade** | Blink several LEDs on, fading out. |
| 22 | **Twinkle Fade Random** | Blink several LEDs in random colors on, fading out. |
| 23 | **Sparkle** | Blinks one LED at a time. |
| 24 | **Flash Sparkle** | Lights all LEDs in the selected color. Flashes single white pixels randomly. |
| 25 | **Hyper Sparkle** | Like flash sparkle. With more flash. |
| 26 | **Strobe** | Classic Strobe effect. |
| 27 | **Strobe Rainbow** | Classic Strobe effect. Cycling through the rainbow. |
| 28 | **Multi Strobe** | Strobe effect with different strobe count and pause, controlled by speed setting. |
| 29 | **Blink Rainbow** | Classic Blink effect. Cycling through the rainbow. |
| 30 | **Chase White** | Color running on white. |
| 31 | **Chase Color** | White running on color. |
| 32 | **Chase Random** | White running followed by random color. |
| 33 | **Chase Rainbow** | White running on rainbow. |
| 34 | **Chase Flash** | White flashes running on color. |
| 35 | **Chase Flash Random** | White flashes running, followed by random color. |
| 36 | **Chase Rainbow White** | Rainbow running on white. |
| 37 | **Chase Blackout** | Black running on color. |
| 38 | **Chase Blackout Rainbow** | Black running on rainbow. |
| 39 | **Color Sweep Random** | Random color introduced alternating from start and end of strip. |
| 40 | **Running Color** | Alternating color/white pixels running. |
| 41 | **Running Red Blue** | Alternating red/blue pixels running. |
| 42 | **Running Random** | Random colored pixels running. |
| 43 | **Larson Scanner** | K.I.T.T. |
| 44 | **Comet** | Firing comets from one end. |
| 45 | **Fireworks** | Firework sparks. |
| 46 | **Fireworks Random** | Random colored firework sparks. |
| 47 | **Merry Christmas** | Alternating green/red pixels running. |
| 48 | **Fire Flicker** | Fire flickering effect. Like in harsh wind. |
| 49 | **Fire Flicker (soft)** | Fire flickering effect. Runs slower/softer. |
| 50 | **Fire Flicker (intense)** | Fire flickering effect. More range of color. |
| 51 | **Circus Combustus** | Alternating white/red/black pixels running. |
| 52 | **Halloween** | Alternating orange/purple pixels running. |
| 53 | **Bicolor Chase** | Two LEDs running on a background color. |
| 54 | **Tricolor Chase** | Alternating three color pixels running. |
| 55 | **TwinkleFOX** | Lights fading in and out randomly. |

(LEDs are using the [WS2812fx Library from kitesurfer](https://github.com/kitesurfer1404/WS2812FX))

### OTA Mode
Starting OTA mode turns off the top LED strip and activates a scanning effect on the bottom LED strip.

The lightbox creates a Wi-Fi hotspot named "Very Cool Lightbox". The password is "madewithlove"

![WiFi](https://github.com/MrTiiv/Lightbox-V1/blob/main/Pictures/WLAN.png?raw=true)

After connecting to the hotspot, the update portal should open automatically.

![CaptivePortal](https://github.com/MrTiiv/Lightbox-V1/blob/main/Pictures/LightboxOTAGUI.png?raw=true)

In the portal, select your "Wi-Fi" network and enter its password. Press "Update starten" to check the OTA repository for an available update. If a valid update is found, it will be installed automatically.

When the update is complete, the Lightbox will restart.

Don't worry if the update fails or the lightbox loses power during the process. The device can recover from an interrupted update. 

OTA mode is disabled after five minutes of inactivity, after a successful update, or when the device loses power. 
## Hardware

The following table lists all hardware components used in this project.

| Component | Model / Specification | Description |
|---|---|---|
| **Microcontroller** | ESP32 NodeMCU (diymore, CH340, USB-C) | Development board with 2.4 GHz Wi-Fi and Bluetooth for controlling the project. |
| **USB-C Connector** | USB 3.1 Type-C, 4-Pin/2-Pin | USB-C female connector with screw-mounting plate for power supply. |
| **IR Receiver** | HX1838 | Infrared receiver module with remote control for wireless operation. |
| **7-Segment Display** | TM1637, 0.36", 4-Digit | Four-digit LED display for showing numbers and status information. |
| **Passive Buzzer** | 12085, 12 × 8.5 mm, 42 Ω | Passive piezo buzzer for generating audio signals and notifications. |
| **Addressable LED Strip** | BTF-LIGHTING WS2812 ECO, 5 m, 300 LEDs, 5050 SMD | Individually addressable RGB LED strip with 60 LEDs/m and a flexible black PCB for customizable lighting effects. |
## Electrical Diagram

![ElectricDiagram](https://github.com/MrTiiv/Lightbox-V1/blob/main/ElectricDiagram/lightbox_schem.png?raw=true)
## Used Libraries

| Library| Version | Author |
|---|:---:|---|
| Adafruit NeoPixel | 1.15.5 | Adafruit |
| ArduinoJson | 7.4.3 | Benoit Blanchon |
| Async TCP | 3.5.0 | ESP32Async |
| ESPUI | 2.2.4 | Lukas Bachschwell |
| ESP Async WebServer | 3.12.1 | ESP32Async |
| IRremote | 4.7.1 | shirriff, z3t0, ArminJo |
| PLCBlocks | 1.0.0 | MrTiiv |
| TM1637 Driver | 2.2.1 | AKJ |
| WS2812FX | 1.4.7 | Harm Aldick |
| ezBuzzer | 1.0.2 | ArduinoGetStarted.com |
## End

This Project was made with ❤️

You can see a list of all my Projects on my Website [MrTiiv.de](https://mrtiiv.de/)

You know what? Have a random cat:

![Cat](https://cataas.com/cat)

GitHub likes caching images, so this cat may stick around for a while.