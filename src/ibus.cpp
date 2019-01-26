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
 * Ibus class is inspired by blogposts:
 *   https://basejunction.wordpress.com/2015/08/23/en-flysky-i6-14-channels-part1/
 *   http://blog.dsp.id.au/posts/2017/10/22/flysky-ibus-protocol/
 */

#include "Arduino.h"
#include "ibus.h"

Ibus ibus;

void Ibus::begin(HardwareSerial& serial)
{
  this->serial = &serial;
  this->serial->begin(IBUS_BAUD_RATE);
  for(size_t i = 0; i < IBUS_CHANNELS_COUNT; i++) {
    this->controlValuesList[i] = DEFAULT_CONTROL_VALUE;
  }
}

void Ibus::loop(void) {
  this->currentMillis = millis();
  if (this->currentMillis - this->previousMillis >= IBUS_SEND_INTERVAL_MS) {
    this->sendPacket();
    this->previousMillis = this->currentMillis;
  }
}

uint8_t * Ibus::createPacket(void) {
  // Guru Meditation Error: Core  1 panic'ed (LoadProhibited). Exception was unhandled. Thrown if this is not static!
  static uint8_t packetBytesList[IBUS_PACKET_BYTES_COUNT];
  packetBytesList[0] = 0x20;
  packetBytesList[1] = 0x40;
  uint_fast16_t checksum = 0xFFFF - 0x20 - 0x40;
  uint8_t actualPosition = 2;
  for(size_t i = 0; i < IBUS_CHANNELS_COUNT; i++) {
    packetBytesList[actualPosition] = lowByte(this->controlValuesList[i]);
    checksum -= packetBytesList[actualPosition];
    packetBytesList[actualPosition + 1] = highByte(this->controlValuesList[i]);
    checksum -= packetBytesList[actualPosition + 1];
    actualPosition += 2;
  }
  packetBytesList[IBUS_PACKET_BYTES_COUNT - 2] = lowByte(checksum);
  packetBytesList[IBUS_PACKET_BYTES_COUNT - 1] = highByte(checksum);
  return packetBytesList;
}

void Ibus::sendPacket() {
  uint8_t * packetBytesList = this->createPacket();
  for(size_t i = 0; i < IBUS_PACKET_BYTES_COUNT; i++) {
    this->serial->write(packetBytesList[i]);
  }
}
