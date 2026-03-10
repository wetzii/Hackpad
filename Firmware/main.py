import board
import busio
import displayio
import terminalio
from adafruit_display_text import label
import adafruit_displayio_ssd1306

from kmk.kmk_keyboard import KMKKeyboard
from kmk.keys import KC
from kmk.scanners.keypad import KeysScanner
from kmk.scanners import DiodeOrientation
from kmk.matrix import KeyMatrix
from kmk.modules.encoder import EncoderHandler
from kmk.extensions.media_keys import MediaKeys

# ─────────────────────────────────────────────
#  OLED Setup (I2C: SDA=GPIO6, SCL=GPIO7)
# ─────────────────────────────────────────────
displayio.release_displays()

i2c = busio.I2C(scl=board.GPIO7, sda=board.GPIO6)
display_bus = displayio.I2CDisplay(i2c, device_address=0x3C)
display = adafruit_displayio_ssd1306.SSD1306(display_bus, width=128, height=32)

# Splash Screen
splash = displayio.Group()
display.show(splash)

# Hintergrund schwarz
bg_bitmap = displayio.Bitmap(128, 32, 1)
bg_palette = displayio.Palette(1)
bg_palette[0] = 0x000000
bg_sprite = displayio.TileGrid(bg_bitmap, pixel_shader=bg_palette, x=0, y=0)
splash.append(bg_sprite)

# Zeile 1: Großer Text
line1 = label.Label(
    terminalio.FONT,
    text="  NUMPAD PRO",
    color=0xFFFFFF,
    x=0,
    y=8,
    scale=1,
)
splash.append(line1)

# Zeile 2: Kleiner Untertitel
line2 = label.Label(
    terminalio.FONT,
    text=" XIAO RP2040 KMK",
    color=0xFFFFFF,
    x=0,
    y=22,
    scale=1,
)
splash.append(line2)

# ─────────────────────────────────────────────
#  Keyboard Setup
# ─────────────────────────────────────────────
keyboard = KMKKeyboard()

# Matrix: 4 Zeilen x 3 Spalten
# ROW1=GPIO0, ROW2=GPIO4, ROW3=GPIO2, ROW4=GPIO1
# COL1=GPIO26, COL2=GPIO27, COL3=GPIO28
keyboard.matrix = KeyMatrix(
    row_pins=(board.GPIO0, board.GPIO4, board.GPIO2, board.GPIO1),
    col_pins=(board.GPIO26, board.GPIO27, board.GPIO28),
    diode_orientation=DiodeOrientation.ROW2COL,
)

# ─────────────────────────────────────────────
#  Media Keys Extension (für MUTE)
# ─────────────────────────────────────────────
keyboard.extensions.append(MediaKeys())

# ─────────────────────────────────────────────
#  Rotary Encoder (nur Button - GPIO3)
#  Drehfunktion NICHT angeschlossen → nur SW (Mute Toggle)
# ─────────────────────────────────────────────
encoder_handler = EncoderHandler()
encoder_handler.pins = ((board.GPIO3, None, None, True),)  # (SW, A, B, pullup)
encoder_handler.map = [
    # (drehen links, drehen rechts, drücken)
    ((KC.NO, KC.NO, KC.MUTE),),
]
keyboard.modules.append(encoder_handler)

# ─────────────────────────────────────────────
#  Keymap
#  Layout laut PCB (Bild 3):
#
#  ROW1: SW1=7   SW5=9   SW9=3
#  ROW2: SW2=4   SW6=5   SW10=BSPC
#  ROW3: SW3=1   SW7=6   SW11=ENTER  (SW11 fehlt → SW7=9? → Nein, lt. Bestätigung)
#  ROW4: SW4=8   SW8=?   SW12=0
#
#  Korrigiertes Layout nach Bestätigung:
#  ROW1: SW1=7,  SW5=9,  SW9=3
#  ROW2: SW2=4,  SW6=5,  SW10=BSPC
#  ROW3: SW3=1,  SW7=6,  SW11=ENTER
#  ROW4: SW4=8,  SW8=2,  SW12=0     (SW8 laut Bild = 6... aber SW6=5, SW9=3)
#
#  Finales bestätigtes Layout:
#  Spalte:   COL1    COL2    COL3
#  ROW1:     SW1=7   SW5=9   SW9=3
#  ROW2:     SW2=4   SW6=5   SW10=BSPC
#  ROW3:     SW3=1   SW7=6   SW11=ENT
#  ROW4:     SW4=8   SW8=2   SW12=0
# ─────────────────────────────────────────────
keyboard.keymap = [
    [
        # ROW1
        KC.N7,    KC.N9,    KC.N3,
        # ROW2
        KC.N4,    KC.N5,    KC.BSPC,
        # ROW3
        KC.N1,    KC.N6,    KC.ENT,
        # ROW4
        KC.N8,    KC.N2,    KC.N0,
    ]
]

if __name__ == "__main__":
    keyboard.go()
