# WiFi Drone (ESP32)

It creates an interface between the WiFi (WebSocket) and IBus bus.

## Features
* 14 channels
* Web server on port 80 serve your html file like [this one](https://github.com/MichalSchwarz/rc-controller/blob/master/dist/index_html.h) on `/` route.
* WebSocket server running on `/ws` route is waiting on controll messages.
  * Message is array of 28 Bytes. 14 Integers in range between 1000 and 2000. We can write it in JavaScript:
    ```js
    const socket = new WebSocket('ws://'+window.location.host+'/ws');
    socket.addEventListener('open', function (event) {
      let message = new Uint16Array(14);
      for (let index = 0; index < message.length; index++) {
        message[index] = 1500;
      }
      socket.send(message);
    });
    ```
* Ibus transmission is activated by the first received WS message. If no WS message arrives within 2 seconds, Ibus will deactivate.

## How to Use it

1. Clone project
    ```bash
    git clone git@github.com:MichalSchwarz/wifi-drone-esp32.git
    ```
2. Create header file with WiFi SSID and password in `src/` folder. By this [example](https://github.com/MichalSchwarz/wifi-drone-esp32/wiki/ExampleSecretHeader).

3. Add Controller header file like [this one](https://github.com/MichalSchwarz/rc-controller/blob/master/dist/index_html.h) into `src/` folder.

4. Add libraries [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) and [AsyncTCP](https://github.com/me-no-dev/AsyncTCP). More info in [this blogpost](https://techtutorialsx.com/2017/12/01/esp32-arduino-asynchronous-http-webserver/).

5. Connect IBus reciever to ESP-32, pin 27 (GPIO17, TX2).

6. Compile and upload this project to ESP-32.