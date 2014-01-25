ev3sensor: Basic C API for reading sensors with Lego Mindstorms EV3.

### Usage
This can be used together with Bricxcc, found at: 
http://bricxcc.sourceforge.net/test_releases/ (read readme_1st.txt for installation and usage).

The C API at the above link (lms_api.zip) does not support sensors yet (as of January 26th, 2014).
This project is meant to fill the void until that API includes sensor support,
or until a better API for sensors come along.

1. In Bricxcc, open View|Project Manager and add ev3sensor.c to the list of sources.
2. The API is found in "ev3sensor.h", which is the only header necessary to include in your source code.

### Sensor support
The current version should support most sensors, but it is only tested with the 3 types of sensors
that come with the standard EV3 kit (IR, color and touch sensors). IIC sensors should work but is untested.

This API is also very basic and only provides reading raw sensor values, and setting sensor mode.