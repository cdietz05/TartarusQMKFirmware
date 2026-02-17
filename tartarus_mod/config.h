/*
Copyright 2026 Chris Dietz
GPL-2.0-or-later
*/

#pragma once

/*
   Pro Micro to QMK Pin Layout
           +--USB--+
      RAW  |       |  VCC
      GND  |       |  GND
      RST  |       |  RST
      GND  |       |  FND
  2 - PD1  |       |  F4 - A3
  3 - PD0  |       |  F5 - A2
  4 - PD4  |       |  F6 - A1
  5 - PC6  |       |  F7 - A0
  6 - PD7  |       |  B1 - 15
  7 - PE6  |       |  B3 - 14
  8 - PB4  |       |  B2 - 16
  9 - PB5  |       |  B6 - 10
     +-------------+
*/

/* Joystick Dummy (Satisfies the analog driver) */
#define JOYSTICK_AXES_COUNT 0
#define USB_POLLING_INTERVAL_MS 1
#define EECONFIG_USER_DATA 4