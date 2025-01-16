# New Default Layout for CoolerMaster Quickfire Rapid + Frosty Flake (2014) TKL

QMK's default layout for the Frosty Flake is lacking some of the basic functionality that the CoolerMaster QuickFire Rapid has in place by default - namely, the media functions and WinLock key.

This is aimed at being a new layout that should serve as a basic jumping off point.

This is for the Tenkey-less version of the keyboard.

I also plan on adding a new keymap that adds macro functionality for this entire keyboard.

# Instructions

I set this up as a new keyboard, since I had to make some changes to the LED pin assignments (namely, getting rid of them). As such, you should be able to copy the `keyboard` folder into your `qmk_firmware` folder. It will put a new keyboard called `custom_fw` in the correct place (`qmk_firmware/keyboards/bpiphany/frosty_flake/`).

The keymap you should place in: (`qmk_firmware/keyboards/bpiphany/frosty_flake/keymaps/[your_folder_name]`)

Then, from your `qmk_firmware` folder, you can build and flash with these commands:

```
qmk compile -kb bpiphany/frosty_flake/custom_fw -km [your_folder_name]
qmk flash -kb bpiphany/frosty_flake/custom_fw -km [your_folder_name]
```

When flashing, make sure you hit a key combo to put the keyboard in programming mode (if you previously set one with some other keymap/fw), or use a magnet above the arrow keys somewhere.

## Desired Functionality:

On function layer:

1. [x] F5 is media play/pause
1. [x] F6 is media stop
1. [x] F7 is media previous track
1. [x] F8 is media next track
1. [ ] F9 is a functioning Win Lock toggle key
1. [x] F10 is audio mute
1. [x] F11 is audio volume down
1. [x] F12 is audio volume up
1. [x] Esc is BOOTLOADER (for programming)
1. [x] Tilde/backtick is ~~RESET~~ REBOOT (for programming)
1. [ ] CapsLock LED is on while holding FN key
1. [ ] Add a layer for macros
1. [ ] CapsLock when double tapped sets macro layer
1. [ ] CapsLock single tap returns to our regular layer
1. [ ] CapsLock key should blink on interval when in macro mode.

## Notes

* LED high is off, LED low is on for the indicator lights on this board
* You need to remove the definition of the pins from `keyboard.json` to use them for other purposes; I should create a new keyboard entry for this purpose
* Make sure you define the LED pins/initialize them before you try to use them
* LED pins are:
  * B7 for NumLock (WinLock key)
  * C5 for CapsLock
  * C6 for ScrollLock