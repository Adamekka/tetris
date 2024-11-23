#ifndef OPTIONAL_INT_H
#define OPTIONAL_INT_H

#include "optional.h"
#include <stdint.h>

typedef optional(int8_t) optional_int8;
typedef optional(int16_t) optional_int16;
typedef optional(int32_t) optional_int32;
typedef optional(int64_t) optional_int64;

typedef optional(uint8_t) optional_uint8;
typedef optional(uint16_t) optional_uint16;
typedef optional(uint32_t) optional_uint32;
typedef optional(uint64_t) optional_uint64;

#endif
