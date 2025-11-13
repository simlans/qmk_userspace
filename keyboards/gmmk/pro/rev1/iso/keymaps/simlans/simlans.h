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
