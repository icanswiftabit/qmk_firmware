/* Copyright 2019 Josh Johnson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum {
    TD_DOT_COMMA,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_DOT_COMMA] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMMA),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
       KC_MPLY,        KC_MUTE,
    KC_PAST, KC_7,   KC_8,   KC_9,
    KC_PMNS, KC_4,   KC_5,   KC_6,
    KC_PPLS, KC_1,   KC_2,   KC_3,
    KC_PENT,   KC_TAB,KC_0,   TD(TD_DOT_COMMA)
  ),

  [1] = LAYOUT( /* LED Control */
        _______,           _______,
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, _______,
    _______, _______, _______, _______
    ),
};

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left Encoder */
        if (clockwise) {
            tap_code(KC_MEDIA_PREV_TRACK);
        } else {
            tap_code(KC_MEDIA_NEXT_TRACK);
        }
    } else if (index == 1) { /* Right Encoder */
        if (clockwise) {
            tap_code(KC_AUDIO_VOL_DOWN);
        } else {
            tap_code(KC_AUDIO_VOL_UP);
        }
    }
    return true;
}
