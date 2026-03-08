// Copyright 2024 Wetzl
// SPDX-License-Identifier: GPL-2.0-or-later

#include "wetzl_numpad.h"

// -------------------------------------------------------------------------
// OLED Display 128x32
// Zeigt aktuelle Layer-Information und Encoder-Status
// -------------------------------------------------------------------------
#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

bool oled_task_kb(void) {
    // Layer-Name anzeigen
    oled_set_cursor(0, 0);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("NUMPAD          "), false);
            break;
        case 1:
            oled_write_P(PSTR("LAYER 1         "), false);
            break;
        case 2:
            oled_write_P(PSTR("LAYER 2         "), false);
            break;
        default:
            oled_write_P(PSTR("LAYER ?         "), false);
            break;
    }

    // Zeile 2: Num Lock Status
    oled_set_cursor(0, 1);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("NUM:"), false);
    oled_write_P(led_state.num_lock ? PSTR("ON  ") : PSTR("OFF "), false);
    oled_write_P(PSTR("CAPS:"), false);
    oled_write_P(led_state.caps_lock ? PSTR("ON  ") : PSTR("OFF "), false);

    // Zeile 3: Wetzl Numpad Info
    oled_set_cursor(0, 2);
    oled_write_P(PSTR("Wetzl Numpad v1 "), false);

    // Zeile 4: Encoder Taster Info
    oled_set_cursor(0, 3);
    oled_write_P(PSTR("ENC=BTN         "), false);

    return false;
}

#endif // OLED_ENABLE
