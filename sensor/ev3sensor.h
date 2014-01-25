
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