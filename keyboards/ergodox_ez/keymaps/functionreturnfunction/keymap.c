#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

enum custom_keycodes {
  CX1 = SAFE_RANGE,
  CX2,
  CX3,
  CXO,
  CXB,
  CXCS,
  CXCF,
  HSHRKT,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case CX1:
        SEND_STRING(SS_LCTRL("x") "1");
        return false;
      case CX2:
        SEND_STRING(SS_LCTRL("x") "2");
        return false;
      case CX3:
        SEND_STRING(SS_LCTRL("x") "3");
        return false;
      case CXO:
        SEND_STRING(SS_LCTRL("x") "o");
        return false;
      case CXB:
        SEND_STRING(SS_LCTRL("x") "b");
        return false;
      case CXCS:
        SEND_STRING(SS_LCTRL("xs"));
        return false;
      case CXCF:
        SEND_STRING(SS_LCTRL("xf"));
        return false;
      case HSHRKT:
        SEND_STRING("=>");
        return false;
    }
  }
  return true;
}

enum layers {
  BASE = 0,
  CLEAN,
  MCRO,
  FUNCY,
  GAMIN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Default Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |   6  |           |   `  |   7  |   8  |   9  |   0  |   -  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  Nop |           | [    |   Y  |   U  |   I  |   O  |   P  |   ]    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | \      |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | '      |
 * |--------+------+------+------+------+------| ~L3  |           | ~L3  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtrl| LCtrl| LGui | LAlt | LAlt |                                       |  Lft |  Dn  |  Up  | Rght | RCtrl|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Home | End  |       | Del  | Ins  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | L2/  |      | PgDn |       | PrScr|      |      |
 *                                 | Space| BkSpc|------|       |------| Enter| Space|
 *                                 |      |      | PgUp |       | Pause|      |      |
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
  [BASE] = LAYOUT_ergodox(
    // left hand
      KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,
      KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,    KC_NO,
     KC_BSLS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
     KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,MO(FUNCY),
     KC_LCTL,  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LALT,
                                                       KC_HOME,   KC_END,
                                                                 KC_PGUP,
                                    LT(MCRO, KC_SPC), KC_BSPC,  KC_PGDN,

    // right hand
      KC_GRV,     KC_7,     KC_8,     KC_9,     KC_0,  KC_MINS,   KC_EQL,
     KC_LBRC,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_RBRC,
                  KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT,
   MO(FUNCY),     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_RSFT,
                         KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,  KC_RCTL,

      KC_DEL,   KC_INS,
     KC_PSCR,
     KC_PAUS,   KC_ENT,   KC_SPC
                  ),
/* Keymap 1: Clean Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |   6  |           |   `  |   7  |   8  |   9  |   0  |   -  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L0  |           |  [   |   Y  |   U  |   I  |   O  |   P  |   ]    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | \      |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | '      |
 * |--------+------+------+------+------+------|  ~L3 |           |  ~L3 |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtrl| LCtrl| LGui | LAlt | LAlt |                                       |  Lft |  Dn  |  Up  | Rght | RAlt |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Home | End  |       | Del  | Ins  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | PgDn |       | PrScr|      |      |
 *                                 | Space| BkSpc|------|       |------| Enter| Space|
 *                                 |      |      | PgUp |       | Pause|      |      |
 *                                 `--------------------'       `--------------------'
 */
  [CLEAN] = LAYOUT_ergodox(
    // left hand
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, TO(BASE),
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,MO(FUNCY),
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                       KC_TRNS,  KC_TRNS,
                                                                 KC_TRNS,
                                               KC_SPC, KC_TRNS,  KC_TRNS,
       // right hand
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
               KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                         KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,

     KC_TRNS,  KC_TRNS,
     KC_TRNS,
     KC_TRNS,  KC_TRNS, KC_TRNS
),
/* Keymap 2: Macro Keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  Lock  | C-x 1| C-x 2| C-x 3|  Nop |  Nop |  Nop |           |  Nop |  Nop |  Nop |  Nop |  Nop |  Nop | HshRckt|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  Nop   |  Nop |  Nop |  Nop |  Nop |  Nop |  Nop |           |  M-{ |  Nop |  Nop |  Nop | C-x,o|  Nop |  M-}   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Nop   |  Nop |C-xC-s|  Nop |C-xC-f|  C-g |------|           |------|  Nop |  Nop |  Nop |  Nop |  Nop |  Nop   |
 * |--------+------+------+------+------+------|  Nop |           |  Nop |------+------+------+------+------+--------|
 * |  Nop   |  Nop |  Nop |  Nop |  Nop | C-x,b|      |           |      |  Nop |  Nop |  M-< |  M-> |  Nop |  Nop   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  Nop |  Nop |  Nop |  Nop |  Nop |                                       |  Nop |  Nop |  Nop |  Nop |  Nop |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  Nop |  Nop |       |  Nop |  Nop |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  Nop |       |  Nop |      |      |
 *                                 | TRNS |  Nop |------|       |------|  Nop | Nop  |
 *                                 |      |      |  Nop |       |  Nop |      |      |
 *                                 `--------------------'       `--------------------'
 */
  [MCRO] = LAYOUT_ergodox(
    // left hand
     G(KC_L),      CX1,      CX2,      CX3,    KC_NO,    KC_NO,    KC_NO,
       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
       KC_NO,    KC_NO,     CXCS,    KC_NO,     CXCF,  C(KC_G),
       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      CXB,    KC_NO,
       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                                         KC_NO,    KC_NO,
                                                                   KC_NO,
                                             KC_TRNS,    KC_NO,    KC_NO,
    // right hand
       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   HSHRKT,
  A(KC_LCBR),    KC_NO,    KC_NO,    KC_NO,      CXO,    KC_NO,A(KC_RCBR),
                 KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
       KC_NO,    KC_NO,    KC_NO, A(KC_LT), A(KC_GT),    KC_NO,    KC_NO,
                           KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
       KC_NO,    KC_NO,
       KC_NO,
       KC_NO,    KC_NO,    KC_NO
),
/* Keymap 3: Fn keys, number pad, mouse controls
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  L0    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  Nop   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TRNS  |  Nop |MousUp|  Nop |  Nop |  Nop |  L4  |           |  L1  |  Nop |   7  |   8  |   9  |  NUM |  Nop   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Nop   |MousLf|MousDn|MousRt|  Nop |  Nop |------|           |------|  Nop |   4  |   5  |   6  |  Nop |  Nop   |
 * |--------+------+------+------+------+------| TRNS |           | TRNS |------+------+------+------+------+--------|
 * |  TRNS  |  Nop |  Nop |  Nop |  Nop |  Nop |      |           |      |  Nop |   1  |   2  |   3  | TRNS |  Nop   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | TRNS | TRNS | TRNS | TRNS | TRNS |                                       |   0  |   0  |   .  | Btn1 | Btn2 |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Btn2 |  Nop |       | Mute |  Nop |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | TRNS |       | VolUp|      |      |
 *                                 | Btn1 | TRNS |------|       |------| TRNS | TRNS |
 *                                 |      |      | TRNS |       | VolDn|      |      |
 *                                 `--------------------'       `--------------------'
 */
[FUNCY] = LAYOUT_ergodox(
  // left hand
    TO(BASE),    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
     KC_TRNS,    KC_NO,  KC_MS_U,    KC_NO,    KC_NO,    KC_NO,TO(GAMIN),
       KC_NO,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_TRNS,  KC_TRNS,
     KC_TRNS,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                          KC_BTN2, KC_TRNS,
                                                                   KC_TRNS,
                                                 KC_BTN1, KC_TRNS, KC_TRNS,
  // right hand
       KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,    KC_NO,
   TO(CLEAN),    KC_NO,    KC_P7,    KC_P8,    KC_P9,  KC_NLCK,    KC_NO,
                 KC_NO,    KC_P4,    KC_P5,    KC_P6,    KC_NO,    KC_NO,
     KC_TRNS,    KC_NO,    KC_P1,    KC_P2,    KC_P3,  KC_TRNS,    KC_NO,
                           KC_P0,    KC_P0,   KC_DOT,  KC_BTN1,  KC_BTN2,
     KC_MUTE,    KC_NO,
     KC_VOLU,
     KC_VOLD,  KC_TRNS,  KC_TRNS
),
),
/* [DEV] = LAYOUT_ergodox( */
/*        // left hand */
/*        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, */
/*        KC_TRNS, KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_TRNS, */
/*        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, */
/*        KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS, */
/*        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, */
/*                                            KC_TRNS, KC_TRNS, */
/*                                                     KC_TRNS, */
/*                                   KC_TRNS, KC_TRNS, KC_TRNS, */
/*        // right hand */
/*        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, */
/*        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, */
/*                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, */
/*        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, */
/*                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, */
/*        KC_TRNS, KC_TRNS, */
/*        KC_TRNS, */
/*        KC_TRNS, KC_TRNS, KC_TRNS */
/* ), */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case CLEAN:
            // Binary 1 represented by the leds
            // --*
            ergodox_right_led_3_on();
            break;
        case MCRO:
            // Binary 2 represented by the leds
            // -*-
            ergodox_right_led_2_on();
            break;
        case FUNCY:
            // Binary 3 represented by the leds
            // -**
            ergodox_right_led_3_on();
            ergodox_right_led_2_on();
            break;
        case GAMIN:
            // Binary 4 represented by the leds
            // *--
            ergodox_right_led_1_on();
            break;
        default:
            // none
            break;
    }
};
