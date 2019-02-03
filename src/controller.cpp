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
#include "controller.h"

Controller controller;


void Controller::begin(void)
{
  ibus.begin(Serial2);
  wifi.begin(onWsEvent);
}

void Controller::loop(void) {
  controller.currentMillis = millis();
  if (controller.currentMillis - controller.wifiRecievedMillis >= WIFI_FAIL_TIMEOUT_MS) {
    ibus.disable();
  } else {
    ibus.enable();
  }
  ibus.loop();
}

void Controller::updateControlValues(uint8_t list[Ibus::IBUS_CHANNELS_COUNT*2]) {
  controller.wifiRecievedMillis = millis();
  ibus.setControlValuesList(list);
}

void Controller::onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len)
{
  if(type == WS_EVT_DATA) {
    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    if(info->final && info->index == 0 && info->len == len && len == (Ibus::IBUS_CHANNELS_COUNT*2)){
      uint8_t controlValuesList[Ibus::IBUS_CHANNELS_COUNT*2];
      for(size_t i=0; i < info->len; i++) {
        controlValuesList[i] = data[i];
      }
      updateControlValues(controlValuesList);
    }
  }
}
