/*
Copyright 2013 TD22057

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
//(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <avr/io.h>

// Set the bit number 'bit' in the variable 'field' to 1.
#define BIT_SET( field, bit ) (field) |= ( 1 << bit )

// Set the bit number 'bit' in the variable 'field' to 0.
#define BIT_CLEAR( field, bit ) (field) &= ~( 1 << bit )

// Return the bit number 'bin' from the variable 'field'.
#define BIT_READ( field, bit ) (field) & ( 1 << bit )

// TeensyPin macro constructor.  Use this instead of the class
// constructor to build a TeensyPin object.  It will expand an input
// port letter (A,B,C,D,E,F) and number (0,1,2,3,5,6,7) into the three
// needed register (DDR##, PORT##, PIN##) variables.
//
// TeensyPin b2 = TPIN( B, 2 );
//
#define TPIN( letter, number ) \
   TeensyPin( &DDR##letter, &PORT##letter, &PIN##letter, number )

// Teensy pin encapsulation class.  This class stores the addresses of
// the three registers used to control a pin on a Teensy processor:
//     DDR:  pin direction: 0=input, 1=output
//     PORT: port control: output: 0=low, 1=high
//                         input: 0=normal, 1=pullup resistor
//     PIN:  read the pin
//
class TeensyPin
{
public:
   TeensyPin( volatile uint8_t* direction, volatile uint8_t* port,
              volatile uint8_t* address, uint8_t pin );

   // Initialize the pin mode.
   void input();
   void input_pullup();
   void output();

   // Input mode: 0 = low, 1 = high
   uint8_t read() const;

   // Output mode
   void high();
   void low();

private:
   // For an explanation on why the address of the port is stored, see
   // http://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_port_pass
   volatile uint8_t* m_direction;
   volatile uint8_t* m_port;
   volatile uint8_t* m_address;
   uint8_t m_pin;
};

inline
TeensyPin::
TeensyPin( volatile uint8_t* direction, volatile uint8_t* port,
           volatile uint8_t* address, uint8_t pin )
   : m_direction( direction ),
     m_port( port ),
     m_address( address ),
     m_pin( pin )
{
}

inline uint8_t
TeensyPin::
read() const
{
   return BIT_READ( *m_address, m_pin );
}

inline void
TeensyPin::
input()
{
   BIT_CLEAR( *m_direction, m_pin );
   BIT_CLEAR( *m_port, m_pin );
}

inline void
TeensyPin::
input_pullup()
{
   BIT_CLEAR( *m_direction, m_pin );
   BIT_SET( *m_port, m_pin );
}

inline void
TeensyPin::
output()
{
   BIT_SET( *m_direction, m_pin );
}

inline void
TeensyPin::
low()
{
   BIT_CLEAR( *m_port, m_pin );
}

inline void
TeensyPin::
high()
{
   BIT_SET( *m_port, m_pin );
}

