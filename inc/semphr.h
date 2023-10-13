#ifndef SEMPHR_H
#define SEMPHR_H
/*
 * Normally this file would be included from FreeRTOS. Since we are not using that
 * in this project, we need some defines to keep the code happy
 */
#include <stdint.h>

typedef uint32_t SemaphoreHandle_t ;

#define xSemaphoreCreateMutex(x) (0)

#define pdMS_TO_TICKS(x) (0)
#define xSemaphoreTake(a,b) true
#define xSemaphoreGive(a)

#endif /* SEMPH_H */