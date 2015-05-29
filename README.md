PID Control Library
====
PID control library implemented in floating point arithmetic, it is designed to run in almost any microcontroller that can accept C language code and implement floating point routines. It is based on the Arduino project PID library that can be found in the following address:

* http://playground.arduino.cc/Code/PIDLibrary
* https://github.com/br3ttb/Arduino-PID-Library

The main advantage of this PID library is that it can be compiled on a wide range of devices, due to the fact that this library does not require a C++ compiler and can be linked with our other libraries for maximum portability to other platforms.

Library Usage
====

The following code depicts the library basic usage, input and output functions should be provided by end user.

```
#include "PID.h"

// Structure to strore PID data and pointer to PID structure
struct pid_controller ctrldata;
pid_t pid;

// Control loop input,output and setpoint variables
float input = 0, output = 0;
float setpoint = 15;

// Control loop gains
float kp = 2.5, ki = 1.0, kd = 1.0;

void main()
{
	// Prepare PID controller for operation
	pid = pid_create(&ctrldata, &input, &output, &setpoint, kp, ki, kd);
	// Set controler output limits from 0 to 200
	pid_limits(pid, 0, 200);
	// Allow PID to compute and change output
	pid_auto(pid);

	// MAIN CONTROL LOOP
	for (;;) {
		// Check if need to compute PID
		if (pid_need_compute(pid)) {
			// Read process feedback
			input = process_input();
			// Compute new PID output value
			pid_compute(pid);
			//Change actuator value
			process_output(output);
		}
	}
}
```

Librería de control PID
====

Librería de control PID en punto flotante diseñada para correr en prácticamente cualquier microcontrolador que pueda aceptar código en lenguaje C y aritmética de punto flotante. Esta basada en la librería PID de arduino que puede encontrarse en la siguiente dirección:

* http://playground.arduino.cc/Code/PIDLibrary
* https://github.com/br3ttb/Arduino-PID-Library

La ventaja de esta librería es que puede compilarse para una mayor cantidad de dispositivos pues no requiere un compilador de C++ y puede enlazarse con otras de nuestras librerías para maxima portabilidad a otras plataformas.

Uso de la librería
====

El codigo siguiente muestra el uso básico de la librería, las funciones de entrada y salida deben ser provistas por el usuario.

```
#include "PID.h"

// Structure to strore PID data and pointer to PID structure
struct pid_controller ctrldata;
pid_t pid;

// Control loop input,output and setpoint variables
float input = 0, output = 0;
float setpoint = 15;

// Control loop gains
float kp = 2.5, ki = 1.0, kd = 1.0;

void main()
{
	// Prepare PID controller for operation
	pid = pid_create(&ctrldata, &input, &output, &setpoint, kp, ki, kd);
	// Set controler output limits from 0 to 200
	pid_limits(pid, 0, 200);
	// Allow PID to compute and change output
	pid_auto(pid);

	// MAIN CONTROL LOOP
	for (;;) {
		// Check if need to compute PID
		if (pid_need_compute(pid)) {
			// Read process feedback
			input = process_input();
			// Compute new PID output value
			pid_compute(pid);
			//Change actuator value
			process_output(output);
		}
	}
}
```


