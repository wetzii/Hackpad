#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        /* Spalte 1   Spalte 2   Spalte 3   Spalte 4 (Shortcuts) */
        KC_P7,     KC_P8,     KC_P9,     KC_NO,    
        KC_P4,     KC_P5,     KC_P6,     KC_NO,    
        KC_P1,     KC_P2,     KC_P3,     KC_NO,    
        KC_P0,     KC_PDOT,   KC_PENT,   KC_NO     
    )
};

/* Encoder Steuerung (z.B. Lautstärke) */
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}