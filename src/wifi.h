/*
 * This file is part of the  distribution (https://github.com/wifi-drone-esp32 or http://wifi-drone-esp32.github.io).
 * Copyright (c) 2019 Michal Schwarz.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef Wifi_h
#define Wifi_h

#include "Arduino.h"
#include "secret.h"
#include "index_html.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiAP.h>
#include <ESPAsyncWebServer.h>

class Wifi {
  public:
    void begin(void);

  private:
    static const unsigned int WEBSERVER_PORT = 80;
    const char * WEBSOCKET_PATH = "/ws";
    const char * MDNS_DOMAIN_NAME = "quadcopter";

    void beginWebServer(AsyncWebServer * server);
    static void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len);
};

extern Wifi wifi;

#endif