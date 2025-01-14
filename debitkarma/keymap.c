#include QMK_KEYBOARD_H

enum custom_keycodes {
    COPY = SAFE_RANGE,
    PASTE,
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
                 QK_BOOTLOADER, DB_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MPLY,  KC_MSTP,  KC_MPRV,  KC_MNXT,  KC_NO,  KC_MUTE, KC_VOLD,  KC_VOLU,             KC_TRNS, KC_NUM, KC_TRNS,
                 QK_REBOOT, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
                 KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,
                 KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,          KC_ENT,
                 KC_LSFT,KC_NUBS,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,            KC_UP,
                 KC_LCTL,KC_LGUI,KC_LALT,                KC_SPC,                                 KC_RALT,KC_RGUI, KC_TRNS,  KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT  ),
[2] = LAYOUT_tkl(
                 KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,             KC_PSCR, KC_SCRL, KC_PAUS,
                 KC_TRNS, COPY,   PASTE,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
                 KC_TRNS, KC_NO,   KC_NO,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN,
                 KC_TRNS, KC_NO,   KC_NO,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,          KC_ENT,
                 KC_NO,KC_NUBS,KC_NO,   KC_NO,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,          KC_RSFT,            KC_UP,
                 KC_NO,KC_NO,KC_NO,                KC_SPC,                                 KC_RALT,KC_RGUI, LT(1,KC_APP),  KC_RCTL,   KC_LEFT, KC_DOWN, KC_RGHT  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    //repurposing NumLock LED
    switch (get_highest_layer(state)) {
        case 2:
            writePinHigh(B7);
            break;
        case 1:
            writePinHigh(B7);
            break;
        default:
            writePinLow(B7);
            break;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case COPY:
        if (record->event.pressed) {
            SEND_STRING( SS_DOWN(X_LCTL) "C" SS_UP(X_LCTL) );
        } else {
            // when keycode is released
        }
        break;
    case PASTE:
        if (record->event.pressed) {
            SEND_STRING( SS_DOWN(X_LCTL) "V" SS_TAP(X_LCTL) );
        } else {
            // when keycode is released
        }
        break;
    }
    return true;
};

// SEND_STRING( SS_DOWN(X_LCTL) SS_DOWN(X_L_SFT) SS_TAP(X_LEFT) SS_UP(X_L_SFT) "C" SS_UP(X_LCTL) );
// SEND_STRING( SS_DOWN(X_LCTL) SS_DOWN(X_L_SFT) SS_TAP(X_RIGHT) SS_UP(X_L_SFT) "V" SS_UP(X_LCTL) );