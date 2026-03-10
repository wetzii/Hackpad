# ─────────────────────────────────────────────────────────────────────────────
#  NUMPAD PRO - KMK Firmware
#  Hardware:  Seeed Studio XIAO RP2040 (DIP)
#  Matrix:    4 rows x 3 cols (12 keys) with diodes (ROW2COL)
#  Encoder:   Rotary encoder button only (rotation not connected)
#  Display:   SSD1306 OLED 128x32 via I2C
# ─────────────────────────────────────────────────────────────────────────────

import board
import busio
import displayio
import terminalio
from adafruit_display_text import label
import adafruit_displayio_ssd1306

from kmk.kmk_keyboard import KMKKeyboard
from kmk.keys import KC
from kmk.matrix import KeyMatrix
from kmk.scanners import DiodeOrientation
from kmk.modules.encoder import EncoderHandler
from kmk.extensions.media_keys import MediaKeys

# ─────────────────────────────────────────────────────────────────────────────
#  OLED Display Setup
#  SDA → GPIO6 (pin 5 on XIAO)
#  SCL → GPIO7 (pin 6 on XIAO)
#  Resolution: 128x32 pixels
#  I2C Address: 0x3C (standard for SSD1306)
# ─────────────────────────────────────────────────────────────────────────────

# Release any previously used displays
displayio.release_displays()

# Initialize I2C bus
i2c = busio.I2C(scl=board.GPIO7, sda=board.GPIO6)

# Create display bus and display object
display_bus = displayio.I2CDisplay(i2c, device_address=0x3C)
display = adafruit_displayio_ssd1306.SSD1306(display_bus, width=128, height=32)

# Create root display group
splash = displayio.Group()
display.show(splash)

# Black background fill
bg_bitmap = displayio.Bitmap(128, 32, 1)
bg_palette = displayio.Palette(1)
bg_palette[0] = 0x000000  # Black
bg_sprite = displayio.TileGrid(bg_bitmap, pixel_shader=bg_palette, x=0, y=0)
splash.append(bg_sprite)

# Line 1 - Main title (top of screen)
line1 = label.Label(
    terminalio.FONT,
    text="  NUMPAD PRO",
    color=0xFFFFFF,  # White text
    x=0,
    y=8,
    scale=1,
)
splash.append(line1)

# Line 2 - Subtitle (bottom of screen)
line2 = label.Label(
    terminalio.FONT,
    text=" XIAO RP2040 KMK",
    color=0xFFFFFF,  # White text
    x=0,
    y=22,
    scale=1,
)
splash.append(line2)

# ─────────────────────────────────────────────────────────────────────────────
#  Keyboard Initialization
# ─────────────────────────────────────────────────────────────────────────────
keyboard = KMKKeyboard()

# ─────────────────────────────────────────────────────────────────────────────
#  Key Matrix Configuration
#
#  Row Pins:
#    ROW1 → GPIO0  (pin 7)
#    ROW2 → GPIO4  (pin 10)
#    ROW3 → GPIO2  (pin 9)
#    ROW4 → GPIO1  (pin 8)
#
#  Column Pins:
#    COL1 → GPIO26 (pin 1)
#    COL2 → GPIO27 (pin 2)
#    COL3 → GPIO28 (pin 3)
#
#  Diode orientation: ROW2COL
#  (diode cathode faces the row line)
#
#  Physical layout:
#  ┌──────┬──────┬──────┐
#  │ SW1  │ SW5  │ SW9  │  ROW1
#  │  7   │  9   │  3   │
#  ├──────┼──────┼──────┤
#  │ SW2  │ SW6  │ SW10 │  ROW2
#  │  4   │  5   │ BSPC │
#  ├──────┼──────┼──────┤
#  │ SW3  │ SW7  │ SW11 │  ROW3
#  │  1   │  6   │ ENT  │
#  ├──────┼──────┼──────┤
#  │ SW4  │ SW8  │ SW12 │  ROW4
#  │  8   │  2   │  0   │
#  └──────┴──────┴──────┘
# ─────────────────────────────────────────────────────────────────────────────
keyboard.matrix = KeyMatrix(
    row_pins=(board.GPIO0, board.GPIO4, board.GPIO2, board.GPIO1),
    col_pins=(board.GPIO26, board.GPIO27, board.GPIO28),
    diode_orientation=DiodeOrientation.ROW2COL,
)

# ─────────────────────────────────────────────────────────────────────────────
#  Extensions
#  MediaKeys: enables consumer keycodes like KC.MUTE
# ─────────────────────────────────────────────────────────────────────────────
keyboard.extensions.append(MediaKeys())

# ─────────────────────────────────────────────────────────────────────────────
#  Rotary Encoder Configuration
#  SW17 - Button only (rotation pins A/B not connected to MCU)
#  Button → GPIO3 (pin 11)
#  Press = System Mute toggle (works in all apps)
# ─────────────────────────────────────────────────────────────────────────────
encoder_handler = EncoderHandler()
encoder_handler.pins = (
    (board.GPIO3, None, None, True),  # (button_pin, pin_a, pin_b, use_pullup)
)
encoder_handler.map = [
    (
        (KC.NO, KC.NO, KC.MUTE),  # (turn_left, turn_right, press)
    ),
]
keyboard.modules.append(encoder_handler)

# ─────────────────────────────────────────────────────────────────────────────
#  Keymap - Layer 0 (only layer)
#  Keys are listed row by row, left to right
# ─────────────────────────────────────────────────────────────────────────────
keyboard.keymap = [
    [
        # ROW1: SW1,   SW5,   SW9
        KC.N7,  KC.N9,  KC.N3,
        # ROW2: SW2,   SW6,   SW10
        KC.N4,  KC.N5,  KC.BSPC,
        # ROW3: SW3,   SW7,   SW11
        KC.N1,  KC.N6,  KC.ENT,
        # ROW4: SW4,   SW8,   SW12
        KC.N8,  KC.N2,  KC.N0,
    ]
]

# ─────────────────────────────────────────────────────────────────────────────
#  Start the keyboard
# ─────────────────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    keyboard.go()
