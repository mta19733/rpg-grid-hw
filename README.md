# RPG Grid Arduino
Code for controlling RPG Grid [ESP32] hardware via Bluetooth [RPG Grid] app.

## Prerequisites
* Install [PlatformIO CLI].
* Preferably install an IDE, [CLion] is a good choice.

## Development
If you've chosen to use [CLion], before opening the project run:
```bash
pio init --ide clion --board esp32doit-devkit-v1
```

To upload your code and run the serial monitory:
```bash
pio run
```

If upload gets stuck at `Connecting...`, first make sure that serial monitor is
closed. If that doesn't help, you might have multiple USB devices. To
workaround this, list all serial ports:
```bash
pio device list
```

Grab the one which is your [ESP32] device and run the following (replace `PORT`
with your device port):
```bash
pio run --upload-port <YOUR_PORT>
```

[PlatformIO CLI]: https://platformio.org/install/cli
[RPG Grid]: https://github.com/Edvinas01/rpg-grid
[ESP32]: https://www.espressif.com/en/products/hardware/esp32/overview
[CLion]: https://www.jetbrains.com/clion
