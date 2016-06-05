// Phantom ANSI
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 0: QWERTY */
    KEYMAP_ANSI(\
        ESC,          F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12,       PSCR, SLCK, BRK,  \
        GRV,     1,    2,    3,    4,    5,    6,    7,    8,    9,    0, MINS,  EQL, BSPC,        INS, HOME, PGUP, \
        TAB,     Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P, LBRC, RBRC, BSLS,        DEL,  END, PGDN, \
        LCTL,    A,    S,    D,    F,    G,    H,    J,    K,    L, SCLN, QUOT,        ENT,                         \
        LSFT,    Z,    X,    C,    V,    B,    N,    M, COMM,  DOT, SLSH,             RSFT,               UP,       \
        LCTL, LALT, LGUI,                    SPC,             RGUI, RALT,  FN0, RCTL,             LEFT, DOWN, RGHT),

    /* 0: FN0 Layer */
    KEYMAP_ANSI(\
       //ESC,         F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12,       PSCR, SLCK, BRK,  \
        TRNS,       TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS, \
       //GRV,    1,    2,    3,    4,    5,    6,    7,    8,    9,    0, MINS,  EQL, BSPC,        INS, HOME, PGUP, \
        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS, \
       //TAB,    Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P, LBRC, RBRC, BSLS,        DEL,  END, PGDN, \
        TRNS,    7,    8,    9, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS, \
      //LCTL,    A,    S,    D,    F,    G,    H,    J,    K,    L, SCLN, QUOT,        ENT,                         \
        TRNS,    4,    5,    6,  DOT, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS,                         \
      //LSFT,    Z,    X,    C,    V,    B,    N,    M, COMM,  DOT, SLSH,             RSFT,               UP,       \
        TRNS,    1,    2,    3,    0,  ENT, TRNS, TRNS, TRNS, TRNS, TRNS,             TRNS,             TRNS,       \
      //LCTL, LALT, LGUI,                    SPC,             RGUI, RALT,  FN0, RCTL,             LEFT, DOWN, RGHT  \
        TRNS, TRNS, TRNS,                   TRNS,             TRNS, TRNS, TRNS, TRNS,             TRNS, TRNS, TRNS)

    /* 0: FN1 Layer
    KEYMAP_ANSI(\
        TRNS,      TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,      TRNS,TRNS,SLEP, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,MUTE,VOLD,VOLU,TRNS,      TRNS,TRNS,TRNS, \
        TRNS,   1,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,MSTP,MPLY,MPRV,MNXT,MSEL,      TRNS,TRNS,TRNS, \
        TRNS,   4,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,                      \
        TRNS,     TRNS,TRNS,CALC,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,           TRNS,      \
        TRNS,TRNS,TRNS,               TRNS,               TRNS,TRNS,TRNS,TRNS,      TRNS,TRNS,TRNS)
     */
};
static const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1)
};
