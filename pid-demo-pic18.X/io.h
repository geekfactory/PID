/*	IO Ports Abstraction Layer for microcontrollers
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
#ifndef IO_H
#define	IO_H
/*-------------------------------------------------------------*/
/*		Includes and dependencies			*/
/*-------------------------------------------------------------*/
#include <stdint.h>

/*-------------------------------------------------------------*/
/*		Macros and definitions				*/
/*-------------------------------------------------------------*/
#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW 0
#endif

#ifndef OUTPUT
#define OUTPUT 0
#endif

#ifndef INPUT
#define INPUT 1
#endif

/*-------------------------------------------------------------*/
/*		Function prototypes				*/
/*-------------------------------------------------------------*/

/**
 * @brief Configures the pin mode
 *
 * This function allows the programmer to configure a pin as input or output.
 * The function accepts two parameters: the pin number and the pin mode
 *
 * @param pin The number of the pin to configure
 * @param mode The mode to configure the pin: INPUT or OUTPUT
 */
void io_mode(uint8_t pin, uint8_t mode);

/**
 * @brief Changes the output level of the selected IO pin
 * 
 * Writes a new logic value to the selected IO pin. The pin should be configured
 * as output to actualy see the value on the pin.
 * 
 * @param pin The number of the pin to write
 * @param value The logic level to write: LOW or HIGH
 */
void io_write(uint8_t pin, uint8_t value);


/**
 * @brief Reads the current state on the selected IO pin
 *
 * Reads the present logic level on the IO pin.
 *
 * @param pin The number of the pin to read
 *
 * @return Returns HIGH if a high logic level is present on the pin or LOW if a
 * low level is present.
 */
uint8_t io_read( uint8_t pin );





#endif
//End of Header file
