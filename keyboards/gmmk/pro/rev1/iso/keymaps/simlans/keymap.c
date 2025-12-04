/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "simlans.h"

// clang-format off

// Track the current base layer for LED colors
static uint8_t current_base_layer = DEFAULT_LAYER;

// OS detection state - LEDs stay off until OS is detected
static bool os_detected = false;
static uint32_t keyboard_init_time = 0;

// Visor effect state
static bool visor_effect_active = false;
static uint32_t visor_effect_start_time = 0;

// LED column distances from center (0 = center, higher = further out)
// Based on physical keyboard layout - Space bar area is center
static const uint8_t PROGMEM led_distance_from_center[RGB_MATRIX_LED_COUNT] = {
    // Row 0: ESC to Del (indices 0, 6, 12, 18, 23, 28, 34, 39, 44, 50, 56, 61, 66, 70)
    [0] = 7,   // ESC - far left
    [6] = 6,   // F1
    [12] = 5,  // F2
    [18] = 4,  // F3
    [23] = 3,  // F4
    [28] = 2,  // F5
    [34] = 1,  // F6
    [39] = 0,  // F7 - center
    [44] = 1,  // F8
    [50] = 2,  // F9
    [56] = 3,  // F10
    [61] = 4,  // F11
    [66] = 5,  // F12
    [70] = 6,  // Del
    [73] = 7,  // Home

    // Row 1: ~ to Backspace (indices 1, 7, 13, 19, 24, 29, 35, 40, 45, 51, 57, 62, 79, 86)
    [1] = 7,   // ~
    [7] = 6,   // 1
    [13] = 5,  // 2
    [19] = 4,  // 3
    [24] = 3,  // 4
    [29] = 2,  // 5
    [35] = 1,  // 6
    [40] = 0,  // 7 - center
    [45] = 1,  // 8
    [51] = 2,  // 9
    [57] = 3,  // 0
    [62] = 4,  // -
    [79] = 5,  // =
    [86] = 6,  // Backspace
    [76] = 7,  // PgUp

    // Row 2: Tab to ] (indices 2, 8, 14, 20, 25, 30, 36, 41, 46, 52, 58, 63, 90)
    [2] = 7,   // Tab
    [8] = 6,   // Q
    [14] = 5,  // W
    [20] = 4,  // E
    [25] = 3,  // R
    [30] = 2,  // T
    [36] = 1,  // Y
    [41] = 0,  // U - center
    [46] = 1,  // I
    [52] = 2,  // O
    [58] = 3,  // P
    [63] = 4,  // [
    [90] = 5,  // ]

    // Row 3: Caps to Enter (indices 3, 9, 15, 21, 26, 31, 37, 42, 47, 53, 59, 64, 95, 97)
    [3] = 7,   // Caps
    [9] = 6,   // A
    [15] = 5,  // S
    [21] = 4,  // D
    [26] = 3,  // F
    [31] = 2,  // G
    [37] = 1,  // H - center
    [42] = 0,  // J - center
    [47] = 1,  // K
    [53] = 2,  // L
    [59] = 3,  // ;
    [64] = 4,  // '
    [95] = 5,  // #
    [97] = 6,  // Enter
    [87] = 7,  // PgDn

    // Row 4: Shift to Shift (indices 4, 67, 10, 16, 22, 27, 32, 38, 43, 48, 54, 60, 91)
    [4] = 7,   // Shift L
    [67] = 6,  // backslash
    [10] = 5,  // Z
    [16] = 4,  // X
    [22] = 3,  // C
    [27] = 2,  // V
    [32] = 1,  // B
    [38] = 0,  // N - center
    [43] = 1,  // M
    [48] = 2,  // ,
    [54] = 3,  // .
    [60] = 4,  // /
    [91] = 5,  // Shift R
    [94] = 6,  // Up
    [83] = 7,  // End

    // Row 5: Ctrl to Right (indices 5, 11, 17, 33, 49, 55, 65, 96, 98, 80)
    [5] = 7,   // Ctrl L
    [11] = 6,  // Win
    [17] = 5,  // Alt L
    [33] = 0,  // Space - center
    [49] = 3,  // Alt R
    [55] = 4,  // FN
    [65] = 5,  // Ctrl R
    [96] = 6,  // Left
    [98] = 7,  // Down
    [80] = 7,  // Right

    // Side LEDs - left side (far left = high distance)
    [68] = 8,  // Side L 1
    [71] = 8,  // Side L 2
    [74] = 8,  // Side L 3
    [77] = 8,  // Side L 4
    [81] = 8,  // Side L 5
    [84] = 8,  // Side L 6
    [88] = 8,  // Side L 7
    [92] = 8,  // Side L 8

    // Side LEDs - right side (far right = high distance)
    [69] = 8,  // Side R 1
    [72] = 8,  // Side R 2
    [75] = 8,  // Side R 3
    [78] = 8,  // Side R 4
    [82] = 8,  // Side R 5
    [85] = 8,  // Side R 6
    [89] = 8,  // Side R 7
    [93] = 8,  // Side R 8
};

// Start the visor effect animation
void start_visor_effect(void) {
    visor_effect_active = true;
    visor_effect_start_time = timer_read32();
}

// Reset state on USB connection/reconnection
void keyboard_pre_init_user(void) {
    // Reset OS detection state - will be set when OS is detected
    os_detected = false;
    visor_effect_active = false;
    keyboard_init_time = timer_read32();
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Del           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Home
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]                          PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "        #        Enter             PgDn
//      Sh_L     /        Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backspace. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [DEFAULT_LAYER] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,       KC_F12,  KC_DEL,           KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,      KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,      KC_RBRC,                   KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,      KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,               KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(FN_LAYER), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [MACOS_LAYER] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, KC_LALT, KC_LGUI,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [FN_LAYER] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          _______,
        _______, RM_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, RM_VALU, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, RM_VALD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, RM_HUEU, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RM_NEXT, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RM_SPDD, RM_PREV, RM_SPDU
    ),
};

// LED Color Maps for each layer
// Use RGB_MATRIX_LAYOUT_LEDMAP to define colors in a visual matrix format
const ledmap PROGMEM ledmaps[][RGB_MATRIX_LED_COUNT] = {

//      LU = Left Underglow, RU = Right Underglow
//      LU_1                                                                                                                                              RU_1
//      LU_2       ESC     F1      F2      F3      F4      F5      F6      F7      F8      F9      F10     F11     F12     Del                Home        RU_2
//      LU_3       ~       1       2       3       4       5       6       7       8       9       0        -      (=)     BackSpc            PgUp        RU_3
//      LU_4       Tab     Q       W       E       R       T       Y       U       I       O       P       [       ]                                      RU_4
//      LU_5       Caps    A       S       D       F       G       H       J       K       L       ;       "       #       Enter              PgDn        RU_5
//      LU_6       Sh_L    /       Z       X       C       V       B       N       M       ,       .       ?               Sh_R      Up       End         RU_6
//      LU_7       Ct_L    Win_L   Alt_L                           SPACE                           Alt_R   FN      Ct_R    Left      Down     Right       RU_7
//      LU_8                                                                                                                                              RU_8
    [DEFAULT_LAYER] = RGB_MATRIX_LAYOUT_LEDMAP(
        LED_BLUE___,                                                                                                                                                                                                                 LED_BLUE___,
        LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___,              LED_BLUE___, LED_BLUE___,
        LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___,              LED_BLUE___, LED_BLUE___,
        LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___,                                        LED_BLUE___,
        LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___,              LED_BLUE___, LED_BLUE___,
        LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___,              LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___,
        LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___,                                        LED_BLUE___,                                        LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___, LED_BLUE___,
        LED_BLUE___,                                                                                                                                                                                                                 LED_BLUE___
    ),

    [MACOS_LAYER] = RGB_MATRIX_LAYOUT_LEDMAP(
        LED_WHITE__,                                                                                                                                                                                                                 LED_WHITE__,
        LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__,              LED_WHITE__, LED_WHITE__,
        LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__,              LED_WHITE__, LED_WHITE__,
        LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__,                                        LED_WHITE__,
        LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__,              LED_WHITE__, LED_WHITE__,
        LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__,              LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__,
        LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__,                                        LED_WHITE__,                                        LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__, LED_WHITE__,
        LED_WHITE__,                                                                                                                                                                                                                 LED_WHITE__
    ),

    [FN_LAYER] = RGB_MATRIX_LAYOUT_LEDMAP(
        LED_GREEN__,                                                                                                                                                                                                                 LED_GREEN__,
        LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__,              LED_GREEN__, LED_GREEN__,
        LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__,              LED_GREEN__, LED_GREEN__,
        LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__,                                        LED_GREEN__,
        LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__,              LED_GREEN__, LED_GREEN__,
        LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__,              LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__,
        LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__,                                        LED_GREEN__,                                        LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__, LED_GREEN__,
        LED_GREEN__,                                                                                                                                                                                                                 LED_GREEN__
    ),
};

void keyboard_post_init_user(void) {
    // Set RGB Matrix to solid color mode
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
}

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }

    // Ensure we're in solid color mode
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);

    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            current_base_layer = MACOS_LAYER;
            set_single_default_layer(MACOS_LAYER);
            break;
        case OS_WINDOWS:
            current_base_layer = DEFAULT_LAYER;
            set_single_default_layer(DEFAULT_LAYER);
            break;
        case OS_LINUX:
            current_base_layer = DEFAULT_LAYER;
            set_single_default_layer(DEFAULT_LAYER);
            break;
        case OS_UNSURE:
            current_base_layer = DEFAULT_LAYER;
            set_single_default_layer(DEFAULT_LAYER);
            break;
    }

    // Mark OS as detected and start the visor effect animation
    os_detected = true;
    start_visor_effect();

    return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // If OS not yet detected, check for timeout
    if (!os_detected) {
        if (timer_elapsed32(keyboard_init_time) >= OS_DETECTION_TIMEOUT) {
            // Timeout reached - no OS detected, use default layer and start visor
            os_detected = true;
            current_base_layer = DEFAULT_LAYER;
            set_single_default_layer(DEFAULT_LAYER);
            start_visor_effect();
        } else {
            // Still waiting for OS detection - keep LEDs off
            for (uint8_t i = led_min; i < led_max; i++) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
            return false;
        }
    }

    // Get current active layer, or use base layer if none active
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == 0) {
        layer = current_base_layer;
    }

    // Handle visor effect animation
    if (visor_effect_active) {
        uint32_t elapsed = timer_elapsed32(visor_effect_start_time);

        if (elapsed >= VISOR_EFFECT_DURATION) {
            // Animation complete
            visor_effect_active = false;
        } else {
            // Calculate current wave position (0-8, representing distance from center)
            // The wave expands outward from center
            uint8_t current_wave = (elapsed * 9) / VISOR_EFFECT_DURATION;

            // Get target color from current layer's ledmap
            for (uint8_t i = led_min; i < led_max; i++) {
                uint8_t distance = pgm_read_byte(&led_distance_from_center[i]);
                ledmap target_led = ledmaps[layer][i];

                if (distance <= current_wave) {
                    // This LED has been reached - show target color
                    if (target_led.r != 0 || target_led.g != 0 || target_led.b != 0) {
                        rgb_matrix_set_color(i, target_led.r, target_led.g, target_led.b);
                    }
                } else {
                    // This LED hasn't been reached yet - stay off
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }

            // Override with Caps Lock indicator even during visor effect
            if (host_keyboard_led_state().caps_lock) {
                const uint8_t side_leds_left[] = SIDE_LED_LEFT;
                const uint8_t side_leds_right[] = SIDE_LED_RIGHT;

                for (uint8_t i = 0; i < SIDE_LED_COUNT; i++) {
                    rgb_matrix_set_color(side_leds_left[i], LED_RED_RGB);
                }
                for (uint8_t i = 0; i < SIDE_LED_COUNT; i++) {
                    rgb_matrix_set_color(side_leds_right[i], LED_RED_RGB);
                }
            }

            return false;
        }
    }

    // Normal operation: Apply layer-specific LED colors from ledmap
    if (layer < sizeof(ledmaps) / sizeof(ledmaps[0])) {
        for (uint8_t i = led_min; i < led_max; i++) {
            ledmap led = ledmaps[layer][i];
            // Only set color if it's not RGB_OFF (which means "no change")
            if (led.r != 0 || led.g != 0 || led.b != 0) {
                rgb_matrix_set_color(i, led.r, led.g, led.b);
            }
        }
    }

    // Override with Caps Lock indicator on side LEDs
    if (host_keyboard_led_state().caps_lock) {
        const uint8_t side_leds_left[] = SIDE_LED_LEFT;
        const uint8_t side_leds_right[] = SIDE_LED_RIGHT;

        // Set left side strip to red
        for (uint8_t i = 0; i < SIDE_LED_COUNT; i++) {
            rgb_matrix_set_color(side_leds_left[i], LED_RED_RGB);
        }

        // Set right side strip to red
        for (uint8_t i = 0; i < SIDE_LED_COUNT; i++) {
            rgb_matrix_set_color(side_leds_right[i], LED_RED_RGB);
        }
    }

    return false;
}

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [DEFAULT_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MACOS_LAYER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [FN_LAYER] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

// clang-format on