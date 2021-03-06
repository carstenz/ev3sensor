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

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "ev3sensor.h"
#include "uart.h"
#include "iic.h"
#include "analog.h"

int g_uartFile = 0;
int g_iicFile = 0;
int g_analogFile = 0;
UART* g_uartSensors = 0;
IIC* g_iicSensors = 0;
ANALOG* g_analogSensors = 0;
int g_sensorMode[INPUTS];

int initSensors()
{
    g_uartFile = open("/dev/lms_uart", O_RDWR | O_SYNC);
	g_iicFile =  open("/dev/lms_iic", O_RDWR | O_SYNC);
	g_analogFile = open("/dev/lms_analog", O_RDWR | O_SYNC);

    g_uartSensors = (UART*)mmap(0, sizeof(UART), PROT_READ | PROT_WRITE,
                                MAP_FILE | MAP_SHARED, g_uartFile, 0);
    g_iicSensors = (IIC*)mmap(0, sizeof(UART), PROT_READ | PROT_WRITE,
                              MAP_FILE | MAP_SHARED, g_iicFile, 0);
	g_analogSensors = (ANALOG*)mmap(0, sizeof(ANALOG), PROT_READ | PROT_WRITE,
									MAP_FILE | MAP_SHARED, g_analogFile, 0);
	int i;
	for (i = 0; i < INPUTS; i++)
		g_sensorMode[i] = 0;

	if (g_uartFile && g_iicFile && g_analogFile &&
		g_uartSensors && g_iicSensors && g_analogSensors)
		return 0;
	return -1;
}

DATA8 getSensorConnectionType(int sensorPort)
{
	if (!g_analogSensors || sensorPort < 0 || sensorPort >= INPUTS)
		return 0;
	return g_analogSensors->InConn[sensorPort];
}

DATA8 getSensorMode(int sensorPort)
{
	if (!g_analogSensors || sensorPort < 0 || sensorPort >= INPUTS)
		return 0;
	return g_analogSensors->InDcm[sensorPort];
}

void* readUartSensor(int sensorPort)
{
	if (!g_uartSensors)
		return 0;
    UWORD currentSensorSlot = g_uartSensors->Actual[sensorPort];
    return g_uartSensors->Raw[sensorPort][currentSensorSlot];
}

void* readIicSensor(int sensorPort)
{
	if (!g_iicSensors)
		return 0;
    UWORD currentSensorSlot = g_iicSensors->Actual[sensorPort];
    return g_iicSensors->Raw[sensorPort][currentSensorSlot];
}

void* readNewDumbSensor(int sensorPort)
{
	return (void*)&(g_analogSensors->InPin6[sensorPort]);
}

void* readOldDumbSensor(int sensorPort)
{
	return (void*)&(g_analogSensors->InPin1[sensorPort]);
}

void* readNxtColor(int sensorPort, DATA8 index)
{
	return 0; // Not supported
/*
	DATAF result = DATAF_NAN;
	cInputCalibrateColor(g_analogSensors->NxtCol[sensorPort], g_analogSensors->NxtCol[sensorPort].SensorRaw);

	switch (g_sensorMode[sensorPort])
	{
	case 2: return cInputCalculateColor(g_analogSensors->NxtCol[sensorPort]); //NXT-COL-COL
    case 1: return g_analogSensors->NxtCol[sensorPort].ADRaw[BLANK]; // NXT-COL-AMB
    case 0: return g_analogSensors->NxtCol[sensorPort].ADRaw[RED]; // NXT-COL-RED
    case 3: return g_analogSensors->NxtCol[sensorPort].ADRaw[GREEN]; // NXT-COL-GRN
    case 4: return g_analogSensors->NxtCol[sensorPort].ADRaw[BLUE]; // NXT-COL-BLU
    case 5: return g_analogSensors->NxtCol[sensorPort].SensorRaw[Index]; // NXT-COL-RAW
	}
	return result;
*/
}

void* readSensorData(int sensorPort)
{
	if (!g_analogSensors || sensorPort < 0 || sensorPort >= INPUTS)
		return 0;

	CONN connectionType = getSensorConnectionType(sensorPort);
	switch (connectionType)
	{
		case CONN_NONE: case CONN_ERROR: return 0;
		case CONN_INPUT_UART: return readUartSensor(sensorPort);
		case CONN_NXT_IIC: return readIicSensor(sensorPort);
		case CONN_INPUT_DUMB: return readNewDumbSensor(sensorPort);
		case CONN_NXT_COLOR: return readNxtColor(sensorPort, 0);
		default: return readOldDumbSensor(sensorPort);
	}
	return 0;
}

int readSensor(int sensorPort)
{
	void* data = readSensorData(sensorPort);
	if (!data)
		return -1;

	CONN connectionType = getSensorConnectionType(sensorPort);
	switch (connectionType)
	{
		case CONN_INPUT_UART:
		case CONN_NXT_IIC: return *((DATA8*)data);
	}	
	return *((DATA16*)data);
}

int setSensorMode(int sensorPort, int mode)
{
	if (!g_analogSensors || sensorPort < 0 || sensorPort >= INPUTS)
		return -1;

	// Remember device mode
	g_sensorMode[sensorPort] = mode;

	// Set actual device mode
	DEVCON devCon;
	int i;
	for (i = 0; i < INPUTS; i++)
	{
	    devCon.Connection[sensorPort] = getSensorConnectionType(sensorPort);
	    devCon.Type[sensorPort] = 0; // ?
	    devCon.Mode[sensorPort] = g_sensorMode[sensorPort];
	}
	ioctl(g_uartFile, UART_SET_CONN, &devCon);
	ioctl(g_iicFile, IIC_SET_CONN, &devCon);
	return 0;
}
