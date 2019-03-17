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

#include "Arduino.h"
#include "wifi.h"

Wifi wifi;

void Wifi::begin(void (*controlCallback)(uint8_t list[Ibus::IBUS_CHANNELS_COUNT*2]))
{
  static WebServer server(WEBSERVER_PORT);
  this->server = &server;
  WiFi.softAPConfig(IPAddress(192, 168, 0, 1), IPAddress(192, 168, 0, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  this->beginWebServer(this->server);
  this->server->begin();
  this->controlCallback = controlCallback;
}

void Wifi::loop()
{
  this->server->handleClient();
}

void Wifi::beginWebServer(WebServer * server)
{
  server->on("/", onRoot);
  server->on(CONTROL_PATH, onControl);
}

void Wifi::onRoot()
{
  wifi.server->send(200, "text/html", INDEX_HTML);
}

void Wifi::onControl()
{
  static uint8_t list[Ibus::IBUS_CHANNELS_COUNT*2];
  for(size_t i = 0; i < Ibus::IBUS_CHANNELS_COUNT; i++)
  {
    String argName = String(i);
    int value = Ibus::DEFAULT_CONTROL_VALUE;
    if(wifi.server->hasArg(argName)) {
      int incommingValue = wifi.server->arg(argName).toInt();
      if(incommingValue >= Ibus::MIN_CONTROL_VALUE && incommingValue <= Ibus::MAX_CONTROL_VALUE) {
        value = incommingValue;
      }
    }
    list[i*2] = lowByte(value);
    list[(i*2)+1] = highByte(value);
  }
  wifi.controlCallback(list);
  wifi.server->send(200, "text/plain", "");
}
