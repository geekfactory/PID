#include "io.h"
#include <xc.h>
volatile uint8_t * portptrs[] =
{
#if defined (_PORTA_RA0_POSN)
	&PORTA,
#endif
#if defined (_PORTB_RB0_POSN)
	&PORTB,
#endif
#if defined (_PORTC_RC0_POSN)
	&PORTC,
#endif
#if defined (_PORTD_RD0_POSN)
	&PORTD,
#endif
#if defined (_PORTE_RE0_POSN)
	&PORTE,
#endif

};

volatile uint8_t * trisptrs[] =
{
#if defined (_TRISA_RA0_POSN)
	&TRISA,
#endif
#if defined (_TRISB_RB0_POSN)
	&TRISB,
#endif
#if defined (_TRISC_RC0_POSN)
	&TRISC
#endif
#if defined (_TRISD_RD0_POSN)
	&TRISD,
#endif
#if defined (_TRISE_RE0_POSN)
	&TRISE,
#endif
};

const uint8_t mask[] =
{
	0x01,
	0x02,
	0x04,
	0x08,
	0x10,
	0x20,
	0x40,
	0x80
};


void io_mode( uint8_t pin, uint8_t value )
{
	uint8_t port = pin / 8;
	uint8_t num = pin % 8;

	uint8_t now = *(trisptrs[port]);

	if( value == OUTPUT )
		now &= ~mask[num];
	else
		now |= mask[num];

	*(trisptrs[port]) = now;
}

void io_write( uint8_t pin, uint8_t value )
{
	uint8_t port = pin / 8;
	uint8_t num = pin % 8;

	uint8_t now = *(portptrs[port]);

	if( value == LOW )
		now &= ~mask[num];
	else
		now |= mask[num];

	*(portptrs[port]) = now;
}


uint8_t io_read( uint8_t pin )
{
	uint8_t port = pin / 8;
	uint8_t num = pin % 8;

	uint8_t now = *(portptrs[port]);

	if( now & mask[num])
		return HIGH;
	else
		return LOW;
}
