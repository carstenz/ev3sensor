/*
 * EV3 Sensor API
 *
 * Copyright (C) 2014 Carsten Zeiffert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 */

#include <stdio.h>
#include <unistd.h>

#include "ev3_lcd.h"
#include "ev3_command.h"
#include "ev3sensor.h"

int main()
{
    initSensors();
    setSensorMode(INPUT_1, 0);
    LcdInit();
    
    char buffer[50];
    int i;
    for (i = 0; i < 40; i++)
    {
        LcdClean();

        sprintf (buffer, "Sensor value: %i", readSensor(INPUT_1));
        LcdText(1, 0, 0, buffer);
        sprintf (buffer, "Iteration:%i", i);
        LcdText(1, 0, 10, buffer);

        Wait(200);
    }
    LcdExit();
}
