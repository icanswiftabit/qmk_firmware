/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

enum layers {
  _MAC_BASE,
  _MAC_FN,
  _WIN_BASE,
  _WIN_FN,
  _WIN_GAME
};

enum {
  TD_MESS_TELEGRAM_OPEN,
  TD_SLACK_OR_JIRA_OPEN,
  TD_XCODE_OR_SUBLIMETEXT_OR_TERMINAL_OPEN,
  TD_MERGE_OR_GITHUB_OPEN
};

bool rgb_matrix_indicators_user(void) {
  if (layer_state_is(_WIN_GAME)) {
      rgb_matrix_set_color(34, 0, 255, 0); // Esc
      rgb_matrix_set_color(35, 0, 255, 0); // Tab
      rgb_matrix_set_color(38, 0, 255, 0); // W
      rgb_matrix_set_color(51, 0, 255, 0); // A
      rgb_matrix_set_color(52, 0, 255, 0); // S
      rgb_matrix_set_color(53, 0, 255, 0); // D
      rgb_matrix_set_color(54, 0, 255, 0); // ;
      rgb_matrix_set_color(64, 0, 255, 0); // X
      rgb_matrix_set_color(77, 0, 255, 0); // Space
      rgb_matrix_set_color(78, 0, 255, 0); // L
      rgb_matrix_set_color(79, 0, 255, 0); // M
  } else {
      rgb_matrix_set_color(34, 0, 0, 0); // Esc
      rgb_matrix_set_color(35, 0, 0, 0); // Tab
      rgb_matrix_set_color(38, 0, 0, 0); // W
      rgb_matrix_set_color(51, 0, 0, 0); // A
      rgb_matrix_set_color(52, 0, 0, 0); // S
      rgb_matrix_set_color(53, 0, 0, 0); // D
      rgb_matrix_set_color(54, 0, 0, 0); // ;
      rgb_matrix_set_color(64, 0, 0, 0); // X
      rgb_matrix_set_color(77, 0, 0, 0); // Space
      rgb_matrix_set_color(78, 0, 0, 0); // L
      rgb_matrix_set_color(79, 0, 0, 0); // M
  }
  return false;
}

void dance_xcode_text_terminal(tap_dance_state_t * state, void * user_data) {
  switch (state -> count) {
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

void dance_merge_github(tap_dance_state_t * state, void * user_data) {
  switch (state -> count) {
  case 1:
    register_code(KC_LALT);
    register_code(KC_LCMD);
    tap_code(KC_F16);
    unregister_code(KC_LCMD);
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
  [TD_MESS_TELEGRAM_OPEN] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_F12), KC_F13),
  [TD_SLACK_OR_JIRA_OPEN] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_F13), HYPR(KC_F17)),
  [TD_XCODE_OR_SUBLIMETEXT_OR_TERMINAL_OPEN] = ACTION_TAP_DANCE_FN(dance_xcode_text_terminal),
  [TD_MERGE_OR_GITHUB_OPEN] = ACTION_TAP_DANCE_FN(dance_merge_github),
};

#define KC_TASK LGUI(KC_TAB)
#define KC_SNAP SCMD(KC_5)
#define KC_FLXP LGUI(KC_E)

#define KC_THGS LALT(KC_F16)
#define KC_TELG KC_F13
#define KC_MESS LSFT(KC_F12)
#define KC_MAIL LSFT(KC_F13)
#define KC_ALFR LGUI(KC_SPACE)
#define KC_SAFR LCTL(KC_F16)

enum combo_events {
  LBRC_COMBO,
  RBRC_COMBO,
  EQL_COMBO,
  MINS_COMBO,
  ARROW_COMBO,
  SPOTLIGH_COMBO
};

const uint16_t PROGMEM lbrc_combo[] = {
  KC_S,
  KC_T,
  COMBO_END
};
const uint16_t PROGMEM rbrc_combo[] = {
  KC_N,
  KC_E,
  COMBO_END
};
const uint16_t PROGMEM eql_combo[] = {
  KC_U,
  KC_Y,
  COMBO_END
};
const uint16_t PROGMEM mins_combo[] = {
  KC_W,
  KC_F,
  COMBO_END
};
const uint16_t PROGMEM arrow_combo[] = {
  KC_W,
  KC_F,
  KC_P,
  COMBO_END
};
const uint16_t PROGMEM spotlight_combo[] = {
  KC_RALT,
  RGUI(RSFT(KC_P)),
  COMBO_END
};
combo_t key_combos[] = {
  [LBRC_COMBO] = COMBO_ACTION(lbrc_combo),
  [RBRC_COMBO] = COMBO_ACTION(rbrc_combo),
  [EQL_COMBO] = COMBO(eql_combo, KC_EQL),
  [MINS_COMBO] = COMBO(mins_combo, KC_MINS),
  [ARROW_COMBO] = COMBO_ACTION(arrow_combo),
  [SPOTLIGH_COMBO] = COMBO(spotlight_combo, RGUI(KC_SPACE))
};

bool combo_should_trigger(uint16_t combo_index, combo_t * combo, uint16_t keycode, keyrecord_t * record) {
  if (get_highest_layer(layer_state|default_layer_state) == _WIN_GAME) {
    return false;
  }
  return true;
}

uint8_t mod_state;
void process_combo_event(uint16_t combo_index, bool pressed) {
  mod_state = get_mods();
  switch (combo_index) {
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

bool process_record_user(uint16_t keycode, keyrecord_t * record) {
  mod_state = get_mods();
  switch (keycode) {
  case KC_SLSH:
    if (record -> event.pressed) {
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC_BASE] = LAYOUT_75_ansi(
        C(G(KC_Q)),           KC_BRID,  KC_BRIU,  LALT(KC_F7),        XXXXXXX,  DM_REC1,  DM_PLY1,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_SNAP,      LGUI(KC_BSPC),   HYPR(KC_F19),
        LT(_MAC_FN, KC_GRV),  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     XXXXXXX,  XXXXXXX,  KC_BSPC,  LGUI(KC_UP),
        KC_TAB,               KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,               KC_SCLN,  KC_BSPC,  KC_BSLS,  XXXXXXX,                       LGUI(KC_DOWN),
        KC_ESC,               KC_A,     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,     KC_N,     KC_E,     KC_I,               KC_O,     KC_QUOT,  KC_ENT,                                  LGUI(KC_LEFT),
        SC_LSPO,                        KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_K,     KC_M,     KC_COMM,            KC_DOT,   KC_SLSH,  SC_RSPC,  KC_UP,                         LGUI(KC_RGHT),
        KC_LCTL,  KC_LOPT, KC_LCMD,                               KC_SPC,                                 KC_RCMD, KC_RALT, RGUI(LSFT(KC_P)),  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_MAC_FN] = LAYOUT_75_ansi(
        QK_BOOT,  KC_F1,                        KC_F2,                                         KC_F3,                        KC_F4,               KC_F5,                 KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______, RGB_TOG,
        _______,  TD(TD_SLACK_OR_JIRA_OPEN),    TD(TD_XCODE_OR_SUBLIMETEXT_OR_TERMINAL_OPEN),  TD(TD_MERGE_OR_GITHUB_OPEN),  LCTL(LOPT(KC_LEFT)), LCTL(LOPT(KC_RGHT)) ,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, RGB_MOD,
        RM_TOGG,  KC_SAFR, LSFT(LCTL(KC_TAB)),  LCTL(KC_TAB),                                  KC_MS_BTN1,                   _______,             _______,               _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_RMOD,
        _______,  TD(TD_MESS_TELEGRAM_OPEN),    KC_MAIL,                                       KC_THGS,                      _______,             _______,               _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  KC_BSPC,                      LGUI(KC_DOWN),                                 LGUI(KC_UP),                  _______,             _______,               _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,                                KC_ENT,                                _______,  _______,   _______,  _______,  _______,  _______),

    [_WIN_BASE] = LAYOUT_75_ansi(
        LGUI(KC_L),           KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,  KC_F11,    KC_F12,   KC_PSCR,  KC_DEL,   HYPR(KC_F19),
        LT(_WIN_FN, KC_GRV),  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_MINS,   KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,               KC_Q,     KC_W,     KC_F,     KC_P,     KC_G,     KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN, KC_BSPC,   KC_BSLS,  XXXXXXX,  KC_PGDN,
        KC_ESC,               KC_A,     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,     KC_N,     KC_E,     KC_I,     KC_O,    KC_QUOT,   KC_ENT,             KC_HOME,
        SC_LSPO,              KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_K,     KC_M,     KC_COMM,            KC_DOT,  KC_SLSH,   SC_RSPC,  KC_UP,    KC_END,
        KC_LGUI,  KC_RALT,  KC_LCTL,                                KC_SPC,                                 KC_RCMD, KC_RALT, TG(_WIN_GAME),  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_WIN_FN] = LAYOUT_75_ansi(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  _______,  _______,  RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______, RGB_MOD,
        _______,  _______,  LSFT(LCTL(KC_TAB)), LCTL(KC_TAB),  KC_MS_BTN1,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______, _______, RGB_RMOD,
        _______,  _______, KC_MESS, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,  _______,
        _______,  KC_TELG, KC_MAIL, KC_THGS,  _______,  _______,  _______, _______,  _______,  _______, _______, _______,  _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______, XXXXXXX,  _______,  _______,  _______),

    [_WIN_GAME] = LAYOUT_75_ansi(
      LGUI(KC_L),   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   HYPR(KC_F19),
      KC_GRV,       KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_VOLU,
      KC_P,         KC_Y,     KC_U,     KC_ESC,   KC_TAB,   KC_O,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_VOLD,
      KC_H,         KC_J,     KC_K,     KC_L,     KC_I,     KC_SCLN,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_QUOT,            KC_ENT,             KC_MUTE,
      KC_LSFT,                KC_N,     KC_M,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
      KC_LGUI,  KC_RALT,  KC_LCTL,                                KC_SPC,                                              KC_L,      KC_M,  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT),
};
