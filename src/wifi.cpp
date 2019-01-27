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

void Wifi::begin()
{
  WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
  static AsyncWebServer server(WEBSERVER_PORT);
  this->beginWebServer(&server);
  static AsyncWebSocket ws(WEBSOCKET_PATH);
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.begin();
  MDNS.begin(MDNS_DOMAIN_NAME);
}

void Wifi::beginWebServer(AsyncWebServer * server)
{
  server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", INDEX_HTML);
  });
}

void Wifi::onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len)
{
  if(type == WS_EVT_CONNECT) {
    client->text("Hello from ESP32 Server");
  } else if(type == WS_EVT_DISCONNECT) {
  }
}
