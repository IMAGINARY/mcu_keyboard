# Custom Teensy LC keyboard

In the context of exhibitions, software is often controlled via dedicated custom buttons build into the case of the exhibit. Most often, only a limited set of keys is needed to navigate the exhibit. 

This project aims to aid custom keyboard creation using a Teensy LC micro controller. All push buttons that close an electrical connection when pressed and open it when released can be used.

# Wiring

A button must be connected to GND and one of the digital pins of the Teensy LC.
A useful set of keys is listed in the `config.h` file, e.g. the line
```
createButton(26, KEY_TAB, MODIFIERKEY_SHIFT),
```
indicates that a button connected to GND and digital pin 26 will emulate the <kbd>TAB</kbd> key with pressed <kbd>SHIFT</kbd> modifier key. Pins for keys that are not used but are listed in `config.h` should be left unconnected.

# Flashing the .hex file

For convenience, we offer pre-compiled `.hex` files for download in the release section.
The device specific `.hex` file can be flashed onto the Teensy LC via the [Teensy Loader](https://www.pjrc.com/teensy/loader.html). Downloading and installing the
full [Teensyduino IDE](https://www.pjrc.com/teensy/teensyduino.html) is not necessary for flashing the `.hex` file.

Open the Teensy Loader, connect the Teensy LC, open the `.hex` file and flash.

There are also other methods involving [command line tools](https://www.pjrc.com/teensy/loader_cli.html), but they are not discussed here.

# Customization

The most important options of this sketch can be customized via the `config.h`
file, but this requires [recompilation](#Compilation) of the code.

# Keys & pins

Pin and key assignments can be reconfigured by adding, removing or modifying the `createButton(pin, keyCode, modifiers)` calls.

 - [Teensy LC pinout](https://www.pjrc.com/teensy/pinout.html)
 - [Key IDs](https://www.pjrc.com/teensy/td_keyboard.html)

# Debouncing

Almost every physical button is subject to contact-bounce such that it takes a couple of milliseconds until the contact is stable and stops bouncing between digital 0 and 1. The length of the debouncing interval (in milliseconds) can be configured via the `DEBOUNCE_INTERVAL` macro.

# Compilation

Compiling the sketch requires the [Teensyduino IDE](https://www.pjrc.com/teensy/teensyduino.html).

After opening the project in Teensyduino and connecting the Teensy LC, you have to apply a couple of settings:
- Tools -> Board -> Teensyduino -> Teensy LC
- Tools -> USB Type -> Serial + Keyboard + Mouse + Joystick
- CPU Speed -> 24 MHz
- Keyboard Layout: US English (or whatever is needed for your `config.h` modifications)

Now you can verify and upload your sketch to the Teensy LC.
