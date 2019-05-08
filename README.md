# WiFi Drone (ESP32)

It creates an interface between the WiFi (WebSocket) and IBus bus.

## Example

[![Esp32 Asgard32-F7 Drone](https://michalschwarz.github.io/rc-controller/assets/Esp32-Asgard32_F7-Drone-full-thumb.jpg)](https://michalschwarz.github.io/rc-controller/assets/Esp32-Asgard32_F7-Drone-full.jpg)
[![Esp32 Asgard32-F7 Drone controller](https://michalschwarz.github.io/rc-controller/assets/Esp32-Asgard32_F7-Drone-controller-thumb.jpg)](https://michalschwarz.github.io/rc-controller/assets/Esp32-Asgard32_F7-Drone-controller.jpg)

[How to Build a ESP32 Drone controlled by Web browser](https://michalschwarz.github.io/rc-controller/esp32/quadcopter/f450/asgard32/schema/2019/05/07/esp32-drone-v1.0.0.html)

## Features
* 14 channels
* Web server on port 80 serve your html file like [this one](https://github.com/MichalSchwarz/rc-controller/blob/master/dist/index_html.h) on `/` route.
* Controller is running on `/control` and waiting on control GET HTTP requests.
* Ibus transmission is activated by the first received request. If no request arrives within 2 seconds, Ibus will deactivate.

## How to Use it

1. Clone project
    ```bash
    git clone git@github.com:MichalSchwarz/wifi-drone-esp32.git
    ```
2. Create header file with WiFi SSID and password in `src/` folder. By this [example](https://github.com/MichalSchwarz/wifi-drone-esp32/wiki/ExampleSecretHeader).

3. Add Controller header file like [this one](https://github.com/MichalSchwarz/rc-controller/blob/master/dist/index_html.h) into `src/` folder.

4. Add ESP32 library [https://github.com/espressif/arduino-esp32](https://github.com/espressif/arduino-esp32).

5. Connect IBus reciever to ESP-32, pin 27 (GPIO17, TX2).

6. Compile and upload this project to ESP-32.