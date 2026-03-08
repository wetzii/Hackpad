// Copyright 2024 Hackpad
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// -------------------------------------------------------------------------
// XIAO RP2040 DIP - Pin Mapping
// Pin 1  = GP26 = COL1
// Pin 2  = GP27 = COL2
// Pin 3  = GP28 = COL3
// Pin 4  = GP29 = COL4
// Pin 5  = GP6  = SDA (OLED)
// Pin 6  = GP7  = SCL (OLED)
// Pin 7  = GP0  = ROW1
// Pin 8  = GP1  = ROW4
// Pin 9  = GP2  = ROW3
// Pin 10 = GP4  = ROW2
// Pin 11 = GP3  = ENC_SW (nur Taster)
// -------------------------------------------------------------------------

#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7
#define I2C1_CLOCK_SPEED 400000

#define OLED_DISPLAY_128X32
#define OLED_TIMEOUT 30000
#define OLED_I2C_ADDRESS 0x3C

#define DEBOUNCE 5
