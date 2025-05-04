/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers{
    _MAC_BASE,
    _MAC_FN,
    _WIN_BASE,
    _WIN_FN,
    _WIN_GAME
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// TAPDANCE

enum {
    TD_SPOTLIGHT_OPEN,
    TD_MESS_TELEGRAM_OPEN,
    TD_SLACK_OR_JIRA_OPEN,
    TD_XCODE_OR_SUBLIMETEXT_OR_TERMINAL_OPEN,
    TD_MERGE_OR_GITHUB_OPEN
};

void dance_xcode_text_terminal(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code(KC_F17);
            break;
        case 2:
            register_code(KC_LSFT);
            tap_code(KC_F17);
            unregister_code(KC_LSFT);
            break;
        case 3:
            register_code(KC_LCTL);
            tap_code(KC_F17);
            unregister_code(KC_LCTL);
            break;
   }
}

void dance_merge_github(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            // LALT(KC_F15)
            register_code(KC_LALT);
            tap_code(KC_F15);
            unregister_code(KC_LALT);
            break;
        case 2:
            register_code(KC_LALT);
            tap_code(KC_F13);
            unregister_code(KC_LALT);
            break;
   }
}

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_SPOTLIGHT_OPEN] = ACTION_TAP_DANCE_DOUBLE(LGUI(KC_SPACE), LGUI(KC_O)),
    [TD_MESS_TELEGRAM_OPEN] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_F12), KC_F13),
    [TD_SLACK_OR_JIRA_OPEN] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_F13), HYPR(KC_F17)),
    [TD_XCODE_OR_SUBLIMETEXT_OR_TERMINAL_OPEN] = ACTION_TAP_DANCE_FN(dance_xcode_text_terminal),
    [TD_MERGE_OR_GITHUB_OPEN] = ACTION_TAP_DANCE_FN(dance_merge_github),
};

// COMBOS

enum combo_events {
  LBRC_COMBO,
  RBRC_COMBO,
  EQL_COMBO,
  MINS_COMBO,
  ARROW_COMBO
};

const uint16_t PROGMEM lbrc_combo[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM rbrc_combo[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM eql_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM mins_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM arrow_combo[] = {KC_W, KC_F, KC_P, COMBO_END};
combo_t key_combos[] = {
    [LBRC_COMBO] = COMBO_ACTION(lbrc_combo),
    [RBRC_COMBO] = COMBO_ACTION(rbrc_combo),
    [EQL_COMBO] = COMBO(eql_combo, KC_EQL),
    [MINS_COMBO] = COMBO(mins_combo, KC_MINS),
    [ARROW_COMBO] = COMBO_ACTION(arrow_combo),
};

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case LBRC_COMBO:
            if (layer_state_is(_WIN_GAME)) {
                return false;
            }
        case RBRC_COMBO:
            if (layer_state_is(_WIN_GAME)) {
                return false;
            }
        case EQL_COMBO:
            if (layer_state_is(_WIN_GAME)) {
                return false;
            }
        case MINS_COMBO:
            if (layer_state_is(_WIN_GAME)) {
                return false;
            }
        case ARROW_COMBO:
            if (layer_state_is(_WIN_GAME)) {
                return false;
            }
    }
    return true;
}

uint8_t mod_state;
void process_combo_event(uint16_t combo_index, bool pressed) {
    mod_state = get_mods();
    switch(combo_index) {
        case ARROW_COMBO:
            if (pressed) {
                tap_code16(KC_MINS);
                tap_code16(S(KC_DOT));
            }
        break;
        case LBRC_COMBO:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_code16(KC_LBRC);
                    set_mods(mod_state);
                } else {
                    tap_code16(S(KC_LBRC));
                }
            }
        break;
        case RBRC_COMBO:
            if (pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_code16(KC_RBRC);
                    set_mods(mod_state);
                } else {
                    tap_code16(S(KC_RBRC));
                }
            }
        break;
        }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    switch (keycode) {
        case KC_SLSH:
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    tap_code16(KC_SLSH);
                    set_mods(mod_state);
                } else {
                    tap_code16(S(KC_SLSH));
                }
                return false;
            }
            return true;
        break;
    } 
    return true;
}
// LAYERS

#define KC_THGS LALT(KC_F16)
#define KC_TELG KC_F13
#define KC_MESS LSFT(KC_F12)
#define KC_MAIL LSFT(KC_F13)
#define KC_ALFR LGUI(KC_SPACE)
#define KC_SAFR LCTL(KC_F16)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC_BASE] = LAYOUT_ansi_82(
        C(G(KC_Q)),   KC_BRID,  KC_BRIU,  LALT(KC_F7),  XXXXXXX,  DM_REC1, DM_PLY1,  KC_MPRV,     KC_MPLY,  KC_MNXT,  KC_MUTE,    KC_VOLD,  KC_VOLU,  LGUI(KC_BSPC),  HYPR(KC_F19),
        LT(_MAC_FN, KC_GRV),   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,               KC_7,     KC_8,     KC_9,              KC_0, XXXXXXX, XXXXXXX,   KC_BSPC,    LGUI(KC_UP),
        KC_TAB,   KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,               KC_L,     KC_U,     KC_Y,              KC_SCLN,     KC_BSPC,  KC_BSLS,  XXXXXXX,    LGUI(KC_DOWN),
        KC_ESC,   KC_A,     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,               KC_N,     KC_E,     KC_I,              KC_O,        KC_QUOT,            KC_ENT,     LGUI(KC_LEFT),
        SC_LSPO,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,               KC_K,     KC_M,     KC_COMM,           KC_DOT,      KC_SLSH,            SC_RSPC,    KC_UP,
        KC_LCTL,  KC_LOPT,  KC_LGUI,                                KC_SPC,                       KC_LGUI,  KC_RALT,           TD(TD_SPOTLIGHT_OPEN),  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_MAC_FN] = LAYOUT_ansi_82(
        QK_BOOT, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______,
        _______, TD(TD_SLACK_OR_JIRA_OPEN), TD(TD_XCODE_OR_SUBLIMETEXT_OR_TERMINAL_OPEN), TD(TD_MERGE_OR_GITHUB_OPEN), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_SAFR, LSFT(LGUI(KC_LBRC)), LSFT(LGUI(KC_RBRC)), KC_MS_BTN1,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, TD(TD_MESS_TELEGRAM_OPEN), KC_MAIL, KC_THGS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_BSPC, LGUI(KC_DOWN), LGUI(KC_UP), _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                                         KC_ENT,                                _______,  _______,  _______,  _______,  _______,  _______),

    [_WIN_BASE] = LAYOUT_ansi_82(
        LGUI(KC_L),   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_DEL,             KC_MUTE,
        LT(_WIN_FN, KC_GRV),       KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     XXXXXXX, XXXXXXX,   KC_BSPC,            KC_PGUP,
        KC_TAB,       KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_BSPC,    KC_BSLS,  XXXXXXX,            KC_PGDN,
        KC_ESC,       KC_A,     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,              KC_ENT,             KC_HOME,
        SC_LSPO,                KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              SC_RSPC,  KC_UP,
        KC_LGUI,      KC_RALT,  KC_LCTL,                                KC_SPC,                                 KC_RCTL,  KC_RALT, TO(_WIN_GAME),  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_WIN_FN] = LAYOUT_ansi_82(
        QK_BOOT,  KC_BRID,     KC_BRIU,             KC_TASK,       KC_FLXP,      RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,  _______,  _______,
        _______,  _______, LSFT(LGUI(KC_LBRC)), LSFT(LGUI(KC_RBRC)), KC_MS_BTN1, _______,  _______,  _______,  _______, _______, _______, _______, _______,  _______,  _______, _______,  _______, LSFT(LGUI(KC_LBRC)), LSFT(LGUI(KC_LBRC)), KC_MS_BTN1,   _______,  _______,  _______,  _______, _______, _______, _______, _______,  _______,  _______,
        _______,  _______, TD(TD_MESS_TELEGRAM_OPEN), _______, _______,  _______,  _______,  _______,  _______, _______, _______, _______, _______,  _______,
        _______,  KC_TELG, KC_MAIL, KC_THGS, _______,  _______,  _______, _______,  _______,  _______, _______, _______,  _______,
        _______,  _______,     _______,                                          _______,                                _______,  _______,  _______,  _______,  _______,  _______),

    [_WIN_GAME] = LAYOUT_ansi_82(
        LGUI(KC_L),   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_DEL,             KC_MPLY,
        KC_GRV,       KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,       KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_ESC,       KC_A,     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,              KC_ENT,             KC_HOME,
        KC_LSFT,                KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_K,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_O,      KC_RALT,  KC_LCTL,                                KC_SPC,                                 KC_RGUI,  KC_RALT, TO(_WIN_BASE),  KC_LEFT,  KC_DOWN,  KC_RGHT),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_MAC_FN]   = { ENCODER_CCW_CW(KC_BRID, KC_BRIU)},
    [_WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_WIN_FN]   = { ENCODER_CCW_CW(KC_BRID, KC_BRIU)},
    [_WIN_GAME]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
};
#endif // ENCODER_MAP_ENABLE
