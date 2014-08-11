#ifndef IO_H
#define	IO_H

#include <stdint.h>

void io_write(uint8_t pin, uint8_t value);

void io_mode(uint8_t pin, uint8_t mode);


#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW 0
#endif


#endif
//End of header file
