#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "color.h"
#include "debug.h"
#include "version.h"

/*
 * MACROS/CONSTANTS
 */

// How long to leave RGB underglow on after swithcing layers
#define LED_SLEEP_TIMEOUT_MS 5000

// Color "Electric Indigo"
// #6100FF
#define HSV_BASE  188, 255, 255
// Color "Harlequin"
// #42FF00
#define HSV_CLEAN 74, 255, 255
// Color "Assassin's Red"
// #f50909
#define HSV_MACRO 0, 245, 245
// Color "Blue Sparkle"
// #0075FF
#define HSV_FNCY  152, 255, 255
// Color "Cadmium Yellow"
// #FFF500
#define HSV_GAME  41, 255, 255

/*
 * ENUMERATIONS/LOOKUP TABLES
 */

enum custom_keycodes {
    CX1 = SAFE_RANGE,
    CX2,
    CX3,
    CXO,
    CXB,
    CXCS,
    CXCF,
    CCCT,
    CCCXTAB,
    MARROW,
    EARROW,
};

enum layers {
    BASE = 0,
    CLEN,
    MCRO,
    FNCY,
    GAME
};

const hsv_t layer_lights[] = {
    {HSV_BASE},
    {HSV_CLEAN},
    {HSV_MACRO},
    {HSV_FNCY},
    {HSV_GAME}
};

/*
 * VARIABLES
 */

deferred_token led_sleep_token = 0;
uint8_t previous_layer = 255;

/*
 * PRIVATE FUNCTIONS
 */

uint32_t led_sleep_callback(uint32_t trigger_time, void *cb_arg) {
    rgblight_disable_noeeprom();

    led_sleep_token = 0;

    return 0;
}

void try_cancel_led_sleep_callback(void) {
    if (led_sleep_token == 0) {
        return;
    }

    cancel_deferred_exec(led_sleep_token);
    led_sleep_token = 0;
}

void reset_led_sleep_callback(void) {
    if (led_sleep_token == 0) {
        led_sleep_token = defer_exec(LED_SLEEP_TIMEOUT_MS, led_sleep_callback, NULL);
    } else {
        extend_deferred_exec(led_sleep_token, LED_SLEEP_TIMEOUT_MS);
    }
}

void on_layer_change(uint8_t new_layer, uint8_t old_layer) {
    hsv_t new_layer_hsv = layer_lights[new_layer];

    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(new_layer_hsv.h, new_layer_hsv.s, new_layer_hsv.v);

    // On the base layer display the base layer color and then disable after
    // LED_SLEEP_TIMEOUT_MS miliseconds.  On any other layer display that
    // layer's color and leave it on.
    if (new_layer == BASE) {
        reset_led_sleep_callback();
    } else {
        try_cancel_led_sleep_callback();
    }
}

/*
 * EVENT HOOKS
 */

// Runs whenever the keyboard initializes
void keyboard_post_init_user(void) {
    ergodox_board_led_off();

    rgblight_mode_noeeprom(1);

    on_layer_change(BASE, BASE);

    if (host_keyboard_led_state().num_lock) {
        ergodox_right_led_1_on();
    }
    if (host_keyboard_led_state().caps_lock) {
        ergodox_right_led_2_on();
    }
    if (host_keyboard_led_state().scroll_lock) {
        ergodox_right_led_3_on();
    }
}

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = get_highest_layer(state);

    if (layer == previous_layer) {
        return state;
    }

    previous_layer = layer;

    on_layer_change(layer, previous_layer);

    return state;
};

// Runs whenever one of the num/caps/scroll lock states are toggled
bool led_update_user(led_t led_state) {
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    if (led_state.num_lock) {
        ergodox_right_led_1_on();
    }
    if (led_state.caps_lock) {
        ergodox_right_led_2_on();
    }
    if (led_state.scroll_lock) {
        ergodox_right_led_3_on();
    }

    return true;
}

// Runs whenever a key event is fired
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            // C-x 1 (delete-other-windows)
            case CX1:
                SEND_STRING(SS_LCTL("x") "1");
                return false;
            // C-x 2 (split-window-below)
            case CX2:
                SEND_STRING(SS_LCTL("x") "2");
                return false;
            // C-x 3 (split-window-right)
            case CX3:
                SEND_STRING(SS_LCTL("x") "3");
                return false;
            // C-x 0 (other-window)
            case CXO:
                SEND_STRING(SS_LCTL("x") "o");
                return false;
            // C-x b (switch-to-buffer)
            case CXB:
                SEND_STRING(SS_LCTL("x") "b");
                return false;
            // C-x C-s (save-buffer)
            case CXCS:
                SEND_STRING(SS_LCTL("xs"));
                return false;
            // C-x C-f (find-file)
            case CXCF:
                SEND_STRING(SS_LCTL("xf"));
                return false;
            // C-c C-t (org-todo)
            case CCCT:
                SEND_STRING(SS_LCTL("ct"));
                return false;
            // C-c C-x tab (org-clock-in)
            case CCCXTAB:
                SEND_STRING(SS_LCTL("cx"));
                SEND_STRING(SS_TAP(X_TAB));
                return false;
            // type "->"
            case MARROW:
                SEND_STRING("->");
                return false;
            // type "=>"
            case EARROW:
                SEND_STRING("=>");
                return false;
        }
    }
    return true;
}

/*
 * LAYER DEFITIONS
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Default Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |   6  |           |   `  |   7  |   8  |   9  |   0  |   -  |   =    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  Nop |           | [    |   Y  |   U  |   I  |   O  |   P  |   ]    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | \      |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | '      |
 * |--------+------+------+------+------+------| ~FNCY|           | ~FNCY|------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtrl| LCtrl| LGui | LAlt | LAlt |                                       |  Lft |  Dn  |  Up  | Rght | RCtrl|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Home | End  |       | Del  | Ins  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | MCRO/|      | PgDn |       | PrScr|      |      |
 *                                 | Space| BkSpc|------|       |------| Enter| Space|
 *                                 |      |      | PgUp |       | Pause|      |      |
 *                                 `--------------------'       `--------------------'
 */
  [BASE] = LAYOUT_ergodox(
    // left hand
      KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,
      KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,    KC_NO,
     KC_BSLS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
     KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B, MO(FNCY),
     KC_LCTL,  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LALT,
                                                       KC_HOME,   KC_END,
                                                                 KC_PGUP,
                                    LT(MCRO, KC_SPC), KC_BSPC,  KC_PGDN,

    // right hand
      KC_GRV,     KC_7,     KC_8,     KC_9,     KC_0,  KC_MINS,   KC_EQL,
     KC_LBRC,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_RBRC,
                  KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT,
    MO(FNCY),     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_RSFT,
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
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | BASE |           |  [   |   Y  |   U  |   I  |   O  |   P  |   ]    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | \      |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | '      |
 * |--------+------+------+------+------+------| ~FNCY|           | ~FNCY|------+------+------+------+------+--------|
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
  [CLEN] = LAYOUT_ergodox(
    // left hand
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, TO(BASE),
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, MO(FNCY),
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
 * |  Lock  | C-x 1| C-x 2| C-x 3|  Nop |  Nop |  Nop |           |  Nop |  Nop |  Nop | RecM1| StopM|  ->  |   =>   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |C-cC-xTb|  Nop |  Nop |PlayM1|  Nop |C-cC-t|  Nop |           |  M-{ |  Nop |  Nop | RecM2| C-x,o|  Nop |  M-}   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  Nop   |  Nop |C-xC-s|PlayM2|C-xC-f|  C-g |------|           |------|  Nop |  Nop |  Nop |  Nop |  Nop |  Nop   |
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
     CCCXTAB,    KC_NO,    KC_NO,  DM_PLY1,    KC_NO,     CCCT,    KC_NO,
       KC_NO,    KC_NO,     CXCS,  DM_PLY2,     CXCF,  C(KC_G),
       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,      CXB,    KC_NO,
       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                                                         KC_NO,    KC_NO,
                                                                   KC_NO,
                                             KC_TRNS,    KC_NO,    KC_NO,
    // right hand
       KC_NO,    KC_NO,    KC_NO,  DM_REC1,  DM_RSTP,   MARROW,   EARROW,
  A(KC_LCBR),    KC_NO,    KC_NO,  DM_REC2,      CXO,    KC_NO,A(KC_RCBR),
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
 * |  BASE  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  Nop   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TRNS  |  Nop |MousUp|  Nop |  Nop |  Nop | GAME |           | CLEN |  Nop |   7  |   8  |   9  |  NUM |  Nop   |
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
[FNCY] = LAYOUT_ergodox(
  // left hand
    TO(BASE),    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,
     KC_TRNS,    KC_NO,  KC_MS_U,    KC_NO,    KC_NO,    KC_NO, TO(GAME),
       KC_NO,  KC_MS_L,  KC_MS_D,  KC_MS_R,    KC_NO,    KC_NO,
     KC_TRNS,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                       KC_BTN2,    KC_NO,
                                                                 KC_TRNS,
                                             KC_BTN1,  KC_TRNS,  KC_TRNS,
  // right hand
       KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,    KC_NO,
    TO(CLEN),    KC_NO,    KC_P7,    KC_P8,    KC_P9,   KC_NUM,    KC_NO,
                 KC_NO,    KC_P4,    KC_P5,    KC_P6,    KC_NO,    KC_NO,
     KC_TRNS,    KC_NO,    KC_P1,    KC_P2,    KC_P3,  KC_TRNS,    KC_NO,
                           KC_P0,    KC_P0,   KC_DOT,  KC_BTN1,  KC_BTN2,
     KC_MUTE,    KC_NO,
     KC_VOLU,
     KC_VOLD,  KC_TRNS,  KC_TRNS
),
/* Keymap 4: Gaming Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc    |   1  |   2  |   3  |   4  |   5  |   6  |           |  Nop |  Nop |  Nop |  Nop |  Nop |  Nop |  Nop   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | BASE |           |  Nop |  Nop |  Nop |  Up  |  Nop |  Nop |  Nop   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | \      |   A  |   S  |   D  |   F  |   G  |------|           |------|  Nop |  Lft |  Dn  | Rght |  Nop |  Nop   |
 * |--------+------+------+------+------+------|  Nop |           |  Nop |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |  Nop |  Nop |  Nop |  Nop |  Nop |  Nop   |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtrl| LCtrl| LGui | LAlt | LAlt |                                       |  Alt |  Nop |  Nop |  Nop | Ctrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Home | End  |       | Mute |  Nop |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | PgDn |       | VolUp|      |      |
 *                                 | Space| BkSpc|------|       |------| Enter| Space|
 *                                 |      |      | PgUp |       | VolDn|      |      |
 *                                 `--------------------'       `--------------------'
 */
[GAME] = LAYOUT_ergodox(
  // left hand
      KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,
      KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T, TO(BASE),
     KC_BSLS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,
     KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,    KC_NO,
     KC_LCTL,  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LALT,
                                                       KC_HOME,   KC_END,
                                                                 KC_PGUP,
                                              KC_SPC,  KC_BSPC,  KC_PGDN,
  // right hand
       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
       KC_NO,    KC_NO,    KC_NO,    KC_UP,    KC_NO,    KC_NO,    KC_NO,
                 KC_NO,  KC_LEFT,  KC_DOWN,  KC_RGHT,    KC_NO,    KC_NO,
       KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
                         KC_RALT,    KC_NO,    KC_NO,    KC_NO,  KC_RCTL,
     KC_MUTE,    KC_NO,
     KC_VOLU,
     KC_VOLD,   KC_ENT,   KC_SPC
),
};

