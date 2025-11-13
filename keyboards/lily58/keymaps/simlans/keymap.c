#include "simlans.h"

enum layer_number {
  _QWERTY = 0,
  //_BONE=0,
  _SYM,
  _SYM_MAC,
  _NAV,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  ß   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  Ü   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI | SYM  | /Space  /       \Enter \  |  NAV |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_QWERTY] = LAYOUT(
  KC_ESC,   DE_1,   DE_2,   DE_3,     DE_4,     DE_5,                                 DE_6,     DE_7,    DE_8,    DE_9,    DE_0,     DE_SS,
  KC_TAB,   DE_Q,   DE_W,   DE_E,     DE_R,     DE_T,                                 DE_Y,     DE_U,    DE_I,    DE_O,    DE_P,     DE_UDIA,
  KC_LCTL,  DE_A,   DE_S,   DE_D,     DE_F,     DE_G,                                 DE_H,     DE_J,    DE_K,    DE_L,    DE_ODIA,  DE_ADIA,
  KC_LSFT,  DE_Z,   DE_X,   DE_C,     DE_V,     DE_B,     _______,          _______,  DE_N,     DE_M,    DE_COMM, DE_DOT,  DE_MINS,  KC_RSFT,
                            KC_LALT,  KC_LGUI,  CKC_SYM,  KC_SPC,           KC_ENT,   MO(_NAV), KC_BSPC, KC_RGUI
),

/* BONE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |   -  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   J  |   D  |   U  |   A  |   X  |                    |   P  |   H  |   L  |   M  |   W  |   ß  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   C  |   T  |   I  |   E  |   O  |-------.    ,-------|   B  |   N  |   R  |   S  |   G  |   Q  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   F  |   V  |   Ü  |   Ä  |   Ö  |-------|    |-------|   Y  |   Z  |   ,  |   .  |   K  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI | SYM  | /Space  /       \Enter \  |  NAV |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
/*
 [_BONE] = LAYOUT(
  KC_ESC,   DE_1,   DE_2,    DE_3,    DE_4,     DE_5,                                   DE_6,     DE_7,    DE_8,    DE_9,    DE_0,   DE_MINS,
  KC_TAB,   DE_J,   DE_D,    DE_U,    DE_A,     DE_X,                                   DE_P,     DE_H,    DE_L,    DE_M,    DE_W,   DE_SS,
  KC_LCTL,  DE_C,   DE_T,    DE_I,    DE_E,     DE_O,                                   DE_B,     DE_N,    DE_R,    DE_S,    DE_G,   DE_Q,
  KC_LSFT,  DE_F,   DE_V,    DE_UDIA, DE_ADIA,  DE_ODIA,    _______,          _______,  DE_Y,     DE_Z,    DE_COMM, DE_DOT,  DE_K,   KC_RSFT,
                              KC_LALT, KC_LGUI, CKC_SYM, KC_SPC,              KC_ENT,   MO(_NAV), KC_BSPC, KC_RGUI
),
 */
/* SYM
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ---- |   ¹  |   ²  |   ³  | ---- | ---- |                    | ---- | ---- |   ,  |   ‘  |   ’  | ---- |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ---- |   …  |   _  |   [  |   ]  |   ^  |                    |   !  |   <  |   >  |   =  |   &  | ---- |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ---- |   \  |   /  |   {  |   }  |   *  |-------.    ,-------|   ?  |   (  |   )  |   -  |   :  |   @  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | ---- |   #  |   $  |   |  |   ~  |   `  |-------|    |-------|   +  |   %  |   "  |   '  |   ;  | ---- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI | ---- | /Space  /       \Enter \  | ---- |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_SYM] = LAYOUT(
  KC_ESC,   L58_SYM_SUPS_1,     L58_SYM_SUPS_2,       L58_SYM_SUPS_3,       KC_NO,                KC_NO,                                                    KC_NO,                  KC_NO,                  L58_SYM_SBQUO,          L58_SYM_LSQ,            L58_SYM_RSQ,          KC_NO,
  KC_TAB,   L58_SYM_ELLIPSIS,   L58_SYM_UNDERSCORE,   L58_SYM_LBRACKET,     L58_SYM_RBRACKET,     L58_SYM_CIRCUMFLEX,                                       L58_SYM_EXCLAMATION,    L58_SYM_LESSTHAN,       L58_SYM_GREATERTHAN,    L58_SYM_EQUAL,          L58_SYM_AMPERSAND,    KC_NO,
  KC_LCTL,  L58_SYM_BSLASH,     L58_SYM_SLASH,        L58_SYM_CLBRACKET,    L58_SYM_CRBRACKET,    L58_SYM_ASTERISK,                                         L58_SYM_QUESTIONMARK,   L58_SYM_LPARENTHESES,   L58_SYM_RPARENTHESES,   L58_SYM_HYPHEN_MINUS,   L58_SYM_COLON,        L58_SYM_AT,
  KC_LSFT,  L58_SYM_HASH,       L58_SYM_DOLLAR,       L58_SYM_PIPE,         L58_SYM_TILDE,        L58_SYM_BACKTICK,     _______,                _______,    L58_SYM_PLUS,           L58_SYM_PERCENT,        L58_SYM_DOUBLE_QUOTE,   L58_SYM_SINGLE_QUOTE,   L58_SYM_SEMICOLON,    KC_NO,
                                                      KC_LALT,              KC_LGUI,              _______,              KC_SPC,                 KC_ENT,     _______,                KC_BSPC,                KC_RGUI
),
 [_SYM_MAC] = LAYOUT(
  KC_ESC,   DE_1,               DE_2,                 DE_3,                   DE_4,                     DE_5,                                                    KC_NO,                  KC_NO,                  L58_SYM_SBQUO_MAC,        L58_SYM_LSQ_MAC,        L58_SYM_RSQ_MAC,      KC_NO,
  KC_TAB,   L58_SYM_ELLIPSIS,   L58_SYM_UNDERSCORE,   L58_SYM_LBRACKET_MAC,   L58_SYM_RBRACKET_MAC,     L58_SYM_CIRCUMFLEX_MAC,                                   L58_SYM_EXCLAMATION,    L58_SYM_LESSTHAN_MAC,   L58_SYM_GREATERTHAN_MAC,  L58_SYM_EQUAL,          L58_SYM_AMPERSAND,    KC_NO,
  KC_LCTL,  L58_SYM_BSLASH_MAC, L58_SYM_SLASH_MAC,    L58_SYM_CLBRACKET_MAC,  L58_SYM_CRBRACKET_MAC,    L58_SYM_ASTERISK,                                         L58_SYM_QUESTIONMARK,   L58_SYM_LPARENTHESES,   L58_SYM_RPARENTHESES,     L58_SYM_HYPHEN_MINUS,   L58_SYM_COLON,        L58_SYM_AT_MAC,
  KC_LSFT,  L58_SYM_HASH,       L58_SYM_DOLLAR,       L58_SYM_PIPE_MAC,       L58_SYM_TILDE_MAC,        L58_SYM_BACKTICK,     _______,                _______,    L58_SYM_PLUS,           L58_SYM_PERCENT,        L58_SYM_DOUBLE_QUOTE,     L58_SYM_SINGLE_QUOTE,   L58_SYM_SEMICOLON,    KC_NO,
                                                      KC_LALT,                KC_LGUI,                  _______,              KC_SPC,                 KC_ENT,     _______,                KC_BSPC,                KC_RGUI
),

/* NAV
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    | ---- | Tab  |   /  |  *   |   -  | ---- |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | PgUp |   ⌫  |  Up  |   ⌦  | PgDn |                    | ---- |   7  |  8   |  9   |   +  | ---- |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Home | Left | Down | Right| End  |-------.    ,-------| ---- |   4  |  5   |  6   |   ,  |   .  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | Esc  | Tab  | Ins  | Enter| ---- |-------|    |-------|   :  |   1  |  2   |  3   |   ;  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI | ---- | /Space  /       \Enter \  | ---- |BackSP|  0   |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_NAV] = LAYOUT(
  KC_ESC,   KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,                                        KC_NO,            KC_TAB,     L58_SYM_SLASH,    L58_SYM_ASTERISK,   L58_SYM_HYPHEN_MINUS,   KC_NO,
  KC_TAB,   KC_PGUP,    KC_BSPC,    KC_UP,      KC_DEL,     KC_PGDN,                                      KC_NO,            KC_7,       KC_8,             KC_9,               L58_SYM_PLUS,           KC_NO,
  KC_LCTL,  KC_HOME,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_END,                                       KC_NO,            KC_4,       KC_5,             KC_6,               DE_COMM,                KC_DOT,
  KC_LSFT,  KC_ESC,     KC_TAB,     KC_INS,     KC_ENT,     KC_NO,    _______,                _______,    L58_SYM_COLON,    KC_1,       KC_2,             KC_3,               L58_SYM_SEMICOLON,      KC_NO,
                                    KC_LALT,    KC_LGUI,    _______,  KC_SPC,                 KC_ENT,     _______,          KC_BSPC,    KC_0
)
};

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

uint16_t os_based_sym_layer(void) {
    switch(detected_host_os()) {
      case OS_MACOS:
      case OS_IOS:
        return _SYM_MAC;
      default:
        return _SYM;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CKC_SYM: {
      uint16_t os_symbol_layer = _SYM;
      os_symbol_layer = os_based_sym_layer();

      if (!record->tap.count && record->event.pressed) {
          layer_on(os_symbol_layer);
          return false;
      }
      layer_off(os_symbol_layer);
      return false;
    }
  }

  return true;
}
