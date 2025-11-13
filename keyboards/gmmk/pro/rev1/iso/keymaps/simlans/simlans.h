#pragma once
#include QMK_KEYBOARD_H

enum layer_number {
  WIN_LAYER_DEF_LAYER = 0,
  MACOS_LAYER,
  FN_LAYER,
};

// RGB Matrix Colors (HSV: Hue, Saturation, Value)
// Hue: 0-255 color wheel position
// Saturation: 0-255 color intensity (0=white, 255=full color)
// Value: 0-255 brightness (0=off, 255=max brightness)

#define HSV_OS_MACOS   0,   0,   255  // macOS/iOS: White
#define HSV_OS_WINDOWS 170, 255, 255  // Windows: Blue
#define HSV_OS_LINUX   28,  255, 255  // Linux: Orange
#define HSV_OS_UNSURE  0,   255, 255  // Unknown OS: Red

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
#define SIDE_LED_LEFT  {68, 71, 74, 77, 81, 84, 88, 92}
#define SIDE_LED_RIGHT {69, 72, 75, 78, 82, 85, 89, 93}
#define SIDE_LED_COUNT  8
