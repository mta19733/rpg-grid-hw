# RPG Grid
Code for controlling RPG Grid [ESP32] hardware via Bluetooth [RPG Grid] app.

## Prerequisites
* Install [PlatformIO CLI].
* Preferably install an IDE, [CLion] is a good choice.

## Running
If you've chosen to use [CLion], before opening the project run:
```bash
pio init --ide clion --board esp32doit-devkit-v1
```

Then just upload your code and run the serial monitor:
```bash
pio run
```

## Gotchas
If `pio run` gets stuck at `Connecting...` make sure that serial monitor is
closed as only one instance can be running.

If that doesn't help, you might have multiple USB devices connected to your PC.
To workaround this, first list all serial ports:
```bash
pio device list
```

Grab the one which is your [ESP32] device and run the following (replace `PORT`
with your device port):
```bash
pio run --upload-port PORT
```

[PlatformIO CLI]: https://platformio.org/install/cli
[RPG Grid]: https://github.com/mta19733/rpg-grid
[ESP32]: https://www.espressif.com/en/products/hardware/esp32/overview
[CLion]: https://www.jetbrains.com/clion
