#include QMK_KEYBOARD_H
#include "keymap_uk.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define PERMISSIVE_HOLD

#define BASE 0 // default layer
#define FN 1 // FN layer
#define META 2 // META layer

#define ____ KC_TRNS
#define KC_SUPR RCTL(KC_RSFT)
#define KC_ALT LALT(KC_LGUI)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   ____,
        KC_TAB,         KC_Q,         KC_W,   KC_F,   KC_P,   KC_G,   KC_MPLY,
        MO(FN),         KC_A,         KC_R,   KC_S,   KC_T,   KC_D,
        KC_LSFT,        KC_Z,         KC_X,   KC_C,   KC_V,   KC_B,   KC_MUTE,
        ____,           ____,         KC_LGUI,KC_LALT,KC_LCTL,
                                                                      KC_NUHS,  KC_INS,
                                                                                KC_HOME,
                                                            KC_SPC, KC_EQL,     KC_END,
        // right hand
        ____,           KC_6,     KC_7,    KC_8,   KC_9,   KC_0,             KC_RGUI,
        KC_VOLU,           KC_J,     KC_L,    KC_U,   KC_Y,   KC_SCLN,          KC_DEL,
                        KC_H,     KC_N,    KC_E,   KC_I,   KC_O,             KC_BSPC,
        KC_VOLD,           KC_K,     KC_M,    KC_COMM,KC_DOT, KC_SLSH,          KC_SUPR,
	                             MO(META),MO(FN),KC_ALT,____ ,          ____,
        KC_DEL ,KC_RGUI,
        KC_PGUP,
        KC_PGDN,   KC_PLUS, KC_ENT
    ),
[FN] = LAYOUT_ergodox(
       // left hand
       KC_F12, KC_F1,  KC_F2,   KC_F3,   KC_F4,  KC_F5,  ____,
       ____,   ____,  ____,    KC_UNDS, ____,   ____,   ____,
       ____,   ____,  ____,    KC_MINS, ____,   ____,
       ____,   ____,  ____,    ____,    ____,   ____,   ____,
       ____,   ____,  ____,    ____,    ____,
                                       ____,____,
                                               ____,
                               ____,____,____,
       // right hand
       ____, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       ____, ____,    ____,   KC_PLUS, ____,    ____,    ____,
             ____,    ____,   KC_EQL,  ____,    ____,    ____,
       ____, ____,    ____,   ____,    ____,    ____,    ____,
                      ____,   ____,    ____,    ____,     ____,
       ____, ____,
       ____,
       ____, ____, ____
),
[META] = LAYOUT_ergodox(
       LALT(KC_PSCREEN), KC_EXLM,       KC_AT,   KC_HASH, KC_DLR,  KC_PERC,  ____,
       ____,             LCTL(KC_Z),    KC_EQL,   KC_LBRC, KC_RBRC, KC_GRV,   ____,
       ____,             KC_LCBR,       KC_RCBR, KC_LPRN, KC_RPRN, KC_NUHS,
       ____,             KC_EXLM,       KC_AT, UK_PND,  KC_DLR,  KC_PERC, KC_UNDS,
       RESET,             ____,          ____,    ____,    ____,
                                           ____, ____,
                                                 ____,
                                     ____, ____, ____,
    // right hand
       KC_NLCK,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, ____,
       KC_CAPS,  KC_NUBS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_INS,
                 KC_QUOT, KC_LEFT, KC_DOWN, KC_RIGHT,KC_PGDN, ____,
       KC_SLCK,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, ____,
                          ____, ____, ____, ____, ____,
       ____, ____,
       ____,
       ____, ____, ____
),
};

const uint16_t PROGMEM fn_actions[] = {
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
          rgblight_init();
        #endif
        break;
      case FN:
        // ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case META:
        // ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
