#include QMK_KEYBOARD_H

/** #define _DEF 0 */
/** #define FN 1 */
/** #define SPC 2 */

// layer name for readability
enum keymap_layout {
  _DEF = 0,
  _FN1,
  _SPC,
  _SFT,
  _AUX,
  _LED,
  _LCK,
  _RST
}; 

// dual-role shortcuts
#define CAPSDUAL  CTL_T(KC_ESC)
#define SPACEDUAL LT(_SPC, KC_SPACE)
#define APPDUAL  LT(_AUX, KC_APP)
/** #define LEDDUAL LT(_LED, RGB_TOG) */

// increase readability
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// tapdance keycodes
enum td_keycodes {
  LEDDUAL
};

// define a type containing as many tapdance states as you need
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD
} td_state_t;

// create a global instance of the tapdance state type
static td_state_t td_state;

// declare your tapdance functions:

// function to determine the current tapdance state
int cur_dance (qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void ledtap_finished (qk_tap_dance_state_t *state, void *user_data);
void ledtap_reset (qk_tap_dance_state_t *state, void *user_data);

// determine the tapdance state to return
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  else { return 2; } // any number higher than the maximum state value you return above
};

// handle the possible states for each tapdance keycode you define:
void ledtap_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      rgblight_toggle();
      break;
    case SINGLE_HOLD:
      layer_on(_LED);
  }
};

void ledtap_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      break;
    case SINGLE_HOLD:
      layer_off(_LED);
  }
};

// define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
  [LEDDUAL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ledtap_finished, ledtap_reset)
};


    /* 0: Template Layer
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │█████│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │█████│     │     │     │     │     │     │     │     │     │     │█████│     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│█████│     │     │█████│█████│█████│     │█████│█████│█████│█████│     │     │█████│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
/** [_LYR]= LAYOUT_60_hhkb( */
/**        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \ */
/**        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   \ */
/**        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,   \ */
/**        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \ */
/**                 _______, _______,                            _______,                                     _______, _______ ), */
  

/*
 * Default HHKB Layout
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: Default layer
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ Esc │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  -  │  =  │  \  │  `  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│ Tab │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  [  │  ]  │BkSpc│█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Ctrl │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │  ;  │  '  │█████│Enter│█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Shift│█████│  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │█████│Shift│ Fn  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│█████│ Gui │ Alt │█████│█████│Space│█████│█████│█████│█████│█████│ Alt │ Gui │█████│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
[_DEF] = LAYOUT_60_hhkb(
        KC_GESC,   KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL, KC_BSLS, KC_GRV, \
        KC_TAB,    KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSPC,      \
        CAPSDUAL,   KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,       KC_ENT,      \
        KC_LSFT,            KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M, KC_COMM,  KC_DOT, KC_SLSH,      KC_RSFT, MO(_FN1), \
             KC_LGUI, KC_LALT,              SPACEDUAL,                         KC_RALT, APPDUAL ),

    /* 1: HHKB Fn layer
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ Pwr │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │ Ins │ Del │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Caps │ RGB │RGBfw│RGBrv│BLtog│BLstp│     │     │ Psc │ Slk │ Pus │ Up  │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │ VoD │ VoU │ Mut │ Ejc │     │NP_* │NP_/ │Home │PgUp │Left │Right│█████│NPEnt│█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │█████│     │     │     │     │     │NP_+ │NP_- │ End │PgDwn│Down │█████│     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│█████│     │     │█████│█████│█████│     │█████│█████│█████│█████│     │     │█████│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
[_FN1]= LAYOUT_60_hhkb(
       KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL, \
       KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS,   KC_UP, _______, KC_DEL,   \
       _______, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, _______, KC_PAST, KC_PSLS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,       KC_PENT,       \
       _______,       _______, _______, _______, _______, _______, KC_PPLS, KC_PMNS,  KC_END, KC_PGDN, KC_DOWN,       _______, _______, \
             _______, _______,                   XXXXXXX,                         _______, _______ ),

    /* 2: Space Fn layer
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│ Pwr │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │ Ins │ Del │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│Caps │ RGB │RGBfw│RGBrv│BLtog│BLstp│     │     │ Psc │ Slk │ Pus │ Up  │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │ VoD │ VoU │ Mut │ Ejc │     │NP_* │NP_/ │Home │PgUp │Left │Right│█████│NPEnt│█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │█████│     │     │     │     │     │NP_+ │NP_- │ End │PgDwn│Down │█████│     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│█████│     │     │█████│█████│█████│     │█████│█████│█████│█████│     │     │█████│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
[_SPC]= LAYOUT_60_hhkb(
       KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  \
       _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT, KC_BSLS,          _______,       \
       _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, MO(_SFT),        MO(_SFT), XXXXXXX, \
                _______, _______,                            _______,                                     _______, KC_APP  ),

    /* 3: Shift Layer
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │  _  │  +  │  {  │  }  │     │Home │PgUp │PgDn │ End │     │     │█████│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │█████│     │     │     │     │     │     │     │     │     │     │█████│     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│█████│     │     │█████│█████│█████│     │█████│█████│█████│█████│     │     │█████│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
[_SFT]= LAYOUT_60_hhkb(
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   \
       _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,   \
       _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
	        _______, _______,                            _______,                                     _______, _______ ),

    /* 4: Aux Layer
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │█████│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │█████│     │     │     │     │     │     │     │     │     │     │█████│     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│█████│     │     │█████│█████│█████│     │█████│█████│█████│█████│     │     │█████│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
[_AUX]= LAYOUT_60_hhkb(
       KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, \
       _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______, KC_VOLU,   \
       _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  KC_HOME, KC_PGUP, _______,          KC_VOLD,   \
       _______,          KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, _______, _______, _______, KC_DEL,  KC_END,  KC_PGDN,          KC_MUTE, TG(_LCK), \
                MO(_RST), _______,                            XXXXXXX,                                  TD(LEDDUAL), _______ ),

    /* 5: LED Control Layer
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │█████│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │█████│     │     │     │     │     │     │     │     │     │     │█████│     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│█████│     │     │█████│█████│█████│     │█████│█████│█████│█████│     │     │█████│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
[_LED]= LAYOUT_60_hhkb(
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
       _______, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, _______,   \
       _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD,RGB_TOG, _______, _______, _______, _______, _______, _______,          _______,   \
       _______,          _______, _______, BL_TOGG, BL_INC,  BL_DEC,  BL_STEP, _______, _______, _______, _______,          _______, XXXXXXX, \
                _______, _______,                            XXXXXXX,                                     _______, _______ ),

    /* 6: Toggle Space / Ctrl Lock
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │█████│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │█████│     │     │     │     │     │     │     │     │     │     │█████│     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│█████│     │     │█████│█████│█████│     │█████│█████│█████│█████│     │     │█████│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
[_LCK]= LAYOUT_60_hhkb(
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   \
       KC_LCTL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,   \
       _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
                _______, _______,                            KC_SPACE,                                    _______, _______ ),

    /* 7: RESET
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
│RESET│     │     │     │     │     │     │     │     │     │     │     │     │     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │     │     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │     │     │     │     │     │     │     │     │     │     │     │█████│     │█████│
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│     │█████│     │     │     │     │     │     │     │     │     │     │█████│     │     │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
│█████│     │     │█████│█████│█████│     │█████│█████│█████│█████│     │     │█████│█████│
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
     */
[_RST]= LAYOUT_60_hhkb(
       RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   \
       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,   \
       _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
                _______, _______,                            XXXXXXX,                                    _______, _______ ),
};


