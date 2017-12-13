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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,QUOT,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     RASE, A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,BSPC,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,SPC ,     ENT , K  , M  ,COMM,DOT ,SLSH,RGUI,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LALT,LCTL,SPC ,          ENT,LOWR,RASE
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = KEYMAP(
  //,-------+-------+-------+-------+-------+-------.                            ,-------+-------+-------+-------+-------+-------.
     LALT(KC_PSCREEN),KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                    KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
  //|-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
     _______,_______, UK_AT ,KC_LBRC,KC_RBRC,KC_GRV ,                             KC_NUBS,KC_PGUP,KC_PGDN,KC_HOME,KC_END ,_______,
  //|-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
     _______,KC_LCBR,KC_RCBR,KC_LPRN,KC_RPRN,KC_NUHS,                             KC_QUOT,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,_______,
  //|-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
     _______,KC_EXLM,UK_QUOT,UK_PND ,KC_DLR ,KC_PERC,KC_EQL ,             KC_MINS,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
  //`-------+-------+-------+-------+-------+-------+-------+----/  \----+-------+-------+-------+-------+-------+-------+-------'
                                     _______,_______,KC_EQL ,             KC_MINS,_______,_______  
  //                                `-------+-------+-------'             `------+-------+-------'
  ),

  [_RAISE] = KC_KEYMAP(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,BL_S,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,MPRV,MNXT,VOLU,PGUP,UNDS,               EQL ,HOME,    ,    ,    ,BSLS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,MSTP,MPLY,VOLD,PGDN,MINS,    ,         ,PLUS,END ,    ,    ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,    
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = KEYMAP(
  //,--------+--------+--------+--------+--------+--------.                          ,--------+--------+--------+--------+--------+--------.
      _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                          |--------+--------+--------+--------+--------+--------|
      RESET  , DEBUG  , RGB_HUD, RGB_SAD, RGB_VAD, _______,                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------.        ,--------|--------+--------+--------+--------+--------+--------|
      BL_STEP, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //`--------+--------+--------+----+---+--------+--------+--------/        \--------+--------+--------+---+----+--------+--------+--------'
                                      _______, _______, _______,                  _______, _______, _______
  //                                `--------+--------+--------'                `--------+--------+--------'
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
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
