// Phantom ANSI
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: QWERTY */
    KEYMAP_ANSI(\
        ESC,          F1,   F2,       F3,          F4,   F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12,       PSCR, SLCK,  BRK, \
        GRV,     1,    2,    3,        4,           5,    6,    7,    8,    9,    0, MINS,  EQL, BSPC,        INS, HOME, PGUP, \
        TAB,     Q,    W,    E,        R,           T,    Y,    U,    I,    O,    P, LBRC, RBRC, BSLS,        DEL,  END, PGDN, \
        LCTL,    A,    S,    D,        F,           G,    H,    J,    K,    L, SCLN, QUOT,        ENT,                         \
        LSFT,          Z,    X,        C,           V,    B,    N,    M, COMM,  DOT, SLSH,       RSFT,               UP,       \
        LCTL, LALT, LGUI,                               SPC,                   RGUI, RALT,  FN0, RCTL,       LEFT, DOWN, RGHT),

    /* 0: FN0 Layer */
    KEYMAP_ANSI(\
        TRNS,       TRNS, TRNS,     TRNS,        TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS, \
        TRNS,    A,    B,    C,        D,           E,    F, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS, \
        TRNS, KP_7, KP_8, KP_9,  KP_PLUS,    KP_MINUS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS, \
        CAPS, KP_4, KP_5, KP_6, KP_SLASH, KP_ASTERISK, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, \
        TRNS, KP_1, KP_2, KP_3,     KP_0,      KP_DOT, TRNS, TRNS, TRNS, TRNS, TRNS,             TRNS,             TRNS,       \
        TRNS, TRNS, KP_ENTER,                          TRNS,                   TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS)
};

static const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1)
};
