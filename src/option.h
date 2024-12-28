#ifndef OPTION_H
#define OPTION_H

#include <stdbool.h>

#define Option(T)                                                              \
    struct {                                                                   \
        bool present;                                                          \
        T value;                                                               \
    }

#endif
