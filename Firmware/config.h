#pragma once

// Bootloader double-tap reset für XIAO RP2040
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

// Matrix
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

// OLED I2C Pins (GP6 = SDA, GP7 = SCL am XIAO RP2040)
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

// OLED Einstellungen
#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_TIMEOUT 30000

// Encoder Knopf (Mute) - als direkter Pin
#define ENCODER_SW_PIN GP3

// Debounce
#define DEBOUNCE 5
