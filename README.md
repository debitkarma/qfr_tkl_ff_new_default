# New Default Layout for CoolerMaster Quickfire Rapid + Frosty Flake (2014) TKL

QMK's default layout for the Frosty Flake is lacking some of the basic functionality that the CoolerMaster QuickFire Rapid has in place by default - namely, the media functions and WinLock key.

This is aimed at being a new layout that should serve as a basic jumping off point.

This is for the Tenkey-less version of the keyboard.

I also plan on adding a new keymap that adds macro functionality for this entire keyboard.

## Desired Functionality:

On function layer:

1. F5 is media play/pause
1. F6 is media stop
1. F7 is media previous track
1. F8 is media next track
1. F9 is a functioning Win Lock toggle key
1. F10 is audio mute
1. F11 is audio volume down
1. F12 is audio volume up
1. Esc is BOOTLOADER (for programming)
1. Tilde/backtick is RESET (for programming)
1. CapsLock LED is on while holding FN key
1. Add a layer for macros
1. CapsLock when double tapped sets macro layer
1. CapsLock single tap returns to our regular layer
1. CapsLock key should blink on interval when in macro mode.

## Notes

* LED high is off, LED low is on for the indicator lights on this board
* You need to remove the definition of the pins from `keyboard.json` to use them for other purposes; I should create a new keyboard entry for this purpose
* Make sure you define the LED pins/initialize them before you try to use them
* LED pins are:
  * B7 for NumLock (WinLock key)
  * C5 for CapsLock
  * C6 for ScrollLock