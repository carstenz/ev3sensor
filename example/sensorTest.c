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
