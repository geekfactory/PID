#include "../PID.h"
#include "../../SPI/SPI.h"

#define CONFIG_TIMING_MAIN_CLOCK 12000000

typedef uint32_t tc_t;

tc_t tc_init(xSPIHandle spid, uint8_t cspin);
int16_t tc_read(tc_t thermo);

// Tick values
uint32_t lastrun = 0;
// PID Variables
float in, out, set=100;
// PID controllers
struct pid_controller pidctrl;
pid_t pid = 0;
// SPI Resource
xSPIHandle spi;
// Thermocouples
tc_t sensor = 0;


int main(int argc, char** argv)
{
	spi = spi_init( E_SPI_1 );
	spi_control( spi, SPI_MASTER | SPI_MODE_0, SPI_DIV_1_64 );

	//Create thermocuples
	sensor = tc_init(spi, 1);

	// Create new PID controllers, set gains
	pid = pid_create(&pidctrl, &in, &out, &set, 5, 1, 3);
	// Set output limits
	pid_limits(pid, 0, 255);
	// Turn on PID
	pid_auto(pid);

	for (;;) {

		if (tick_get() - lastrun >= TICK_SECOND) {
			lastrun = tick_get();
			// Read inputs
			in = (float) tc_read(sensor);
			// Compute PID controllers
			pid_compute(pid);
			// Adjust actuator
			// set_out(output);
		}
	}

}

