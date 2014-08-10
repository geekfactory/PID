/*	Floating point PID control loop for Microcontrollers
	Copyright (C) 2014 Ruben Santa Anna Zamudio.

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
 */
#ifndef PID_H
#define PID_H
/*-------------------------------------------------------------*/
/*		Includes and dependencies			*/
/*-------------------------------------------------------------*/
#include"Tick/Tick.h"

/*-------------------------------------------------------------*/
/*		Macros and definitions				*/
/*-------------------------------------------------------------*/
// Define "boolean" values
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
/*-------------------------------------------------------------*/
/*		Typedefs enums & structs			*/
/*-------------------------------------------------------------*/
enum enCtrlDirs {
	E_PID_DIRECT,
	E_PID_REVERSE,
};

struct pid_controller {
	// Input, output and setpoint
	float * input; //!< Current Process Value
	float * output; //!< Corrective Output from PID Controller
	float * setpoint; //!< Controller Setpoint
	// Tuning parameters
	float Kp; //!< Stores the gain for the Proportional term
	float Ki; //!< Stores the gain for the Integral term
	float Kd; //!< Stores the gain for the Derivative term
	// Output minimum and maximum values
	float omin; //!< Maximum value allowed at the output
	float omax; //!< Minimum value allowed at the output
	// Variables for PID algorithm
	float iterm; //!< Accumulator for integral term
	float lastin; //!< Last input value for differential term
	// Time related
	uint32_t lasttime; //!< Stores the time when the control loop ran last time
	uint32_t sampletime; //!< Defines the PID sample time
	// Operation mode
	uint8_t automode; //!< Defines if the PID controller is enabled or disabled
	enum enCtrlDirs direction;
};

typedef struct pid_controller * pid_t;

/*-------------------------------------------------------------*/
/*		Function prototypes				*/
/*-------------------------------------------------------------*/

/**
 * @brief Creates a new PID controller
 *
 * Creates a new pid controller and initializes it´s internal variables.
 *
 * @param pid A pointer to a pid_controller structure
 * @param in Pointer to float value for the process input
 * @param out Poiter to put the controller output value
 * @param set Pointer float with the process setpoint value
 * @param kp Proportional gain
 * @param ki Integral gain
 * @param kd Diferential gain
 *
 * @return returns a pid_t controller handle
 */
pid_t pid_create(pid_t pid, float* in, float* out, float* set, float kp, float ki, float kd);


uint8_t pid_compute(pid_t pid);

void pid_tune(pid_t pid, float kp, float ki, float kd);

void pid_sample(pid_t pid, uint32_t time);

void pid_limits(pid_t pid, float min, float max);

void pid_direction(pid_t pid, enum enCtrlDirs direction);

void pid_auto(pid_t pid);
#endif
// End of Header file
