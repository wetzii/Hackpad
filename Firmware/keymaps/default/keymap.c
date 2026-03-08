// Copyright 2024 Hackpad
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _NUMPAD = 0,
    _FN,
    _CUSTOM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_NUMPAD] = LAYOUT_4x4(
        KC_P7,   KC_P8,   KC_P9,   KC_NUM,
        KC_P4,   KC_P5,   KC_P6,   KC_PSLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PAST,
        KC_P0,   KC_PDOT, KC_PENT, MO(_FN)
    ),

    [_FN] = LAYOUT_4x4(
        KC_PMNS, KC_PPLS, KC_PEQL, _______,
        KC_MPRV, KC_MPLY, KC_MNXT, _______,
        KC_VOLD, KC_MUTE, KC_VOLU, _______,
        TG(_CUSTOM), _______, _______, _______
    ),

    [_CUSTOM] = LAYOUT_4x4(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,
        KC_F5,   KC_F6,   KC_F7,   KC_F8,
        KC_F9,   KC_F10,  KC_F11,  KC_F12,
        TG(_CUSTOM), KC_PSCR, KC_SCRL, KC_PAUS
    ),
};

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

bool oled_task_user(void) {
    oled_set_cursor(0, 0);
    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:  oled_write_P(PSTR("NUMPAD          "), false); break;
        case _FN:      oled_write_P(PSTR("FN / MEDIA      "), false); break;
        case _CUSTOM:  oled_write_P(PSTR("CUSTOM          "), false); break;
        default:       oled_write_P(PSTR("???             "), false); break;
    }

    oled_set_cursor(0, 1);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_P(PSTR("NUM:"), false);
    oled_write_P(led_usb_state.num_lock  ? PSTR("ON ") : PSTR("OFF"), false);
    oled_write_P(PSTR(" CAP:"), false);
    oled_write_P(led_usb_state.caps_lock ? PSTR("ON ") : PSTR("OFF"), false);

    oled_set_cursor(0, 2);
    oled_write_P(PSTR("Wetzl Hackpad   "), false);

    oled_set_cursor(0, 3);
    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:  oled_write_P(PSTR("SW16=FN         "), false); break;
        case _FN:      oled_write_P(PSTR("SW4=CUSTOM      "), false); break;
        case _CUSTOM:  oled_write_P(PSTR("SW4=NUMPAD      "), false); break;
        default:       oled_write_P(PSTR("                "), false);
    }

    return false;
}

#endif
