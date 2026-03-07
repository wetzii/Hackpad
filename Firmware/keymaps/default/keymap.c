#include QMK_KEYBOARD_H

// Layer Definitionen
enum layers {
    _NUMPAD,   // Standard Numpad Layer
    _SHORTCUTS // Shortcut Layer (gehalten durch untersten rechten Key)
};

// Keymap
// Layout: 4x4 Matrix
// Spalten 0-2 = Numpad | Spalte 3 = Shortcuts
// ┌─────┬─────┬─────┬─────┐
// │  7  │  8  │  9  │ F13 │  ← Row 0
// │  4  │  5  │  6  │ F14 │  ← Row 1
// │  1  │  2  │  3  │ F15 │  ← Row 2
// │  0  │  .  │Enter│ MO1 │  ← Row 3 (MO1 = Shortcut Layer halten)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_NUMPAD] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,   KC_F13,
        KC_P4,   KC_P5,   KC_P6,   KC_F14,
        KC_P1,   KC_P2,   KC_P3,   KC_F15,
        KC_P0,   KC_PDOT, KC_PENT, MO(_SHORTCUTS)
    ),

    [_SHORTCUTS] = LAYOUT(
        // Layer 1: Shortcuts (gehalten durch MO1)
        // Spalten 0-2 = Ctrl+Z/Y/S usw. | Spalte 3 = Mute (Encoder Knopf Funktion hier auch)
        LCTL(KC_Z),  LCTL(KC_Y),  LCTL(KC_S),  _______,
        LCTL(KC_C),  LCTL(KC_V),  LCTL(KC_X),  _______,
        LCTL(KC_A),  LCTL(KC_F),  KC_DEL,       _______,
        LCTL(KC_W),  LALT(KC_F4), LCTL(KC_T),  _______
    )
};

// ── OLED Display ──────────────────────────────────────────────────────────────

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

bool oled_task_user(void) {
    // Zeile 1: Name
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("  Wetzii Hackpad"), false);

    // Zeile 2: Trennlinie
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("----------------"), false);

    // Zeile 3: Aktiver Layer
    oled_set_cursor(0, 2);
    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:
            oled_write_P(PSTR("Layer: NUMPAD   "), false);
            break;
        case _SHORTCUTS:
            oled_write_P(PSTR("Layer: SHORTCUTS"), false);
            break;
        default:
            oled_write_P(PSTR("Layer: UNKNOWN  "), false);
            break;
    }

    // Zeile 4: Num Lock Status
    oled_set_cursor(0, 3);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM: ON  ") : PSTR("NUM: OFF "), false);

    return false;
}

#endif // OLED_ENABLE

// ── Encoder Knopf (GP3) als Mute/Unmute ───────────────────────────────────────
// Der Encoder-Klick ist über config.h als ENCODER_SW_PIN = GP3 definiert.
// In QMK wird er als Matrix-unabhängiger Key behandelt.
// Wir nutzen process_record_user um einen direkten Mute-Key zu bauen.

// Optional: Falls du den Mute-Knopf direkt in die Matrix einbauen willst,
// verbinde GP3 als zusätzliche Row oder direkt über DIRECT_PINS.
// Für jetzt ist er als AUDIO_MUTE über F16 belegbar wenn du ihn in die Matrix bringst.
