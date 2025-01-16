#include QMK_KEYBOARD_H

// adding tracker for win lock state, initializes to OFF
static uint8_t winlock_tracker; // = 0;

enum custom_keycodes {
    KUNDO = SAFE_RANGE,
    KCOPY,
    KPASTE,
    TOGGLEWINLOCK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_tkl(
                 KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,             KC_PSCR, KC_SCRL, KC_PAUS,
                 KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
                 KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,
                 TG(2), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,          KC_ENT,
                 KC_LSFT,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,            KC_UP,
                 KC_LCTL,KC_LGUI,KC_LALT,                KC_SPC,                                 KC_RALT,KC_RGUI, LT(1,KC_APP),  KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT  ),
[1] = LAYOUT_tkl(
                 QK_BOOTLOADER, DB_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MPLY,  KC_MSTP,  KC_MPRV,  KC_MNXT,  TOGGLEWINLOCK,  KC_MUTE, KC_VOLD,  KC_VOLU,                         KC_TRNS, KC_NUM, KC_TRNS,
                 QK_REBOOT, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS,       KC_TRNS,  KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS,  KC_TRNS,
                 KC_CAPS,KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,KC_TRNS,          KC_TRNS,
                 KC_TRNS,KC_NUBS,KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,KC_TRNS, KC_TRNS,          KC_TRNS,                   KC_UP,
                 KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,                                 KC_TRNS,KC_TRNS, KC_TRNS,  KC_TRNS,                                   KC_LEFT, KC_DOWN, KC_RGHT  ),
[2] = LAYOUT_tkl(
                 KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,             KC_PSCR, KC_SCRL, KC_PAUS,
                 KC_TRNS, KUNDO,   KCOPY,   KPASTE,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
                 KC_TRNS, KC_NO,   KC_NO,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,
                 KC_TRNS, KC_NO,   KC_NO,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,          KC_ENT,
                 KC_NO,KC_NUBS,KC_NO,   KC_NO,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,            KC_UP,
                 KC_NO,KC_NO,KC_NO,                KC_SPC,                                 KC_RALT,KC_RGUI, LT(1,KC_APP),  KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT  )
};

void keyboard_pre_init_user(void) {
    setPinOutput(B7);  // initialize B7 for WinLock (numlock) LED
    setPinOutput(C5);  // initialize C5 for CapsLock LED
    setPinOutput(C6);  // initialize C6 for ScrollLock LED
}

void toggle_windows_lock(void) {
    if (winlock_tracker) {
        winlock_tracker++;
        SS_TAP( QK_MAGIC_GUI_ON );
        writePinLow(B7);
    } else {
        winlock_tracker--;
        SS_TAP( QK_MAGIC_GUI_OFF );
        writePinHigh(B7);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {

    // indicator LEDs for this board are opposite
    if(IS_LAYER_ON_STATE(state, 2)) {
        writePinLow(C6);
    } else if(IS_LAYER_ON_STATE(state, 1)) {
        writePinLow(C6);
    } else {
        writePinHigh(C6);
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KUNDO:
        if (record->event.pressed){
            SEND_STRING( SS_LCTL(SS_TAP(X_Z)) );
        } else {
        }
        break;
    case KCOPY:
        if (record->event.pressed) {
            SEND_STRING( SS_LCTL(SS_TAP(X_C)) );
        } else {
            // when keycode is released
        }
        break;
    case KPASTE:
        if (record->event.pressed) {
            SEND_STRING( SS_LCTL(X_V) );
        } else {
            // when keycode is released
        }
        break;
    case TOGGLEWINLOCK:
        if (record->event.pressed) {
            toggle_windows_lock();
        }
    }
    return true;
};

// SEND_STRING( SS_DOWN(X_LCTL) SS_DOWN(X_L_SFT) SS_TAP(X_LEFT) SS_UP(X_L_SFT) "C" SS_UP(X_LCTL) );
// SEND_STRING( SS_DOWN(X_LCTL) SS_DOWN(X_L_SFT) SS_TAP(X_RIGHT) SS_UP(X_L_SFT) "V" SS_UP(X_LCTL) );
