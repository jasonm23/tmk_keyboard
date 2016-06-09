/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
extern "C" {
#include "led.h"
#include "print.h"
#include "debug.h"
#include "timer.h"
#include "util.h"
#include "matrix.h"
} //  extern "C"
#include "TeensyPin.hpp"

//#define DBG_KEYPRESS
//#define DBG_SPEED

static void debounce_key( uint8_t i, uint8_t j, bool isUp );
static void dbg_scan_speed();

static TeensyPin s_rowPins[MATRIX_ROWS] = {
  TPIN(D,0), // row 0
  TPIN(B,7), // row 1
  TPIN(B,3), // row 2
  TPIN(B,2), // row 3
  TPIN(B,1), // row 4
  TPIN(B,0), // row 5
};

static TeensyPin s_colPins[MATRIX_COLS] = {
  TPIN(D,4), // col 00
  TPIN(D,6), // col 01
  TPIN(D,7), // col 02
  TPIN(B,4), // col 03
  TPIN(B,5), // col 04
  TPIN(B,6), // col 05
  TPIN(F,7), // col 06
  TPIN(F,6), // col 07
  TPIN(F,5), // col 08
  TPIN(F,4), // col 09
  TPIN(F,1), // col 10
  TPIN(D,5), // col 11
  TPIN(C,7), // col 12
  TPIN(C,6), // col 13
  TPIN(D,3), // col 14
  TPIN(D,2), // col 15
  TPIN(D,1), // col 16
};

// Keyboard matrix state (0 = up, 1 = down)
static matrix_row_t s_matrix[MATRIX_ROWS];

// Key history for debouncing.  Each key has 8 bits which are the last
// 8 readings from the ky.  (0 = down, 1 = up)
static uint8_t s_debounce[MATRIX_ROWS][MATRIX_COLS];

extern "C" {
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (s_matrix[row] & ((matrix_row_t)1<<col));
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return s_matrix[row];
}

void led_set(uint8_t led)
{
}

void matrix_init(void)
{
    // Initialize row and column pins.
    for ( uint8_t i = 0; i < MATRIX_ROWS; i++ )
    {
       s_rowPins[i].output();
       s_rowPins[i].high();
    }
    for ( uint8_t i = 0; i < MATRIX_COLS; i++ )
    {
       s_colPins[i].input_pullup();
    }

    // Initialize the matrix state: all keys are off
    for ( uint8_t i=0; i < MATRIX_ROWS; i++ )
    {
        s_matrix[i] = 0;

        for ( uint8_t j = 0; j < MATRIX_COLS; j++ )
        {
           // 1 = key up
           s_debounce[i][j] = 0xff;
        }
    }
}

uint8_t matrix_scan(void)
{
    // Loop over the rows and energize each pin one at a time.
    for ( uint8_t i = 0; i < MATRIX_ROWS; i++ )
    {
        s_rowPins[i].low();

        // Delay long enough for the matrix to settle.
        _delay_us(3);

        // Loop over each column and see if any keys are down.
        for ( uint8_t j = 0; j < MATRIX_COLS; j++ )
        {
            // 0 == key pressed (low), 1 == key not pressed (high)
            bool isUp = s_colPins[j].read();

            debounce_key( i, j, isUp );
        }

        // Remove current from the row.
        s_rowPins[i].high();
    }

#ifdef DBG_SPEED
    dbg_scan_speed();
#endif // DBG_SPEED

    // If you really want the debounce algorithm to be 5 ms, then
    // fiddle with this (using DBG_SPEED) until you get roughly 1000
    // calls / 1000 msec.
    //_delay_us( 180 ); // delay to get 1 msec/scan
    return 1;
}

void matrix_print(void)
{
    xprintf("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row);
        xprintf(": ");
        pbin_reverse16(s_matrix[row]);
        xprintf("\n");
    }
}

} // extern "C"

static void debounce_key( uint8_t i, uint8_t j, bool isUp )
{
   // Shift a 0 into the history buffer if the key is down or
   // 1 if it's up.
   s_debounce[i][j] = ( s_debounce[i][j] << 1 ) | isUp;

   // Mask w/ one more bit than the number of consecutive
   // states we're debouncing with (5 in this case).
   uint8_t v = s_debounce[i][j] & 0b00111111;

   // If the key was up (1) followed by 5 consecutive scans w/
   // the key down (0), then mark the key as pressed.
   //if ( v == 0b111110 ) fire on the first press...
   if ( v == 0b100000 ) // wait 5
   {
#ifdef DBG_KEYPRESS
      xprintf( "Key DOWN : Row=%d Col=%d\n", i, j );
#endif // DBG_KEYPRESS
      BIT_SET( s_matrix[i], j );
   }
   // If the key was down (0) followed by 5 consecutive scans
   // w/ the key up (1), then mark the key as not pressed.
   else if ( v == 0b011111 )
   {
#ifdef DBG_KEYPRESS
      xprintf( "Key UP   : Row=%d Col=%d\n", i, j );
#endif // DBG_KEYPRESS
      BIT_CLEAR( s_matrix[i], j );
   }
}


static void
dbg_scan_speed()
{
#  define NUM_SAMPLE 2000
   static uint16_t s_startup = 0;
   if ( s_startup < NUM_SAMPLE )
   {
      static uint32_t s_timer = 0;
      if ( s_startup == 0 )
      {
         s_timer = timer_read32();
      }

      if ( ++s_startup == NUM_SAMPLE )
      {
         uint32_t t = timer_read32();
         uint32_t dt = t - s_timer;
         xprintf( "Num calls: %d\n", NUM_SAMPLE );
         xprintf( "Time     : %d ms\n", dt );
         xprintf( "Goal     : %d ms\n", NUM_SAMPLE );
         if ( abs( dt - NUM_SAMPLE ) < 20 )
         {
            xprintf( "Delay    : GOOD\n" );
         }
         else
         {
            uint32_t delay_usec =  (NUM_SAMPLE - dt) * 1000 / NUM_SAMPLE;
            xprintf( "Set delay: %d usec\n", delay_usec );
         }
      }
   }
}
