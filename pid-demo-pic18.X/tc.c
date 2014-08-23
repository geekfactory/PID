#include "tc.h"

tc_t tc_init(xSPIHandle spid, uint8_t cspin)
{
	struct thermocuple_struct tcpl;

	// Configure Chip Select as output, Set MAX6675 CS to high level
	io_write(cspin, HIGH);
	io_mode(cspin, OUTPUT);
	// Configure SPI for MAX6675 operation
	spi_control(spid, SPI_MASTER | SPI_MODE_1, SPI_DIV_1_8);
	spi_open(spid);
	// Save operation parameters
	tcpl.spi = spid;
	tcpl.cspin = cspin;

	return tcpl;
}

int16_t tc_read(tc_t * tcpl)
{
	uint16_t buf = 0;

	// Pull CS low
	io_write(tcpl->cspin, LOW);
	// Read data
	spi_read_array(tcpl->spi, (uint8_t *) & buf, 2);
	// Pull CS high
	io_write(tcpl->cspin, HIGH);
	// Open or bad connection on thermocuple returns negative value
	if (buf & (1 << 2))
		return -1;
	// Remove dummy bytes
	buf &= 0x7FF8;
	// Shift bits
	buf >>= 3;
	return buf;
}

float tc_read_float(tc_t * tcpl)
{
	return((float) tc_read(tcpl))* 0.25;
}