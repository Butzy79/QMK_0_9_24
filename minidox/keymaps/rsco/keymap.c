#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT
};
//Tap Dance Declarations
enum {  
  TD_PLAYNEX = 0,
  TD_ESC,
  TD_ALTLGUI,
  TD_BSPCDEL
};

//Tap Dance Declarations
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7,
  QUINTUPLE_HOLD = 8,
  TD_STATE_MAGIC
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_PLAYNEX]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,x_finished, x_reset),
  [TD_ESC]		   = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
  [TD_ALTLGUI]       = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_LALT),
  [TD_BSPCDEL]       = ACTION_TAP_DANCE_DOUBLE(KC_BSPC, KC_DEL)
};

//In Layer declaration, add tap dance item in place of a key code
#define PLYNXT TD(TD_PLAYNEX)
#define ESCQ TD(TD_ESC)
#define ALTLGUI TD(TD_ALTLGUI)
#define BSPCDEL TD(TD_BSPCDEL)
// Adding macros to make the keymaps below much easier to read.
#define LCTLSCL LCTL_T(KC_SCLN)
#define RSFTSCL RSFT_T(KC_SCLN)
#define RCTLSLS RCTL_T(KC_SLSH)
#define LCTLZED LCTL_T(KC_Z)
#define RCTLZED RCTL_T(KC_Z)
#define LSFTA LSFT_T(KC_A)
#define RSFTS RSFT_T(KC_S)
#define RSFTO RSFT_T(KC_O)
#define ALTSPC RALT_T(KC_SPC) 
#define GUITAB LGUI(KC_TAB)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT ( \
  ESCQ,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  LSFTA,   KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L,    RSFTSCL, \
  LCTLZED, KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  RCTLSLS, \
                    ALTLGUI, LOWER,   KC_BSPC,    ALTSPC,  RAISE,   KC_ENT                     \
),


[_LOWER] = LAYOUT ( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  GUITAB,  KC_UNDS, KC_UP,   KC_END,  KC_INS,     KC_PGUP, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, \
  KC_TILD, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,     KC_PGDN, KC_QUOT, KC_BSLS, KC_LCBR, KC_RCBR, \
                    KC_APP,  _______, KC_TAB,    KC_ESC,  _______,KC_RGUI                    \
),

[_RAISE] = LAYOUT ( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  GUITAB,  KC_BTN1, KC_MS_U, KC_BTN2, KC_INS,     KC_PGUP, KC_4, KC_5,   KC_6,  KC_PMNS, \
  KC_GRV,  KC_MS_L, KC_MS_D, KC_MS_R, KC_DEL,     KC_PGDN, KC_1, KC_2, KC_3, KC_PPLS, \
                    KC_LGUI, _______, _______,    KC_SPC,  _______, KC_0                       \
),

[_ADJUST] = LAYOUT ( 
  KC_ESC , KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_NLCK,  RESET, _______, _______, DEBUG,    \
  KC_CLCK, KC_F5,   KC_F6,   KC_F7,   KC_F8,      KC_HOME, KC_PSCR, KC_SLCK, KC_PAUS, KC_VOLU,  \
  _______, KC_F9,   KC_F10 , KC_F11,  KC_F12,     KC_END,   KC_SLEP, _______, PLYNXT,  KC_VOLD,  \
                    _______, _______, _______,    _______, _______, _______                     \
)
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
};

void matrix_init_user(void) {
   // This will disable the red LEDs on the ProMicros
   DDRD &= ~(1<<5);
   PORTD &= ~(1<<5);
   DDRB &= ~(1<<0);
   PORTB &= ~(1<<0);

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            persistent_default_layer_set(1UL<<_QWERTY);
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
      }
    return true;
};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return TD_STATE_MAGIC; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

// APP 1x tap, ESC 2x tap, Toggle QWERTY/COLEMAK 3x tap, Keyboard reset 5x tap and hold

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_MPLY); break;
    case DOUBLE_TAP: register_code(KC_MNXT); break;
	case TRIPLE_TAP: register_code(KC_MPRV); break;
  }
}

void x_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_MPLY); break;
    case DOUBLE_TAP: unregister_code(KC_MNXT); break;
	case TRIPLE_TAP: unregister_code(KC_MPRV); break;
  }
  xtap_state.state = 0;
}
