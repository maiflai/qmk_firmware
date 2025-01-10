#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "keymap_uk.h"

#include "lufa.h"
#include "split_util.h"
#include "ssd1306.h"
#include "drivers/sensors/pimoroni_trackball.h"
#include "pointing_device.h"


enum layer_number {
  _COLEMAK= 0,
  _LOWER,
  _RAISE,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR MO(_LOWER)
#define KC_RASE MO(_RAISE)

#define KC_PSCN LALT(KC_PSCREEN)
#define KC_SUPR RCTL(KC_RSFT)
#define KC_LGON LCTL(LGUI(LALT(KC_DEL)))

// for MacOS
#define MC_VOLU KC__VOLUP
#define MC_VOLD KC__VOLDOWN
#define MC_MUTE KC__MUTE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                     KC_6  , KC_7  , KC_8  , KC_9   , KC_0  ,KC_RGUI,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_G  ,                     KC_J  , KC_L  , KC_U  , KC_Y   ,KC_SCLN,KC_DEL ,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     KC_LCTL, KC_A  , KC_R  , KC_S  , KC_T  , KC_D  ,                     KC_H   , KC_N  , KC_E  , KC_I  , KC_O  ,KC_BSPC,
  //|-C-----+-------+-------+-------+-------+-------+-------.    ,-------|-------+-------+-------+-------+-------+-------|
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,MC_VOLU     , MC_VOLD,KC_K  , KC_M  , KC_COMM,KC_DOT ,KC_SLSH,KC_SUPR,
  //`-------+-------+-------+--+-+-------+-------+-------/       \-------+-------+-------+-------+-------+------+-------'
                              KC_LGUI,KC_LALT,KC_LCTL,KC_SPC      , KC_ENT,KC_LOWR,KC_RASE, KC_
  //                           `-------+-------+-------'           `-------+-------+-------'
  ),

  [_LOWER] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                    ,-------+-------+-------+-------+-------+-------.
     KC_PSCN,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                     KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
 //|--------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     _______,_______,KC_EQL ,KC_LBRC,KC_RBRC,KC_GRV ,                     KC_NUBS,KC_HOME, KC_UP ,KC_END ,KC_PGUP,KC_INS ,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     _______,KC_LCBR,KC_RCBR,KC_LPRN,KC_RPRN,KC_NUHS,	                  KC_QUOT,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,_______,
  //|-------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+-------|
     _______,KC_EXLM,KC_AT,UK_PND ,KC_DLR ,KC_PERC  ,KC_,         KC_    ,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
  //`-------+-------+-------+-------+-------+-------+-------/    \-------+-------+-------+-------+-------+-------+-------'
                                KC_ ,_______,_______,KC_EQL,      KC_MINS,_______,_______, KC_
  //                          `----------+----------+-------'     `------+-------+-------+-------'
  ),

  [_RAISE] = LAYOUT(
  //,-------+-------+-------+-------+-------+-------.                            ,-------+-------+-------+-------+-------+-------.
     KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                             KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
  //|-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
     KC_    , KC_   , KC_   ,KC_UNDS, KC_   , KC_   ,                             KC_    ,  KC_  ,KC_PLUS, KC_   ,KC_    ,KC_LGON,
  //|-------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+-------|
     KC_    , KC_   ,KC_    ,KC_MINS, KC_   , KC_   ,                             KC_    ,KC_MUTE,KC_EQL , KC_   ,KC_VOLU, KC_   ,
  //|-------+-------+-------+-------+-------+-------+-------.            ,-------|-------+-------+-------+-------+-------+-------|
       KC_  , KC_   , KC_   , KC_   , KC_   , KC_   ,KC_MPLY             ,MC_MUTE, KC_   ,KC_MRWD,KC_MPLY,KC_MFFD,KC_VOLD,KC_    ,
  //`-------+-------+-------+--+-+-------+-------+-------/               \-------+-------+-------+-------+-------+-------+-------'
                              KC_ , KC_   ,  KC_  ,   KC_  ,                KC_  ,KC_    ,KC_    , KC_
  //                   `-------+-------+-------'                           `-------+-------+-------'
  ),


};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_left())
    return OLED_ROTATION_180; // 270 for plain text
  return rotation;
}

const char *read_logo(void);

void oled_task_user(void) {
  if (!is_keyboard_left()) {
    const char * logo = read_logo();
    oled_write(logo, false);
    // oled_write_P(PSTR("HELLO"), false);
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _RAISE:
        trackball_set_rgbw(0xFF,  0x00, 0x00, 0x00);
        break;
    case _LOWER:
        trackball_set_rgbw(0x00,  0x00, 0xFF, 0x00);
	trackball_set_scrolling(true);
        break;
    default: //  for any other layers, or the default layer
        trackball_set_rgbw(0x00,  0x00, 0x00, 0x00);
	trackball_set_scrolling(false);
        break;
    }
  return state;
}
