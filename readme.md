# Brightness

If pressing `F5/F6` (or other function keys) could change no screen brightness but only the `brightness` file in your `/sys/class/backlight/xxx_backlight/` folder, this program might work.

Inspired by [Brightness Controller](https://github.com/LordAmit/Brightness), this simple program uses `xrandr` to control the brightness of the screen. It could not lower down the energe consumption (unless your screen is not an OLED one) but at least when no other ways work, it can save your eyes.

The source code is easy to understand and modify. As default, it would first search for `dell_backlight` under the  `/sys/class/backlight/` folder and then the `intel_backlight` folder if the previous one is not found. You can simply modify the `backlights` vector to suit it to your computer.

**Brightness** (this program) is under the MIT license. Use it freely.