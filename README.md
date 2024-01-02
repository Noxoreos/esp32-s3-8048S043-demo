# Demo setup for the screen board "ESP32-8048S043-C_I"

## About the author and this repository

Hi, I'm Noxoreos. I'm a professional software developer who is also interested in electronics.

I recently got a the mentioned display board, because I thought this might become a useful "little" thing.

However I did not like the way how the examples were based on outdated libraries when I started with it and after upgrading to the newer version of the suggested graphics library, I noticed some issues around stability of the displayed image (jitter). Furthermore it wasn't particularly quick.

Instead I got into a different library which is called the [LovyanGFX](https://github.com/lovyan03/LovyanGFX).
After figuring out how to use it, I thought this might be interesting to others when they get this screen, because I have invested quite some time in research about this board and have put all of it into this repository.

That is the reason why this repository exists - and of course as a reference for myself in the future.

## General info

This repository holds a basic configuration for an ESP32-S3 display board (4.3 inch ips panel) with a resolution of 800x480 pixels and a capacitive touch panel of the type GT911. Note, that this is a parallel screen, which is why there aren't many library options to choose from.

It also contains an own pin definition file for all hard-wired pins on the board as well as the extended io ports.

Finally it uses the (currently) newest version 1.1.9 of the LovyanGFX library to handle graphics output and touch.

This codebase is meant to be used with the PlatformIO extension on VSCode. The C/C++ extension is also required view this code base.
The code style used in this repository is defined in the `.clang-format` file.

## What does this demo do?

When it's being executed, then it will first start the screen calibration process.
Then it prints out some text on the screen and reads the touchscreen as well.

It then renders a moving rectangle, unless the screen is touched with one finger. At that point it stops moving and is drawn
at the X-position of the touch.

When touched with two fingers or more, it resets back to it moving animation.

## Files in this codebase

Check out the following files:

- `include/esp32_s3_screen_board_defs.h` - Board/pin-out definitions
- `include/esp32_s3_screen_board_8048S043.h` - Setup file for the LovyanGFX library
- `include/main.h` - This file ties everything together and re-enables usage of serial communication via the variable `Serial`
- `src/main.cpp` - This file creates an instance of the LovyanGFX library and a buffer using a sprite. Then it draws everything on the screen.
- `platformio.ini` - Here you find some macro definitions like `MONITOR_SPEED` for the usage with the serial monitor
- `.clang-format` - Code style definition. Make sure to use clang engine and ``Clang_format_style` is set to `file` in teh VSCode settings for this to work properly.
- `license.txt` - The license under which the code is published.

## Credits

Thanks to the folks over at [LovyanGFX](https://github.com/lovyan03/LovyanGFX) for putting in the hard work.

## License

This repository: MIT
[LovyanGFX: FreeBSD](https://raw.githubusercontent.com/lovyan03/LovyanGFX/1.1.9/license.txt) (also included as copy in "LovyanGFX-license.txt")
