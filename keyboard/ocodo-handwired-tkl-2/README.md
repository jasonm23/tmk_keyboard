# KUL ES87 recovery - becomes hand wired TKL

Are you sitting comfortably? Then I'll begin...

During a key switch swap I managed to damage the PCB on a
[KUL-ES87](http://www.keyeduplabs.com/es-87.html).  Rather than simply
repair the PCB. I decided I'd just get a
[Teensy 2.0](https://www.pjrc.com/store/teensy.html) flash it with
[TMK firmware](https://github.com/tmk/tmk_keyboard), handwire the new
switches, and remove the PCB entirely.

I have another 2 KULs with their PCBs intact, one with factory fitted
[Cherry MX Clears](https://deskthority.net/wiki/Cherry_MX_Clear) the
other with
[Purple Zealios (67g)](https://zealpc.net/products/zealio). This hand
wired board feels and sounds practically the same as the one with the
PCB and factory fitted MX Clears, so I was pretty happy with how this
turned out.

On the downside, I'm not particularly proud of my wiring job. I had to
butcher the case internally to free up enough space for everything to
fit.

To give myself some flexibility I wired the Teensy 2.0 with 90 degree
header pins, the column and row jumper wires had sockets to connect
with the header pins (at the teensy end.) I connected the USB socket
board to the teensy via a stripped down mini USB connector. All that
took up a lot of space, and I didn't route the wires smartly.  I
managed to secure the teensy with some insulation tape and stuff the
rest inside. I think maybe it's the rats nest of wiring which help
dampen the acoustics of the board, there's no discernible ping, and to
be honest I'd expected plenty of ping with a plastic housing and
stainless steel plate.

The biggest issue I face was a couple of switches that didn't have
good clips.  It's well known in the mechanical keyboard community that
MX Clears with tight key caps is a recipe for disaster. They a very
difficult to remove and in some cases the switches themselves will
break open.

With these poorly mounted switches, pulling the caps off didn't go
well at all. They popped right out of the plate and tore out their diodes
and wiring. One of them lost one of it's pins, so I had to completely
replace it. Not fun.

I bought a hot-glue gun off Ebay for $10 with 50 free hot glue sticks.
(I later realised I could get one in a store locally for $7, but the
free glue sticks still just about made it a better deal online.  I did
have to wait a week or so for it to show up.)  Thankfully the hot glue
worked a treat! There'll be no more problems replacing key caps now,
hopefully!

Now that it's all done and dusted, I'll probably convert from TMK to
the QMK firmare in a little while. My Phantom TKL board is already on
QMK and it's extra features are great (one shot modifiers, leader key
... etc.)

Here's the finished board (I wrote this overly long preamble with it.)

http://i.imgur.com/Ae6qcAD.jpg


### TMK Firmware - Keymap

Plain QWERTY for Mac OSX (Alt / GUI swapped) and Caps as Left Ctl

    ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
    │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PrS│ScL│Pau│
    └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
    ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
    │~  │  1│  2│  3│  4│  5│  6│  7│  8│  9│  0│  -│  =│Backsp │ │Ins│Hom│PgU│
    ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
    │Tab  │  Q│  W│  E│  R│  T│  Y│  U│  I│  O│  P│  [│  ]│    \│ │Del│End│PgD│
    ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
    │Ctl   │  A│  S│  D│  F│  G│  H│  J│  K│  L│  ;│  '│Return  │
    ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
    │Shift   │  Z│  X│  C│  V│  B│  N│  M│  ,│  .│  /│Shift     │     │Up │
    ├───┬───┬┴──┬┴───┴───┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┬───┤ ┌───┼───┼───┐
    │Ctl│Alt│Gui│               Space           │Alt│Gui│FN0│Ctl│ │Lef│Dow│Rig│
    └───┴───┴───┴───────────────────────────────┴───┴───┴───┴───┘ └───┴───┴───┘


App/Menu key (FN0) press and hold for **Layer 1** - here we have
programming, entry features. Numpad keys on left hand (sending numpad
codes, see the layout map below). A-F for hex entry on keys 1-6.

Caps lock is available and mapped in it's standard position.

App is on Right Ctrl.

Media keys are mapped as

    ┌───────────────────────────────────────────────────┐
    │ F7   │ F8         │ F9   │ F10  │ F11    │ F12    │
    │ PREV │ PLAY/PAUSE │ NEXT │ MUTE │ VOL DN │ VOL UP │
    └───────────────────────────────────────────────────┘


Full **Layer 1** layout here:

    ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
    │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │PRV│PLY│ │NXT│MTE│VDN│VUP│ │PrS│ScL│Pau│
    └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
    ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐
    │~  │  A│  B│  C│  D│  E│  F│  7│  8│  9│  0│  -│  =│Backsp │ │Ins│Hom│PgU│
    ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤
    │Tab  │  7│  8│  9│  +│  -│  Y│  U│  I│  O│  P│  [│  ]│    \│ │Del│End│PgD│
    ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘
    │Caps  │  4│  5│  6│  /│  *│  H│  J│  K│  L│  ;│  '│Return  │
    ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
    │Shift   │  1│  2│  3│  0│  .│  N│  M│  ,│  .│  /│Shift     │     │Up │
    ├───┬───┬┴──┬┴───┴───┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬───┬───┤ ┌───┼───┼───┐
    │Ctl│Alt│Ent│               Space           │Alt│Gui│FN0│App│ │Lef│Dow│Rig│
    └───┴───┴───┴───────────────────────────────┴───┴───┴───┴───┘ └───┴───┴───┘
