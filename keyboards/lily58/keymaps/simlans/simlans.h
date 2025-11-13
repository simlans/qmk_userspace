#pragma once
#include QMK_KEYBOARD_H
#include "keymap_german.h"

// NEO_3 special characters
#define L58_SYM_CAPITAL_SS           RSA(DE_S)                   // ẞ
#define L58_SYM_CAPITAL_UE           S(DE_UDIA)                  // Ü
#define L58_SYM_CAPITAL_OE           S(DE_ODIA)                  // Ö
#define L58_SYM_CAPITAL_AE           S(DE_ADIA)                  // Ä
#define L58_SYM_SUPS_1               ALGR(DE_1)                  // ¹
#define L58_SYM_SUPS_2               DE_SUP2                     // ²
#define L58_SYM_SUPS_3               DE_SUP3                     // ³
#define L58_SYM_RSAQUO               RSA(DE_Y)                   // ›
#define L58_SYM_LSAQUO               RSA(DE_X)                   // ‹
#define L58_SYM_SBQUO                RSA(DE_V)                   // ‚
#define L58_SYM_LSQ                  RSA(DE_B)                   // ‘
#define L58_SYM_RSQ                  RSA(DE_N)                   // ’
#define L58_SYM_ELLIPSIS             ALGR(DE_DOT)                // …
#define L58_SYM_UNDERSCORE           DE_UNDS                     // _
#define L58_SYM_LBRACKET             DE_LBRC                     // [
#define L58_SYM_RBRACKET             DE_RBRC                     // ]
#define L58_SYM_CIRCUMFLEX           DE_CIRC                     // ^
#define L58_SYM_EXCLAMATION          DE_EXLM                     // !
#define L58_SYM_LESSTHAN             DE_LABK                     // <
#define L58_SYM_GREATERTHAN          DE_RABK                     // >
#define L58_SYM_EQUAL                DE_EQL                      // =
#define L58_SYM_AMPERSAND            DE_AMPR                     // &
#define L58_SYM_BSLASH               DE_BSLS                     // (backslash)
#define L58_SYM_SLASH                DE_SLSH                     // /
#define L58_SYM_CLBRACKET            DE_LCBR                     // {
#define L58_SYM_CRBRACKET            DE_RCBR                     // }
#define L58_SYM_ASTERISK             DE_ASTR                     // *
#define L58_SYM_QUESTIONMARK         DE_QUES                     // ?
#define L58_SYM_LPARENTHESES         DE_LPRN                     // (
#define L58_SYM_RPARENTHESES         DE_RPRN                     // )
#define L58_SYM_HYPHEN_MINUS         DE_MINS                     // -
#define L58_SYM_COLON                DE_COLN                     // :
#define L58_SYM_AT                   DE_AT                       // @
#define L58_SYM_HASH                 DE_HASH                     // #
#define L58_SYM_PIPE                 DE_PIPE                     // |
#define L58_SYM_TILDE                DE_TILD                     // ~
#define L58_SYM_BACKTICK             DE_GRV                      // `
#define L58_SYM_PLUS                 DE_PLUS                     // +
#define L58_SYM_PERCENT              DE_PERC                     // %
#define L58_SYM_DOUBLE_QUOTE         DE_DQUO                     // "
#define L58_SYM_SINGLE_QUOTE         DE_QUOT                     // '
#define L58_SYM_SEMICOLON            DE_SCLN                     // ;
#define L58_SYM_MIDDLE_DOT           ALGR(DE_COMM)               // ·
#define L58_SYM_DOLLAR               DE_DLR                      // $

#define L58_SYM_SUPS_1               ALGR(DE_1)                  // ¹
#define L58_SYM_SUPS_2               DE_SUP2                     // ²
#define L58_SYM_SUPS_3               DE_SUP3                     // ³
#define L58_SYM_SBQUO_MAC            A(KC_S)
#define L58_SYM_LSQ_MAC              A(KC_NUHS)
#define L58_SYM_RSQ_MAC              S(A(KC_NUHS))
#define L58_SYM_LBRACKET_MAC         A(KC_5)
#define L58_SYM_RBRACKET_MAC         A(KC_6)
#define L58_SYM_CIRCUMFLEX_MAC       KC_NUBS
#define L58_SYM_LESSTHAN_MAC         KC_GRV
#define L58_SYM_GREATERTHAN_MAC      S(KC_GRV)
#define L58_SYM_BSLASH_MAC           S(A(KC_7))
#define L58_SYM_SLASH_MAC            S(KC_7)
#define L58_SYM_CLBRACKET_MAC        A(KC_8)
#define L58_SYM_CRBRACKET_MAC        A(KC_9)
#define L58_SYM_AT_MAC               A(KC_L)
#define L58_SYM_PIPE_MAC             A(KC_7)
#define L58_SYM_TILDE_MAC            A(KC_N)

enum custom_keycodes {
    CKC_SYM = SAFE_RANGE,
};