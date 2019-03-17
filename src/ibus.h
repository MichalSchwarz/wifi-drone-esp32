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

#ifndef Ibus_h
#define Ibus_h

#include "Arduino.h"

class Ibus {
  public:
    static const unsigned long IBUS_BAUD_RATE = 115200;
    static const unsigned int IBUS_SEND_INTERVAL_MS = 100;
    static const unsigned int IBUS_PACKET_BYTES_COUNT = 32;
    static const unsigned int IBUS_CHANNELS_COUNT = 14;
    static const unsigned int DEFAULT_CONTROL_VALUE = 1000;
    static const unsigned int MIN_CONTROL_VALUE = 1000;
    static const unsigned int MAX_CONTROL_VALUE = 2000;

    void begin(HardwareSerial &serial);
    void loop(void);
    void enable(void);
    void disable(void);
    void setControlValuesList(uint8_t list[IBUS_CHANNELS_COUNT * 2]);

  private:
    HardwareSerial *serial;
    unsigned long previousMillis = 0;
    unsigned long currentMillis = 0;
    uint8_t controlValuesList[IBUS_CHANNELS_COUNT * 2];
    boolean isEnabled = false;

    void sendPacket(void);
    uint8_t * createPacket(void);
};

extern Ibus ibus;

#endif