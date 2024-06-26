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
#include <print.h>

static uint16_t win_space_timer; // グローバル変数として定義


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    WIN_MAC_CTRL,
    WIN_MAC_COMMAND,
    MOUSE,
    MOUSE_SCROLL,
};

enum custom_keycodes {
    MAC_L_CTRL = SAFE_RANGE,
    MAC_L_COMMAND,
    EMACS_CTRL_K,
    WIN_SPACE = SAFE_RANGE,    // 英語キーボード切り替え用
    WIN_SPACE_JP, // 日本語キーボード切り替え用
    SCROLL_LAYER,
    CUSTOM_KC_LBRC, // カスタム[
    LOWER,
    RAISE,
    // for mytap_t
    LT_ESC,
    RT_SPC,
    CT_DEL,
    // ST_SPC,
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_NO,    KC_NO,    RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  KC_DEL,             KC_INS,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_82(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_ansi_82(
        KC_ESC,            KC_F1,    KC_F2,                   KC_F3,            KC_LWIN,  KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,     KC_F12,   KC_DEL,             KC_INS,
        KC_GRV,            KC_1,     KC_2,                    KC_3,             KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,    KC_0,     KC_MINS,    KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,            KC_Q,     KC_W,                    KC_E,             KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,    KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS,            KC_PGDN,
        MO(WIN_MAC_CTRL),  KC_A,     LT(MOUSE_SCROLL, KC_S),  LT(MOUSE, KC_D),  KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,    KC_SCLN,  KC_QUOT,              KC_ENT,             KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,                    KC_C,             KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,           KC_LALT,  WIN_SPACE,                                                       KC_SPC,                                KC_LCTL,  MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_MAC_CTRL] = LAYOUT_ansi_82(
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,     _______,     _______,     _______,               _______,
        _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,     _______,     _______,     _______,               _______,
        C(KC_TAB),   C(KC_Q),  C(KC_W),  C(KC_E),  C(KC_R),  C(KC_T),  C(KC_Y),  C(KC_U),  C(KC_I),  C(KC_O),     C(KC_P),     C(KC_LBRC),  C(KC_RBRC),  C(KC_BSLS),            _______,
        _______,     C(KC_A),  C(KC_S),  C(KC_D),   C(KC_F),  C(KC_G),  KC_BSPC,  KC_PENT,  C(KC_K),  C(KC_L),     C(KC_SCLN),  KC_F10,                   C(KC_ENT),             _______,
        C(KC_LSFT),            C(KC_Z),  C(KC_X),  C(KC_C),  C(KC_V),  C(KC_B),  C(KC_N),  C(KC_M),  C(KC_COMM),  C(KC_DOT),   C(KC_SLSH),               C(KC_RSFT),  _______,
        _______,     _______,  _______,                                _______,                                   _______,     _______,     _______,     _______,     _______,     _______
    ),

    [WIN_MAC_COMMAND] = LAYOUT_ansi_82(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

    [WIN_FN] = LAYOUT_ansi_82(
        QK_BOOT,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,            _______,
        DB_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,  _______,  _______,  _______
        ),

    [MOUSE] = LAYOUT_ansi_82(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,     KC_MPRV,     KC_MPLY,  KC_MNXT,      KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            _______,
        _______,  KC_BTN1,  KC_BTN2,  _______,  _______,  _______,  _______,     _______,     _______,  _______,      _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,     _______,     _______,  _______,      KC_UP,    _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  KC_ACL2,  KC_ACL0,  KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_UP, KC_MS_RIGHT,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  KC_BTN1,     KC_BTN2,     _______,  _______,      _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                            _______,      _______,  _______,  _______,  _______,  _______
        ),

    [MOUSE_SCROLL] = LAYOUT_ansi_82(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  KC_ACL2,  KC_ACL0,  _______,  KC_WH_D,  KC_WH_U,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                      _______,                      _______,  _______,  _______,  _______,  _______,  _______
        ),
};


/* デバッグ用 */
void keyboard_post_init_user(void) {
  // 希望する動作に合わせて値をカスタマイズします
//   debug_enable=true;
//   debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
        uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    #endif 
    switch (keycode) {
        case EMACS_CTRL_K:
            if (record->event.pressed) {
                 // Ctrl + Shift を押す
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                // End を押して放す
                tap_code(KC_END);
                // Ctrl + Shift を放す
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
                // Ctrl + X を押して、選択範囲をカット
                register_code(KC_LCTL);
                tap_code(KC_X);
                unregister_code(KC_LCTL);
            }
            return false;
            break;
        case WIN_SPACE:
            if (record->event.pressed) {
                // キーが押されたときの処理
                win_space_timer = timer_read(); // タイマー開始
                layer_on(WIN_MAC_CTRL);
            } else {
                // キーが離されたときの処理
                layer_off(WIN_MAC_CTRL);
                if (timer_elapsed(win_space_timer) < TAPPING_TERM) {
                    // タップされた場合の処理
                    SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_SPACE) SS_UP(X_LGUI)); // Win + Space
                } else {
                    // 長押しの場合の処理（ここでは何もしない）
                    // 通常、Ctrl の動作は別途 MT(MOD_LCTL, KC_???) などでマップする必要がある
                }
            }
            return false; // これ以上の処理をしない
            break;
        case WIN_SPACE_JP:
            if (record->event.pressed) {
                register_code(KC_GRV);
                unregister_code(KC_GRV);
            }
            return false;
            break;
        case CUSTOM_KC_LBRC:
            if (record->event.pressed) {
                register_code(KC_ESC);
                unregister_code(KC_ESC);
                register_code(KC_LCTL);
                register_code(KC_LBRC);
                unregister_code(KC_LBRC);
                unregister_code(KC_LCTL);
            }
            return false;
            break;

    }

    return true;
}
