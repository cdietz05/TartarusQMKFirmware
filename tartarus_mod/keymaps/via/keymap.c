/*
Copyright 2026 Chris Dietz
GPL-2.0-or-later
*/

#include QMK_KEYBOARD_H

// Encoder Logic
bool encoder_update_user(uint8_t index, bool clockwise) 
{
    if (index == 0) 
    {
        if (clockwise) 
        {
            tap_code(MS_WHLD);
        } 
        else 
        {
            tap_code(MS_WHLU);
        }
    }
    return false;
}

// Default Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    MO(3),  KC_B, KC_SPC,
        KC_W,    KC_A,    KC_S,    KC_D
    ),
    [1] = LAYOUT(
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    ),
    [2] = LAYOUT(
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
    [3] = LAYOUT(
        QK_BOOT,  KC_F24,    KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS
    )
};