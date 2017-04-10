#ifndef PID_SUPPORT_H
#define PID_SUPPORT_H

#include "PID_Types.h"

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

pid_ticks_t pid_ticks_per_second(void); /* tbd by code using this library */
pid_ticks_t pid_ticks_get(void* ticksUser); /* tbd by code using this library */

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* PID_SUPPORT_H */
