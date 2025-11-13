# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a QMK Userspace repository for maintaining custom keyboard firmware keymaps outside the main QMK repository. It contains keymaps for:
- lily58 (split keyboard)
- gmmk/pro/rev1/iso (full-size keyboard)

## Setup Requirements

Before working with this repository:
1. Ensure QMK is installed and configured (`qmk setup`)
2. Configure userspace overlay: `qmk config user.overlay_dir="$(realpath .)"`
3. Build targets are defined in `qmk.json`

## Build Commands

### Compile All Userspace Targets
```bash
qmk userspace-compile
```
This builds all keyboards/keymaps defined in `qmk.json`.

### Compile Single Keyboard
```bash
qmk compile -kb <keyboard> -km <keymap>
# Example:
qmk compile -kb lily58 -km simlans
qmk compile -kb gmmk/pro/rev1/iso -km simlans
```

### Using Make (Alternative)
```bash
make <keyboard>:<keymap>
# Example:
make lily58:simlans
make gmmk/pro/rev1/iso:simlans
```

### Managing Build Targets
```bash
# Add a keyboard/keymap to qmk.json
qmk userspace-add -kb <keyboard> -km <keymap>

# Remove a keyboard/keymap from qmk.json
qmk userspace-remove -kb <keyboard> -km <keymap>

# List current build targets
qmk userspace-list
```

### Create New Keymap
```bash
qmk new-keymap -kb <keyboard> -km <keymap_name>
```

## Repository Structure

```
qmk_userspace/
├── keyboards/          # Keyboard-specific keymaps
│   ├── lily58/
│   │   └── keymaps/
│   │       └── simlans/
│   │           ├── keymap.c         # Main keymap definition
│   │           ├── simlans.h   # Custom keycodes/macros
│   │           ├── config.h         # Keymap configuration
│   │           └── rules.mk         # Feature flags
│   └── gmmk/
│       └── pro/
│           └── rev1/
│               └── iso/
│                   └── keymaps/
│                       └── simlans/
├── layouts/           # Layout-based keymaps (currently unused)
├── users/             # Shared user code (currently unused)
├── qmk.json          # Build target definitions
└── Makefile          # Forwards make commands to qmk_firmware
```

## Keymap Architecture

### File Structure
Each keymap consists of:
- **keymap.c**: Main keymap implementation with layer definitions
- **config.h**: Keyboard-specific configuration (tapping terms, RGB settings, etc.)
- **rules.mk**: Feature toggles (OLED, encoders, RGB, etc.)
- **[optional] .h file**: Custom keycodes, macros, and OS-specific symbol definitions

### Key Concepts

**German Layout**: The lily58 keymap uses `keymap_german.h` and includes extensive German special character definitions (umlauts, typographic quotes, etc.) with both Linux/Windows and macOS variants.

**OS Detection**: Both keymaps use `OS_DETECTION_ENABLE = yes` in rules.mk to detect the host OS and adjust behavior accordingly.

**Custom Keycodes**: Defined in header files (e.g., `simlans.h`) starting from `SAFE_RANGE` to avoid conflicts with QMK built-ins.

**Feature Configuration**:
- lily58 has OLED display enabled with custom library sources in rules.mk (referenced but not present in repo)
- gmmk/pro has rotary encoder support via `ENCODER_MAP_ENABLE`

## Common Development Patterns

### Adding New Keycodes
1. Define in the keymap's header file (e.g., `simlans.h`) in the `custom_keycodes` enum
2. Implement behavior in `process_record_user()` in keymap.c
3. Use in layer definitions

### Modifying Features
1. Edit `rules.mk` to enable/disable features
2. Edit `config.h` for feature-specific settings
3. Recompile with `qmk compile` or `qmk userspace-compile`

### OS-Specific Symbols
The lily58 keymap demonstrates a pattern for OS-specific symbols:
- Define base symbols using German keymap codes
- Define macOS variants with `_MAC` suffix
- Switch between them in keymap.c based on OS detection

## GitHub Actions

Firmware builds automatically on push via `.github/workflows/build_binaries.yaml`:
- Uses QMK's official userspace build workflow
- Builds against `qmk/qmk_firmware:master`
- Publishes firmware binaries to Releases tab

## Output Files

Compiled firmware appears in the root directory:
- `.bin` files for ARM-based keyboards (e.g., gmmk_pro_rev1_iso_simlans.bin)
- `.hex` files for AVR-based keyboards (e.g., lily58_rev1_simlans.hex)

These files can be flashed directly to keyboards using QMK Toolbox or similar tools.
