#ifndef OPTION_INT_H
#define OPTION_INT_H

#include "option.h"
#include <stdint.h>

typedef Option(int8_t) Option_int8;
typedef Option(int16_t) Option_int16;
typedef Option(int32_t) Option_int32;
typedef Option(int64_t) Option_int64;

typedef Option(uint8_t) Option_uint8;
typedef Option(uint16_t) Option_uint16;
typedef Option(uint32_t) Option_uint32;
typedef Option(uint64_t) Option_uint64;

#endif
