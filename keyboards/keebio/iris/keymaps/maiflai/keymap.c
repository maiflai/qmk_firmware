#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_uk.h"

extern keymap_config_t keymap_config;

#define _COLEMAK 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_RST RESET
#define KC_BL_S BL_STEP

#define KC_PSCN LALT(KC_PSCREEN)
#define KC_SUPR RCTL(KC_RSFT)
#define KC_LGON LCTL(LGUI(LALT(KC_DEL)))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,RGUI,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LCTL, A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,BSPC,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,    ,         , K  , M  ,COMM,DOT ,SLSH,SUPR,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LGUI,SPC,          ENT,LOWR,RASE
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                            ,-------+-------+-------+-------+-------+-------.
     KC_PSCN,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                       KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
  //|-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
     _______,LCTL(KC_Z), KC_EQL ,KC_LBRC,KC_RBRC,KC_GRV ,                          KC_NUBS,KC_HOME, KC_UP ,KC_END ,KC_PGUP,KC_INS ,
  //|-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
     _______,KC_LCBR,KC_RCBR,KC_LPRN,KC_RPRN,KC_NUHS,                             KC_QUOT,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,_______,
  //|-------+-------+-------+------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
     _______,KC_EXLM,UK_QUOT,UK_PND ,KC_DLR ,KC_PERC,_______,             _______,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
  //`-------+-------+-------+-------+-------+-------+-------+----/  \----+-------+-------+-------+-------+-------+-------+-------'
                                     _______,_______,KC_EQL,             KC_MINS,_______,_______
  //                                `-------+-------+-------'             `------+-------+-------'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,UNDS,    ,    ,                   ,    ,PLUS,    ,    ,LGON,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,MINS,    ,    ,                   ,    ,EQL ,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,MRWD,MPLY,MFFD,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,      ,   ,          ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      RESET  , DEBUG  , _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                      _______, _______, _______,                  _______, _______, _______
  //                                `--------+--------+--------'                `--------+--------+--------'
  )

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Holding both LOWER and RAISE at the same time will turn on ADJUST.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
