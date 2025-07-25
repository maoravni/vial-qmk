// Copyright 2022 Matthew Dews (@matthew-dews)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layer {
    _QWERTY,
    _LOWER,
    _RAISE,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

// I managed to bungle it up by wiring from the bottom, and the three key row is connected *after* the last row.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
                           //KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6  ,                        KC_F7  , KC_F8  , KC_F9  , KC_F10, KC_F11, //10
        /*KC_ESC  , KC_F1  ,*/ KC_2  , KC_3  , KC_4  , KC_5  , KC_PGUP,                        KC_HOME, KC_6   , KC_7   , KC_8  , KC_9  , /*KC_F12 , KC_BSPC, //14*/
        KC_GRV  , KC_1   , KC_W  , KC_E  , KC_R  , KC_T  , KC_PGDN,                        KC_END , KC_Y   , KC_U   , KC_I  , KC_O  , KC_0   , KC_MINS,// 14
        KC_TAB  , KC_Q   , KC_S  , KC_D  , KC_F  , KC_G  ,                                          KC_H   , KC_J   , KC_K   , KC_L  , KC_P,  KC_BSLS, // 12
        KC_LSFT , KC_A   , KC_X  , KC_C  , KC_V  , KC_B  ,                                          KC_N   , KC_M   , KC_COMM, KC_DOT, KC_SCLN, KC_QUOT, //12

        KC_LCTL , KC_Z   , KC_LBRC, KC_RBRC, KC_ENT, /*KC_BSPC,*/ KC_GRV,                      KC_LGUI, /*KC_LALT, */KC_ENT , KC_MINS, KC_EQL, KC_SLSH, KC_LCTL, // 14

                                            KC_SPC , KC_TAB, RAISE,                      LOWER,  KC_DEL, KC_SPC   // 6


    ),

    [_LOWER] = LAYOUT(
                          //_______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, /*_______, _______, _______, _______,*/
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, /*_______, _______,*/
                                            _______, _______, _______,                   _______, _______, _______
        // KC_ESC , KC_F1  , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6  ,                       KC_F7 , KC_F8  , KC_F9 ,KC_F10 ,KC_F11 ,KC_F12 , _______,
        // _______, KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL , _______,
        // _______, _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS, _______,
        // QK_BOOT, _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,                                         KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE, _______,
        // QK_RBT , _______,_______,_______,_______,_______,                                         KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS, _______,
        //                          _______,KC_PSCR,                                                        _______, KC_P0,
        //                                         _______,_______,                         _______,_______,
        //                                         _______,_______,                         _______,_______,
        //                                         _______,_______,                         _______,_______
    ),

    [_RAISE] = LAYOUT(
                          //_______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, /*_______, _______, _______, _______,*/
        _______, _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        QK_BOOT, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        QK_RBT , _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, /*_______, _______,*/
                                            _______, _______, _______,                   _______, _______, _______
    )
};

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}

// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//     if (!is_keyboard_master()) {
//         return OLED_ROTATION_90;  // flips the display 180 degrees if offhand
//     }

//     return rotation;
// }

void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return true;
}

#endif

void keyboard_post_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
}
