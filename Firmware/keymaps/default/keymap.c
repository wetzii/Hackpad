#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,   KC_F13,
        KC_P4,   KC_P5,   KC_P6,   KC_F14,
        KC_P1,   KC_P2,   KC_P3,   KC_F15,
        KC_P0,   KC_PDOT, KC_PENT, MO(1)
    ),
    [1] = LAYOUT(
        LCTL(KC_Z), LCTL(KC_Y), LCTL(KC_S), _______,
        LCTL(KC_C), LCTL(KC_V), LCTL(KC_X), _______,
        LCTL(KC_A), LCTL(KC_F), KC_DEL,     _______,
        LCTL(KC_W), LALT(KC_F4),LCTL(KC_T), _______
    )
};
