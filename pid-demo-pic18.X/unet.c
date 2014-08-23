#include <stdint.h>;
#include "io.h";

// Output services
#define DOUT_SERVICE	10	//!< Digital Output control service
#define AOUT_SERVICE	11	//!< Analog output control service
#define IRTX_SERVICE	12	//!< Infrarred transmission service
#define CHARLCD_SERVICE	14	//!< Serial LCD service
#define SBRIDGE_SERVICE	15	//!< Serial Port bridge service


// Storage non IO services
#define TIME_SERVICE	50
#define TIMERS_SERVICE

//Input services
#define DIN_SERVICE	100
#define AIN_SERVICE	101
#define IRRX_SERVICE	102
#define


enum unet_msg_types
{
	MT_WRITESERV_REQ,
	MT_WRITESERV_RES,
	MT_WRITESERV_ERR,

	MT_READSERV_REQ,
	MT_READSERV_RES,
	MT_READSERV_ERR,

	MT_DISCOVER_REQ,
	MT_DISCOVER_RES,
	MT_DISCOVER_ERR,

};
// message types

#define SETDATA_REQ_TYPE 10
#define SETDATA_RES_TYPE 11
#define SETDATA_ERR_TYPE 12
#define GETDATA_REQ_TYPE 20
#define GETDATA_RES_TYPE 21
#define GETDATA_ERR_TYPE 22

#define SRVDISC_REQ_TYPE
#define SRVDISC_RES_TYPE
#define SRVDISC_ERR_TYPE

struct unet_msg {
	uint8_t mtype;
	uint8_t len;
};

union unet_header {
	struct unet_msg curmsg;
	uint8_t data;
};



typedef uint8_t(*unetwr_t) (char cTxChar);
typedef uint8_t(*unetrd_t) (char * rxbuf);

uint8_t buf[10];
uint8_t buf[10];

// arreglo para definir los servicios implementados por este dispositivo
uint8_t device_services[] = {DOUT_SERVICE, TIME_SERVICE};

/**
 * Escribe datos a un servicio que utiliza el protocolo unet. El servicio debe
 * implementar los procedimientos necesarios para realizar la acción solicitada
 * o ajustar los valores solicitados y responder a la petición escribiendo su
 * respuesta en el mismo buffer donde se proporcionaron los datos de entrada
 *
 * @param data Datos de entrada (payload) para la petición de cambio/escritura
 * @param result Datos del resultado o respuesta de la petición (payload).
 *
 * @return Debe retornarse el tipo de mensaje, ya sea SETDATA_RES_TYPE o
 * SETDATA_ERR_TYPE segun se haya llevado o no a cabo de manera correcta la
 * petición solicitada
 */
uint8_t unet_set(uint8_t * data)
{
	switch (*((uint16_t *) data)) {
		// Datos de salidas digitales
	case DOUT_SERVICE:
		if (data[2] == DOUTHIGH)
			io_write(data[3], HIGH);
		else if (data[2] == DOUTLOW)
			io_write(data[3], LOW);
		else if (data[2] == DOUTTOGGLE)
			io_write(data[3], TOGGLE);

		break;
	case IRTX_SERVICE:
		if (data[2] == IRTXSEND)
			ir_send(data[3], (uint32_t *) data[4]);
		break;
	}
}

uint8_t unet_get(uint8_t * data, uint8_t * result)
{
}
unetrd_t read_callback;
unetwr_t write_callback;

BOOL unet_init(unetrd_t reader, unetwr_t writer)
{
	read_callback = reader;
	write_callback = writer;
}

enum unet_states {
	E_RX_HEADER,
	E_RX_PAYLOAD,
};

void unet_task()
{
	union unet_header header;

	static uint8_t i = 0;
	static enum unet_states unetst = E_RX_HEADER;

	switch (unetst) {
	case E_RX_HEADER:
		// mientras haya datos en el buffer de rx llenar header
		while (read_callback(header.data[i])) {
			if (++i >= sizeof(header)) {
				// Cuando este hecho avanzar FSM a recibir el payload
				unetst = E_RX_PAYLOAD;
				i = 0;
				break;
			}
		}
		break;
	case E_RX_PAYLOAD:
		break;

	case E_PROCESS:
		switch (header.curmsg.mtype) {
		case SETDATA_REQ_TYPE:
			// Peticion de "setear" datos para un servicio SETDATA_REQ
			// Ejecutamos la petición
			header.curmsg.len = unet_set(buf, header.curmsg.len, &header.curmsg.mtype);
			unet_send(header.curmsg, buf);
			break;
		case GETDATA_REQ_TYPE:
			break;
		}
		break;

	}

}

