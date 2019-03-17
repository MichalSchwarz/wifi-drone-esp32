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
  wifi.begin(onControlEvent);
}

void Controller::loop(void) {
  controller.currentMillis = millis();
  if (controller.currentMillis - controller.wifiRecievedMillis >= WIFI_FAIL_TIMEOUT_MS) {
    ibus.disable();
  } else {
    ibus.enable();
  }
  wifi.loop();
  ibus.loop();
}

void Controller::updateControlValues(uint8_t list[Ibus::IBUS_CHANNELS_COUNT*2]) {
  controller.wifiRecievedMillis = millis();
  ibus.setControlValuesList(list);
}

void Controller::onControlEvent(uint8_t list[Ibus::IBUS_CHANNELS_COUNT*2])
{
  updateControlValues(list);
}
