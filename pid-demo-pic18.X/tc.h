/*	Thermocuple Interface Using MAX6675 IC
	Copyright (C) 2014 Jesus Ruben Santa Anna Zamudio.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Author website: http://www.geekfactory.mx
	Author e-mail: ruben at geekfactory dot mx
 */
#ifndef TC_H
#define	TC_H
/*-------------------------------------------------------------*/
/*		Includes and dependencies			*/
/*-------------------------------------------------------------*/
#include <stdint.h>
#include "../SPI/SPI.h"
#include "io.h"

/*-------------------------------------------------------------*/
/*		Macros and definitions				*/
/*-------------------------------------------------------------*/


/*-------------------------------------------------------------*/
/*		Typedefs enums & structs			*/
/*-------------------------------------------------------------*/
struct thermocuple_struct
{
	xSPIHandle spi;
	uint8_t cspin;
};

typedef struct thermocuple_struct tc_t;


/*-------------------------------------------------------------*/
/*		Function prototypes				*/
/*-------------------------------------------------------------*/

/**
 * @brief Prepares to read the thermocouple
 *
 * @param spid SPI Interface handle to communicate with the thermocuple
 * @param cspin Chip select pin to enable communication with the device
 *
 * @return A thermocuple_structure with information to use the thermocouple
 */
tc_t tc_init(xSPIHandle spid, uint8_t cspin);

/**
 * @brief Read thermocuple probe
 *
 * Returns the thermocuple reading as an integer value. The returnded value
 * is negative if the thermocuple is open or connected incorrectly.
 *
 * @param tcpl A pointer to a thermocuple_struct
 *
 * @return Returns the thermocuple reading as integer
 */
int16_t tc_read(tc_t * tcpl);

/**
 * @brief Read thermocuple probe
 *
 * Returns the thermocouple value as a float. The returned value is negative
 * if the thermocouple probe is open or connected incorrectly.
 *
 * @param tcpl A pointer to a thermocuple_struct
 *
 * @return Returns the thermocuple reading as float
 */
float tc_read_float(tc_t * tcpl);



#endif
// End of Header file
