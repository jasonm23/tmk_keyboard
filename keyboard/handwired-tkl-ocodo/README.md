Ocodo hardwired keyboard firmware
======================

Handwired matrix keyboard made by ocodo

Build
-----
Move to this directory then just run `make` like:

    $ make -f Makefile.pjrc ansi

Keymap
------
The firmware supports multiple physical layouts.
Each layout have their own keymap file.

*Note that only the ANSI keymap is tested on actual hardware.*

To customize a keymap:

1. Edit the file that corresponds to your layout.
2. Specify your layout when building.

See [keymap.c](keymap.c) to define your own custom layout.

### 1. ANSI
This is the default keymap.

See [keymap_ansi.h](keymap_ansi.h) for detail.

#### 1.0. ANSI Default Layer
     ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
     `---'   `---------------' `---------------' `---------------' `-----------'
     ,-----------------------------------------------------------. ,-----------.
     |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | |Ins|Hom|PgU|
     |-----------------------------------------------------------| |-----------|
     |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD|
     |-----------------------------------------------------------| '-----------'
     |Fn0   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
     |-----------------------------------------------------------|     ,---.
     |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |     |Up |
     |-----------------------------------------------------------| ,-----------.
     |Ctl|Gui|Alt|             Space             |Alt|Gui|App|Ctl| |Lef|Dow|Rig|
     `-----------------------------------------------------------' `-----------'

#### 1.1. ANSI layer 1
     ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     |   |   |   |   |   |   | |   |   |   |   | |   |   |   |   | |   |   |Slp|
     `---'   `---------------' `---------------' `---------------' `-----------'
     ,-----------------------------------------------------------. ,-----------.
     |   |   |   |   |   |   |   |   |   |   |Mut|V- |V+ |       | |   |   |   |
     |-----------------------------------------------------------| |-----------|
     |     |   |   |   |   |   |   |   |   |Stp|Ply|Prv|Nxt|Media| |   |   |   |
     |-----------------------------------------------------------| '-----------'
     |      |   |   |   |   |   |   |   |   |   |   |   |        |
     |-----------------------------------------------------------|     ,---.
     |        |   |   |Clc|   |   |   |   |   |   |   |Caps      |     |   |
     |-----------------------------------------------------------| ,-----------.
     |   |   |   |                               |   |   |   |   | |   |   |   |
     `-----------------------------------------------------------' `-----------'
