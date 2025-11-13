#pragma once
#include QMK_KEYBOARD_H

enum layer_number {
    WIN_LAYER_DEF_LAYER = 0,
    MACOS_LAYER,
    FN_LAYER,
};

// RGB LED Matrix Layout for GMMK Pro Rev1 ISO
// Source: Reddit community mapping
//
// LED layout visualization:
// led number, function of the key
//
//  68, Side led 01    0, ESC      6, F1       12, F2       18, F3       23, F4       28, F5       34, F6       39, F7       44, F8       50, F9       56, F10      61, F11      66, F12      70, Del                  Rotary(Mute)      69, Side led 12
//  71, Side led 02    1, `~       7, 1        13, 2        19, 3        24, 4        29, 5        35, 6        40, 7        45, 8        51, 9        57, 0        62, -_       79, (=+)     86, BackSpc                 73, Home       72, Side led 13
//  74, Side led 03    2, Tab      8, Q        14, W        20. E        25, R        30, T        36, Y        41, U        46, I        52, O        58, P        63, [{       90, ]}                                   76, PgUp       75, Side led 14
//  77, Side led 04    3, Caps     9, A        15, S        21, D        26, F        31, G        37, H        42, J        47, K        53, L        59, ;:       64, '"       95, #        97, Enter                   87, PgDn       78, Side led 15
//  81, Side led 05    4, Sh_L     67,\        10, Z        16, X        22, C        27, V        32, B        38, N        43, M        48, ,        54, .        60, /?                    91, Sh_R        94, Up      83, End        82, Side led 16
//  84, Side led 06    5, Ct_L     11,Win_L    17, Alt_L                                           33, SPACE                              49, Alt_R    55, FN       65, Ct_R                  96, Left        98, Down    80, Right      85, Side led 17
//  88, Side led 07                                                                                                                                                                                                                      89, Side led 18
//  92, Side led 08                                                                                                                                                                                                                      93, Side led 19
//
// Side LED strips (left and right edges):
// Left side (8 LEDs):  68, 71, 74, 77, 81, 84, 88, 92
// Right side (8 LEDs): 69, 72, 75, 78, 82, 85, 89, 93
// Total side LEDs: 16

// Array of side LED indices for easy iteration
#define SIDE_LED_LEFT {68, 71, 74, 77, 81, 84, 88, 92}
#define SIDE_LED_RIGHT {69, 72, 75, 78, 82, 85, 89, 93}
#define SIDE_LED_COUNT 8

// LED Color definitions for ledmap (using custom prefix to avoid conflicts)
#define LED_OFF____ {0, 0, 0}
#define LED_RED____ {255, 0, 0}
#define LED_GREEN__ {0, 255, 0}
#define LED_BLUE___ {0, 0, 255}
#define LED_YELLOW_ {255, 255, 0}
#define LED_CYAN___ {0, 255, 255}
#define LED_MAGENTA {255, 0, 255}
#define LED_WHITE__ {255, 255, 255}
#define LED_ORANGE_ {255, 165, 0}
#define LED_GOLD___ {255, 215, 0}
#define LED_PURPLE_ {128, 0, 128}
#define LED_PINK___ {255, 192, 203}

// Placeholder for "no change" or "use default"
#define ______ LED_OFF

// Ledmap structure: array of RGB values for each LED
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} ledmap;

// RGB Matrix Layout Macro
// Maps visual keyboard layout to LED indices
// Based on GMMK Pro Rev1 ISO LED mapping
#define RGB_MATRIX_LAYOUT_LEDMAP(lu1, ru1, lu2, k00, k06, k12, k18, k23, k28, k34, k39, k44, k50, k56, k61, k66, k70, k73, ru2, lu3, k01, k07, k13, k19, k24, k29, k35, k40, k45, k51, k57, k62, k79, k86, k76, ru3, lu4, k02, k08, k14, k20, k25, k30, k36, k41, k46, k52, k58, k63, k90, ru4, lu5, k03, k09, k15, k21, k26, k31, k37, k42, k47, k53, k59, k64, k95, k97, k87, ru5, lu6, k04, k67, k10, k16, k22, k27, k32, k38, k43, k48, k54, k60, k91, k94, k83, ru6, lu7, k05, k11, k17, k33, k49, k55, k65, k96, k98, k80, ru7, lu8, ru8) \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k60, k61, k62, k63, k64, k65, k66, k67, lu1, ru1, k70, lu2, ru2, k73, lu3, ru3, k76, lu4, ru4, k79, k80, lu5, ru5, k83, lu6, ru6, k86, k87, lu7, ru7, k90, k91, lu8, ru8, k94, k95, k96, k97, k98}
