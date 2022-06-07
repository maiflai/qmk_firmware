#include "iris.h"
#include "keymap_uk.h"

extern keymap_config_t keymap_config;

#define _COLEMAK 0
#define _LOWER 1
#define _RAISE 2

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  RAISE,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define KC_PSCN LALT(KC_PSCREEN)
#define SUPER RCTL(KC_RSFT)
#define KC_LGON LCTL(LGUI(LALT(KC_DEL)))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT(
  //,----+----+----+----+----+----.                                 ,----+----+----+----+----+----.
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_RGUI,
  //|----+----+----+----+----+----|                                 |----+----+----+----+----+----|
     KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_G  ,                KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_DEL ,
  //|----+----+----+----+----+----|                                 |----+----+----+----+----+----|
     KC_LGUI, KC_A  , KC_R  , KC_S  , KC_T  , KC_D  ,                KC_H  , KC_N  , KC_E  , KC_I  , KC_O  ,KC_BSPC,
  //|----+----+----+----+----+----+----.                            ,----|----+----+----+----+----+----|
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  , KC_   ,  KC_       , KC_K  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,SUPER,
  //`----+----+----+--+-+----+----+----/    i                       \----+----+----+----+----+----+----'
                       KC_LALT,KC_LCTL,KC_SPC,                       KC_ENT,LOWER,RAISE
  //                  `----+----+----'                                `----+----+----'
  ),

  [_LOWER] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                            ,-------+-------+-------+-------+-------+-------.
     KC_PSCN,KC_EXLM,UK_DQUO,UK_PND,KC_DLR ,KC_PERC,                       KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
  //|-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
     _______,LCTL(KC_Z), KC_EQL ,KC_LBRC,KC_RBRC,KC_NUHS ,                        KC_GRV ,KC_HOME, KC_UP ,KC_END ,KC_PGUP,KC_INS ,
  //|-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
     _______,KC_LCBR,KC_RCBR,KC_LPRN,KC_RPRN,KC_NUBS,                             KC_QUOT,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,_______,
  //|-------+-------+-------+------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
     _______,KC_EXLM,UK_DQUO,UK_PND,KC_DLR ,KC_PERC,_______,             _______,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
  //`-------+-------+-------+-------+-------+-------+-------+----/  \----+-------+-------+-------+-------+-------+-------+-------'
                                     _______,_______,KC_EQL,             KC_MINS,_______,_______
  //                                `-------+-------+-------'             `------+-------+-------'
  ),

  [_RAISE] = LAYOUT(
  //,----+----+----+----+----+----.                                              ,----+----+----+----+----+----.
     KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
  //|----+----+----+----+----+----|                                              |----+----+----+----+----+----|
     KC_ , KC_ , KC_  ,KC_UNDS, KC_  , KC_  ,               KC_   , KC_  ,KC_PLUS, KC_  , KC_  ,KC_LGON,
  //|----+----+----+----+----+----|                                              |----+----+----+----+----+----|
     KC_   , KC_  , KC_  ,KC_MINS,KC_   , KC_  ,               KC_MUTE, KC_  ,KC_EQL , KC_  ,KC_VOLU,KC_   ,
  //|----+----+----+----+----+----+----.                                    ,----|----+----+----+----+----+----|
     KC_   , KC_  , KC_  , KC_  , KC_  ,  KC_ , KC_  , KC_       , KC_  ,KC_MRWD,KC_MPLY,KC_MFFD,KC_VOLD,KC_   ,
  //`----+----+----+--+-+----+----+----/                                    \----+----+----+----+----+----+----'
                       KC_   ,   KC_  ,KC_  ,       KC_  , KC_  , KC_
  //                  `----+----+----'                                        `----+----+----'
  ),


};

