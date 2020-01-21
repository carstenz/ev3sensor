/*
 * EV3 Sensor API
 *
 * Copyright (C) 2014 Carsten Zeiffert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef EV3SENSOR_H
#define EV3SENSOR_H

/**
 * Initializes sensor I/O.
 */
int initSensors();

/**
 * Reads the sensor value from a specific port.
 * Example: readSensor(INPUT_1)
 * Returns a raw sensor value.
 */
int readSensor(int sensorPort);

/**
 * Returns pointer to the current sensor value.
 * The sensor value may be up to 32 bytes long - this function
 * can be used to access it if readSensor() is inadequate.
 */
void* readSensorData(int sensorPort);

/**
 * Set sensor mode for a specific port.
 * Example: setSensorMode(INPUT_1, EV3_IR_MODE_REMOTE)
 */
int setSensorMode(int sensorPort, int mode);

// Sensor ports
#define INPUT_1 0
#define INPUT_2 1
#define INPUT_3 2
#define INPUT_4 3

// EV3 color sensor modes
#define COLOR_MODE_REFLECT 0
#define COLOR_MODE_AMBIENT 1
#define COLOR_MODE_COLOR 2

// EV3 IR sensor modes
#define EV3_IR_MODE_PROXIMITY 0
#define EV3_IR_MODE_SEEK 1
#define EV3_IR_MODE_REMOTE 2
#define EV3_IR_MODE_REMOTE_A 3
#define EV3_IR_MODE_S_ALT 4
#define EV3_IR_MODE_CAL 5

#endif // EV3SENSOR_H
