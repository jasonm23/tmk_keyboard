/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "bootloader.h"
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"


// Convert physical keyboard layout to matrix array.
// This is a macro to define keymap easily in keyboard layout form.
#define KEYMAP( \
  /* Left hand */ \
       K01, K02, K03, K04, K05, K06, \
  K10, K11, K12, K13, K14, K15, K16, \
  K20, K21, K22, K23, K24, K25, K26, \
  K30, K31, K32, K33, K34, K35, K36, K37, \
  K40, K41, K42, K43, K44, K45, K46, K47, \
  K50, K51, K52, K53, K54, K55, K56, K57, \
  /* Right hand */ \
       K09, K0A, K0B, K0C, K0D, K0E, \
       K19, K1A, K1B, K1C, K1D, K1E, K1F, \
       K29, K2A, K2B, K2C, K2D, K2E, K2F, \
  K38, K39, K3A, K3B, K3C, K3D, K3E, K3F, \
  K48, K49, K4A, K4B, K4C, K4D, K4E, K4F, \
  K58, K59, K5A, K5B, K5C, K5D, K5E, K5F \
) { \
{ KC_NO,   KC_##K01,KC_##K02,KC_##K03,KC_##K04,KC_##K05,KC_##K06,KC_NO, \
  KC_NO,   KC_##K09,KC_##K0A,KC_##K0B,KC_##K0C,KC_##K0D,KC_##K0E,KC_NO }, \
{ KC_##K10,KC_##K11,KC_##K12,KC_##K13,KC_##K14,KC_##K15,KC_##K16,KC_NO, \
  KC_NO,   KC_##K19,KC_##K1A,KC_##K1B,KC_##K1C,KC_##K1D,KC_##K1E,KC_##K1F }, \
{ KC_##K20,KC_##K21,KC_##K22,KC_##K23,KC_##K24,KC_##K25,KC_##K26,KC_NO, \
  KC_NO,   KC_##K29,KC_##K2A,KC_##K2B,KC_##K2C,KC_##K2D,KC_##K2E,KC_##K2F }, \
{ KC_##K30,KC_##K31,KC_##K32,KC_##K33,KC_##K34,KC_##K35,KC_##K36,KC_##K37, \
  KC_##K38,KC_##K39,KC_##K3A,KC_##K3B,KC_##K3C,KC_##K3D,KC_##K3E,KC_##K3F }, \
{ KC_##K40,KC_##K41,KC_##K42,KC_##K43,KC_##K44,KC_##K45,KC_##K46,KC_##K47, \
  KC_##K48,KC_##K49,KC_##K4A,KC_##K4B,KC_##K4C,KC_##K4D,KC_##K4E,KC_##K4F }, \
{ KC_##K50,KC_##K51,KC_##K52,KC_##K53,KC_##K54,KC_##K55,KC_##K56,KC_##K57, \
  KC_##K58,KC_##K59,KC_##K5A,KC_##K5B,KC_##K5C,KC_##K5D,KC_##K5E,KC_##K5F }, \
}

#define KEYCODE(layer, row, col) \
   (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))

enum Function_id {
   BOOTLOADER,
};

// Assign Fn key functions.
static const uint16_t PROGMEM fn_actions[] = {
   [0] = ACTION_FUNCTION_TAP(BOOTLOADER), // FN5 Teensy bootloader
   // Function keys
   [1] = ACTION_LAYER_MOMENTARY(1), // Left Fn layer toggle
   [2] = ACTION_LAYER_MOMENTARY(2), // Right Fn layer toggle
   // Macros
   [3] = ACTION_MODS_KEY(MOD_RCTL | MOD_RALT, KC_DELETE), // FN4 ctrl alt delete
   [4] = 0,
   [5] = 0,
   [6] = 0,
   [7] = 0,
   [8] = 0,
   [9] = ACTION_MODS_KEY(MOD_LCTL, KC_BSPC), // ctrl-backspace del back word
   [10] = ACTION_MODS_KEY(MOD_LCTL, KC_DEL), // ctrl-delete del fwd word
   [11] = ACTION_MODS_KEY(MOD_LCTL, KC_K), // ctrl-k delete to end of line
   [12] = ACTION_MODS_KEY(MOD_LCTL, KC_HOME), // ctrl-beg cursor doc beg
   [13] = ACTION_MODS_KEY(MOD_LCTL, KC_END), // ctrl-end cursor doc end
   // Standard cursor movement keys
   [14] = ACTION_MODS_KEY(MOD_LCTL, KC_LEFT), // ctrl-left cursor backward word
   [15] = ACTION_MODS_KEY(MOD_LCTL, KC_RGHT), // ctrl-right cursor forward word
   // Fast access to shifted characters
   [16] = ACTION_MODS_KEY(MOD_LSFT, KC_GRV), // ~
   [17] = ACTION_MODS_KEY(MOD_LSFT, KC_1), // !
   [18] = ACTION_MODS_KEY(MOD_LSFT, KC_2), // @
   [19] = ACTION_MODS_KEY(MOD_LSFT, KC_3), // #
   [20] = ACTION_MODS_KEY(MOD_LSFT, KC_4), // $
   [21] = ACTION_MODS_KEY(MOD_LSFT, KC_5), // %
   [22] = ACTION_MODS_KEY(MOD_LSFT, KC_6), // ^
   [23] = ACTION_MODS_KEY(MOD_LSFT, KC_7), // &
   [24] = ACTION_MODS_KEY(MOD_LSFT, KC_8), // *
   [25] = ACTION_MODS_KEY(MOD_LSFT, KC_9), // (
   [26] = ACTION_MODS_KEY(MOD_LSFT, KC_0), // )
   [27] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS), // _
   [28] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL), // +
   [29] = ACTION_MODS_KEY(MOD_LSFT, KC_LBRC), // {
   [30] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRC), // }
   [31] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS), // back slash
};

// Short keymap names to use instead of FN##
#define KC_BOOT KC_FN0 // boot loader

#define KC_LFN  KC_FN1  // Left hyper key
#define KC_RFN  KC_FN2  // Right hyper key

#define KC_CADL KC_FN3  // ctrl-alt-delte

#define KC_DBWD KC_FN9  // Delete backward word
#define KC_DFWD KC_FN10 // Delete forward word
#define KC_DLIN KC_FN11 // Delete to end of line
#define KC_CBEG KC_FN12 // Cursor to document beg
#define KC_CEND KC_FN13 // Cursor to document end
#define KC_CBWD KC_FN14 // Cursor backward word
#define KC_CFWD KC_FN15 // Cursor forward word

#define KC_TILD KC_FN16 // shift ` = ~
#define KC_BANG KC_FN17 // shift 1 = !
#define KC_AT   KC_FN18 // @
#define KC_HASH KC_FN19 // #
#define KC_DOLR KC_FN20 // $
#define KC_PCT  KC_FN21 // %
#define KC_CART KC_FN22 // ^
#define KC_AND  KC_FN23 // &
#define KC_STAR KC_FN24 // *
#define KC_LPAR KC_FN25 // (
#define KC_RPAR KC_FN26 // )
#define KC_UNDR KC_FN27 // _
#define KC_PLUS KC_FN28 // +
#define KC_LBRA KC_FN29 // {
#define KC_RBRA KC_FN30 // }
#define KC_PIPE KC_FN31 // |

/*
#define KC_CADL KC_FN4    // Ctrl Alt Delete macro
#define KC_BOOT KC_FN5    // Jump to teensy bootloader
#define KC_DBWD KC_FN12   // Emacs backward delete word
#define KC_DFWD KC_FN13   // Emacs forward delete word
#define KC_DLIN KC_FN14   // Emacs delete to end of line
*/

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   /* Layer 0: Default Layer */
   KEYMAP( \
          /* Left hand */
                F1,   F2,   F3,   F4,   F5,   F6, \
          MUTE, GRV,  1,    2,    3,    4,    5, \
          PSCR, TAB,  Q,    W,    E,    R,    T, \
          ESC,  LCTL, A,    S,    D,    F,    G,    BSLS, \
          PGUP, LSFT, Z,    X,    C,    V,    B,    DEL, \
          PGDN, HOME, END,  TAB,  LALT, LFN,  SPC,  BSPC,   \
                /* Right hand */
                      F7,   F8,   F9,   F10,  F11,  F12, \
                      6,    7,    8,    9,    0,    VOLD, VOLU, \
                      Y,    U,    I,    O,    P,    LBRC, RBRC, \
                EQL,  H,    J,    K,    L,    SCLN, QUOT, ENT, \
                MINS, N,    M,    COMM, DOT,  SLSH, RSFT, UP, \
                ENT,  SPC,  RFN,  RALT, RCTL, LEFT, DOWN, RGHT \
                ),

   /* Layer 1: Left Fn */
   KEYMAP( \
          /* Left hand */
                TRNS, TRNS, TRNS, TRNS, TRNS, NO, \
          NO,   TRNS, F1,   F2,   F3,   F4,   F4, \
          SLCK, TRNS, CBEG, CBWD, UP,   CFWD, PGUP, \
          NO,   NO,   HOME, LEFT, DOWN, RGHT, END,  AND, \
          NO,   CAPS, CEND, DBWD, DLIN, DFWD, PGDN, INS, \
          NO,   NO,   NO,   LGUI, NO,   TRNS, TRNS, TRNS, \
                /* Right hand */
                      CALC, NO,   NO,   NO,   NO,   NO, \
                      F6,   F7,   F8,   F9,   F10,  MPLY, MSTP, \
                      HASH, LBRA, RBRA, DOLR, PCT,  NO,   NO, \
                PLUS, STAR, LPAR, RPAR, CART, PIPE, GRV,  NO, \
                MINS, SLSH, LBRC, RBRC, AND,  AT,   NO,   NO, \
                TRNS, TRNS, TRNS, NO,   NO,   NO,   NO,   NO \
                ),

   /* Layer 2: Right Fn */
   KEYMAP( \
          /* Left hand */
                TRNS, TRNS, TRNS, TRNS, TRNS, NO, \
          BOOT, TRNS, F1,   F2,   F3,   F4,   F4, \
          BRK,  NO,   CBEG, CBWD, UP,   CFWD, PGUP, \
          NO,   NO,   HOME, LEFT, DOWN, RGHT, END,  AND, \
          NO,   CAPS, CEND, DBWD, DLIN, DFWD, PGDN, INS, \
          NO,   NO,   NO,   LGUI, NO,   TRNS, TRNS, TRNS, \
                /* Right hand */
                      CALC, NO,   NO,   NO,   NO,   NO, \
                      F6,   F7,   F8,   F9,   F10,  MPLY, MSTP, \
                      HASH, LBRA, RBRA, DOLR, PCT,  NO,   NO, \
                PLUS, STAR, LPAR, RPAR, CART, PIPE, GRV,  NO, \
                MINS, SLSH, LBRC, RBRC, AND,  AT,   NO,   PGUP, \
                TRNS, TRNS, TRNS, NO,   NO,   NO,   NO,   PGDN \
                ),
};


/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
   return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

/* translates Fn index to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
   action_t action;
   if (FN_INDEX(keycode) < sizeof(fn_actions) / sizeof(fn_actions[0])) {
      action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
   } else {
      action.code = ACTION_NO;
   }
   return action;
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
   //keyevent_t event = record->event;
   //tap_t tap = record->tap;

   switch (id) {
   case BOOTLOADER:
      //bootloader_jump();

      cli();
      // disable watchdog, if enabled
      // disable all peripherals
      UDCON = 1;
      USBCON = (1<<FRZCLK);  // disable USB
      UCSR1B = 0;
      _delay_ms(5);
      EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
      TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
      DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
      PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
      asm volatile("jmp 0x7E00");      
      break;
   }
}
